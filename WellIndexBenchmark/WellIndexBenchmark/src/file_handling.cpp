
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDirIterator>
#include <QRegularExpression>
#include "./src/well_data_pcg.h"

#include <term.h>
#include <unistd.h>

// Copy from FieldOpt/Utilities/FileHandling.cpp
// (Replace by library later on...)
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

// Copy from FieldOpt/Utilities/FileHandling.cpp
// (Replace by library later on...)
bool DirectoryExists(QString directory_path)
{
    QFileInfo folder(directory_path);
    if (folder.exists() && folder.isDir()) return true;
    else return false;
}

// Returns current path
QString GetCurrentPath()
{
    QDir dir;
    QString current_path = dir.currentPath();
    qDebug() << "Current path is: " << current_path;
    return current_path;
}

// Returns a WellDataPCG objects that includes a QStringList
// list of all directories within current directory that contain
// a well data file of the form tw*.xyz
WellDataPCG GetDirList(QString directory_path, bool dbgFlag)
{
    WellDataPCG WellDataPCG_;

    // Setup QDir and QDirIterator objects
    QDir dir (directory_path);
    dir.setSorting(QDir::Name);

    QDirIterator it(dir.absolutePath(),
                    QDir::Dirs |
                    QDir::NoDotAndDotDot);

    QStringList well_dirs_paths;
    QStringList well_dirs_names;
    QStringList well_file_names;

    qDebug() << "checking if directories in current path"
                "constain well data files...: ";

    while (it.hasNext()) {

        QString dir_name = it.next();
        if (dbgFlag)
        { qDebug() << "current folder [it.next()]: "
                   << dir_name;  }

        QDir temp_dir (it.fileName());
        QStringList dir_list =
                temp_dir.entryList(QStringList() << "tw*xyz",
                                  QDir::AllEntries |
                                  QDir::Files |
                                  QDir::CaseSensitive |
                                  QDir::NoDotAndDotDot);

        if (dir_list.isEmpty() || dir_list.size() > 1){
            qDebug() << "==> directory" << it.fileName()
                     << "has no well file or has"
                        " multiple well files!";
        }
        else if(dir_list.size()==1){
            if (dbgFlag)
            { qDebug() << "dir_list: " << dir_list;  }
            well_dirs_paths << it.filePath();
            well_dirs_names << it.fileName();
            well_file_names << dir_list;
        }
        else{
            if (dbgFlag)
            { qDebug() << "???? ";  }
        }
    }

    WellDataPCG_.well_dirs_paths = well_dirs_paths;
    WellDataPCG_.well_dirs_names = well_dirs_names;
    WellDataPCG_.well_file_names = well_file_names;

    return WellDataPCG_;
}

// Function that clears screen
// code taken from
// http://www.cplusplus.com/articles/4z18T05o/
void ClearScreen()
{
if (!cur_term)
{
int result;
setupterm( NULL, STDOUT_FILENO, &result );
if (result <= 0) return;
}

putp( tigetstr( "clear" ) );
}

bool CopyCurrentWell(QString directory_path, QString well_name)
{

    QString source_file = directory_path + "/" + well_name;
    QString target_file = directory_path + "/TW01";
    qDebug() << "source_file " << source_file;
    qDebug() << "target_file " << target_file;

    return true;
}
