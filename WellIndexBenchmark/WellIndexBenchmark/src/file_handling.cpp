#include <QDebug>
#include "file_handling.h"

bool FileExists(QString file_path)
{
    QFileInfo file(file_path);
    QFileInfo file_relative(file.absoluteFilePath());
    if (file.exists() && file.isFile())
        return true;
    else if (file_relative.exists() && file_relative.isFile())
        return true;
    else return false;
}

bool DirectoryExists(QString directory_path)
{
    QFileInfo folder(directory_path);
    if (folder.exists() && folder.isDir()) return true;
    else return false;
}

QStringList GetWellList(QString directory_path)
{
    QDir dir (directory_path);
    dir.setSorting(QDir::Name);

    QStringList filter;
    filter << "*.xyz";
    dir.setNameFilters(filter);

    QStringList well_list = dir.entryList(QDir::AllEntries | QDir::Dirs);

    return well_list;
}

bool CopyCurrentWell(QString directory_path, QString well_name)
{

    QString source_file = directory_path + "/" + well_name;
    QString target_file = directory_path + "/TW01";
    qDebug() << "source_file " << source_file;
    qDebug() << "target_file " << target_file;

//    std::ifstream  src("from.xyz", std::ios::binary);
//    std::ofstream  dst("to.xyz",   std::ios::binary);

//    dst << src.rdbuf();
    return true;
}
