#include <QCoreApplication>
#include <QString>
#include <QDebug>
#include <iostream>
#include "./src/file_handling.h"
#include "./src/well_pcg.h"

int main(int argc, char *argv[])
{

    // Directory where input and output well files are stored
    QString input_directory = "/home/bellout/Dropbox/SharedFieldOptDev15"
    "/files_HM/Test_cases_well_index_calculation/wells_input";

    QString output_directory = "/home/bellout/Dropbox/SharedFieldOptDev15"
    "/files_HM/Test_cases_well_index_calculation/wells_output";

    // Create pcg well object
    WellPCG well_pcg = WellPCG();



    QStringList well_list=GetWellList(input_directory);

    qDebug() << well_list;

    QString well_name = well_list[0];

    CopyCurrentWell(output_directory, well_name);

    QCoreApplication a(argc, argv);

    return a.exec();
}
