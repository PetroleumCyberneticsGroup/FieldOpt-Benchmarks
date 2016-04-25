#include <QCoreApplication>
#include <QString>
#include <QProcess>
#include <QtDebug>
#include <iostream>
#include <QVector3D>
#include "./src/test_wells.h"
#include "./src/well_pcg.h"
#include "./src/well_rms.h"
#include "./src/file_handling.h"
#include "./src/well_data_pcg.h"

//#include "../../../FieldOpt/FieldOpt/WellIndexCalculator/geometry_functions/geometryfunctions.h"
//#include "../../../FieldOpt/FieldOpt/WellIndexCalculator/geometry_functions/geometryfunctions_exceptions.h"
//#include "../../../FieldOpt/FieldOpt/Model/reservoir/grid/xyzcoordinate.h"
//#include "../../../FieldOpt/FieldOpt/Model/reservoir/grid/cell.h"

int main(int argc, char *argv[])
{
    int debug_level = 1;

    bool run_rms = false;
    if(argc == 3 && (strcmp(argv[2],"norms") == 0))
    {
        run_rms = false;
    }

    // Clear console
    system("clear");

    // Get current path
    QString current_path = GetCurrentPath();

    // Get WellDataPCG object containing list of all well data
    // dirs and file names within current_path
    WellDataPCG WellDataPCG_;

    if(debug_level==2)
    {
        qDebug() << "argc = " << argc << "argv: " << argv <<
                  "condition: " << (strcmp(argv[1],"all") == 0);
    }

    if(argc == 1)
    {
        qDebug() << "Either provide the name of a well data folder"
                    "or specify 'all' to treat all folder in currrent"
                    "path. Exiting...";
        exit(-1);
    }
    else if(argc >= 2 && (strcmp(argv[1],"all") == 0))
    {
        qDebug() << "treating all folders...";
        WellDataPCG_ = GetDirList(current_path,debug_level);
    }
    else if(argc >= 2)
    {
        qDebug() << "treating single folder...";
        WellDataPCG_ = GetDirListSingle(current_path,argv[1],debug_level);
    }
    else
    {
        qDebug() << "You need to specify the name of the "
                    "well data folder or specify 'all' if "
                    "all folders in current path are to be "
                    "treated as well data folders ... exiting";
        exit(-1);
    }

    if(debug_level==2){
        qDebug() << "\nDEBUG => well dirs paths:"
                 << WellDataPCG_.well_dirs_paths;
        qDebug() << "DEBUG => sizeof(well dirs paths)"
                 << WellDataPCG_.well_dirs_paths.size();

        qDebug() << "\nDEBUG => well dirs names:"
                 << WellDataPCG_.well_dirs_names;
        qDebug() << "DEBUG => sizeof(well dirs names):"
                 << WellDataPCG_.well_dirs_names.size();

        qDebug() << "\nDEBUG => well files paths:"
                 << WellDataPCG_.well_file_names;
        qDebug() << "DEBUG => sizeof(well dirs paths)"
                 << WellDataPCG_.well_file_names.size();
    }

    QString dpath;
    QString dname;
    QString fname;
    QString inputf;
    QString outputf;
    bool ccode;

    /* RMS LOOP
     * Loop through well directories, transfer well data from each
     * directory into workflow directory, compute well indices, then
     * transfer back DATA file containing COMPDAT results
     */

    for ( int ii = 0;
          ii < WellDataPCG_.well_dirs_paths.size(); ii++)
    {
       std::string strout = "\nUSING RMS TO COMPUTE WELL INDICES...";
       std::string lnstr = std::string((strout.length()-1)*2,'=');
       std::cout << lnstr + "\n" << strout + "\n" << lnstr + "\n" << std::endl;
       qDebug("==> treating ii:%2.0d => %s", ii,
              WellDataPCG_.well_dirs_paths[ii].toStdString().c_str());

       // Find and select well data file (tw*.xyz) from one folder
       dpath = WellDataPCG_.well_dirs_paths[ii];
       dname = WellDataPCG_.well_dirs_names[ii];
       fname = WellDataPCG_.well_file_names[ii];
       inputf = dpath + "/" + fname;
       outputf = current_path + "/workflow/TW01.xyz";

       // Copy data well file (tw*.xyz) into workflow folder (TW01.xyz)
       ccode = CopyToFromWorkflowFolder(inputf, outputf);
       if(debug_level==2)
       {
            qDebug() << "boolean flag from copy to workflow: " << ccode;
       }

       // Call RMS workflow for current file
       int ecode = RunRMS(current_path,run_rms);
       qDebug() << "exit code from running RMS: " << ecode;

       // Copy files back to well data folder (EVENTS_TW01.DATA)
       inputf = current_path + "/workflow/EVENTS_TW01.DATA";
       outputf = dpath + "/EVENTS_" + dname + "_RMS.DATA";
       ccode = CopyToFromWorkflowFolder(inputf, outputf);
       if(debug_level==2)
       {
            qDebug() << "boolean flag from copy from workflow: " << ccode;
       }

    }

    /* PCG LOOP
     * Loop through well directories, transfer well data from each
     * directory into workflow directory, compute well indices, then
     * transfer back DATA file containing COMPDAT results
     */
    for ( int ii = 0;
          ii < WellDataPCG_.well_dirs_paths.size(); ii++)
    {
        std::string strout = "USING PCG LIBRARY TO COMPUTE WELL INDICES...";
        std::string lnstr = std::string((strout.length()-1)*2,'=');
        std::cout << lnstr + "\n" << strout + "\n" << lnstr + "\n" << std::endl;

        qDebug("==> treating ii:%2.0d => %s", ii,
               WellDataPCG_.well_dirs_paths[ii].toStdString().c_str());

        // Find and select well data file (tw*.xyz) from one folder
        dpath = WellDataPCG_.well_dirs_paths[ii];
        dname = WellDataPCG_.well_dirs_names[ii];
        fname = WellDataPCG_.well_file_names[ii];
        inputf = dpath + "/" + fname;
//        outputf = current_path + "/workflow/TW01.xyz";

        // Read data from TW01.xyz file
        QFile inputFile(inputf);
        if (inputFile.open(QIODevice::ReadOnly))
        {
           QTextStream in(&inputFile);

           // Read complete file to QString
           QString all_lines = in.readAll();

           // Split file at newline
           QStringList pieces = all_lines.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
           qDebug() << "all_lines(0) = " << pieces.value(0);
           qDebug() << "all_lines(1) = " << pieces.value(1);
           qDebug() << "all_lines(2) = " << pieces.value(2);

           // Second and third lines contain well placement coordinates
           // Simplyfy removes unecessary spaces at beginning and end.
           QString first_vec = pieces.value(1).simplified();
           QString second_vec = pieces.value(2).simplified();

           // Separate coordinates at spaces and add to QVector3D
           QVector3D start_well = QVector3D(first_vec.split(" ").at(0).toFloat(), first_vec.split(" ").at(1).toFloat() ,first_vec.split(" ").at(2).toFloat());
           QVector3D end_well = QVector3D(second_vec.split(" ").at(0).toFloat(), second_vec.split(" ").at(1).toFloat() ,second_vec.split(" ").at(2).toFloat());

           qDebug() << "QVector start_well = " << start_well;
           qDebug() << "QVector end_well = " << end_well;


        /*void GeometryFunctions::print_well_index_file(
            Model::Reservoir::Grid::Grid *grid,
            QList<QVector3D *> start_points,
            QList<QVector3D *> end_points,
            double wellbore_radius,
            double min_wi,
            string filename);
        */
//outputf = dpath + "/EVENTS_" + dname + "_RMS.DATA";


//           in.reset();
//           while (!in.atEnd())
//           {
//              QString line2 = in.readLine();
//              qDebug() << "readline" << line2;
//           }



           inputFile.close();
        }


        // Compute and print well indices using PCG library

    }

    /* Compare DATA files
     * Loop through each
     */



}
