#include <QCoreApplication>
#include <QString>
#include <QProcess>
#include <QtDebug>
#include <iostream>
#include "./src/test_wells.h"
#include "./src/well_pcg.h"
#include "./src/well_rms.h"
#include "./src/file_handling.h"
#include "./src/well_data_pcg.h"

int main(int argc, char *argv[])
{
    // ClearScreen();

    // Get current path
    QString current_path = GetCurrentPath();

    // Get WellDataPCG object containing list of all well data
    // dirs and file names within current_path
    WellDataPCG WellDataPCG_ = GetDirList(current_path,false);

//    qDebug() << "well dirs paths: \n" << WellDataPCG_.well_dirs_paths;
//    qDebug() << "well dirs: \n" << WellDataPCG_.well_dirs_names;
//    qDebug() << "well files names: \n" << WellDataPCG_.well_file_names;
//    qDebug() << "\n";

    // Read data from one of the well files

    qDebug() << sizeof(WellDataPCG_.well_dirs_paths);

    QString inputf = WellDataPCG_.well_dirs_paths[0]
            + "/" +  WellDataPCG_.well_file_names[0];
    QString outputf = WellDataPCG_.well_dirs_paths[0] + "/TW01.xyz";

    qDebug() << "input file \n" << inputf;
    qDebug() << "output file \n" << outputf;

    if (QFile::exists(outputf))
    {
        QFile::remove(outputf);
    }
    bool copy_ok = QFile::copy(inputf, outputf);

    qDebug() << "copy_ok: " << copy_ok;

    // Call RMS workflow for current file

//    bash /opt/roxar/rms/rms_2013.0.3_el5 -project \
//    rms_wi_benchmark.pro -batch EXPORT_TW01_MD -readonly

//    QString rms_command =
//            "bash /opt/roxar/rms/rms_2013.0.3_el5 -project "
//            + current_path + "../rms/rms_wi_benchmark.pro"
//            + " -batch EXPORT_TW01_MD -readonly";
//    system(rms_command);

    QString program = "bash /opt/roxar/rms/rms_2013.0.3_el5";
    QStringList arguments;
    arguments << "-project" << current_path + "../rms/rms_wi_benchmark.pro"
              << " -batch EXPORT_TW01_MD -readonly";
    QProcess process;
    process.start(program, arguments);
    process.waitForBytesWritten();
        if (!process.waitForFinished(1)) {
            process.kill();
            process.waitForFinished(1);
        }

    // Input relative path and name of well data directory
    // If no input, then default is data folder names starting
    // with "tw" lying in current folder



//    QString welldir_name;

//    fs::path welldir_path;
////    fs::path welldir_base = fs::current_path();

//    if (argc > 1){
//        welldir_path = fs::absolute(argv[1], fs::current_path());

//        directory_path = QString::fromStdString(
//                    welldir_path.string());

//        welldir_name = QString::fromStdString(
//                    welldir_path.filename().string());
//    }
//    else{
//        fs::path name = "tw00_00";
//        welldir_path = fs::absolute(name, fs::current_path());
//        directory_path = ".";
////        welldir_name = "tw*";
//        welldir_name = QString::fromStdString(
//                    welldir_path.filename().string());
//    }



//    qDebug() << welldir_name;
//    qDebug() << directory_path;
//    qDebug() << welldir_name;


//    QStringList well_list=GetWellList(welldir_name);




//    // argv[1] input is name of well dir and xyz data file


//    // Get names of well data directories, i.e., directories
//    // containing well data in the form of *.xyz files

//    const std::string fname = argv[1];

//    const fs::path dir_path = fname;
//    const std::string file_name = fname + ".xyz";
//    fs::path path_found;

//    std::cout << "dirpath: " << dir_path.string() << std::endl;

//    qDebug() << QString::fromStdString(dir_path.string());
//    qDebug() << QString::fromStdString(file_name);

//    bool aa = find_file(dir_path, file_name, path_found);

//    std::cout << "bool aa: " << aa << std::endl;

//    qDebug() << QString::fromStdString(path_found.string());

//    std::cout << path_found.string();

//    // Directory where input and output well files are stored
//    QString input_directory = "/home/bellout/git/PCG/FieldOptBenchmarks"
//    "/WellIndexBenchmark/WellIndexBenchmark/wells";

//    QString output_directory = "/home/bellout/Dropbox/SharedFieldOptDev15"
//    "/files_HM/Test_cases_well_index_calculation/wells_output";

    // Create pcg well object
//    WellPCG well_pcg = WellPCG();






//    qDebug() << well_list;

//    QString well_name = well_list[0];

//    CopyCurrentWell(output_directory, well_name);

}
