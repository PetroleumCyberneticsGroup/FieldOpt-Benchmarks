#include <QCoreApplication>
#include <QString>
#include <QtDebug>
#include <iostream>
#include "./src/test_wells.h"
#include "./src/well_pcg.h"
#include "./src/well_rms.h"
#include "./src/file_handling.h"
#include "./src/well_data_pcg.h"





int main(int argc, char *argv[])
{

    // Get current path
    QString current_path = GetCurrentPath();

    // Get WellDataPCG object containing list of all well data
    // dirs and file names within current_path
    WellDataPCG WellDataPCG_ = GetDirList(current_path,true);

    qDebug() << "well dirs paths: \n" << WellDataPCG_.well_dirs_paths;
    qDebug() << "well dirs: \n" << WellDataPCG_.well_dirs_names;
    qDebug() << "well files names: \n" << WellDataPCG_.well_file_names;
    qDebug() << "\n";

    // Read data from one of the well files



    // Call RMS to

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
