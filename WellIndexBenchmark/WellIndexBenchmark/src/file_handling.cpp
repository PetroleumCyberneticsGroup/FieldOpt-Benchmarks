
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
    qDebug() << "==> current path is: " << current_path << "\n";
    return current_path;
}

WellDataPCG GetDirListSingle(QString directory_path,
                             QString dir_name, int debug_level)
{
    WellDataPCG WellDataPCG_;

    // Setup QDir object
    QDir dir (directory_path);
    dir.setSorting(QDir::Name);

    QStringList well_dirs_paths;
    QStringList well_dirs_names;
    QStringList well_file_names;

    qDebug() << "==> checking if directories in current "
                "path constain well data files...: \n";

    QDir temp_dir = directory_path + "/" + dir_name;

    if (!temp_dir.exists())
    {
        qDebug() << "directory does not exist! ..."
                    "exiting";
        exit(-1);
    }

    if (debug_level==2)
    { qDebug() << "current folder: "
               << dir_name;  }
    // Search given directory
    QStringList dir_list =
            temp_dir.entryList(QStringList() << "tw*xyz",
                              QDir::AllEntries |
                              QDir::Files |
                              QDir::CaseSensitive |
                              QDir::NoDotAndDotDot);

    if (dir_list.isEmpty() || dir_list.size() > 1){
        qDebug() << "==> directory" << temp_dir.dirName()
                 << "has no well file or has"
                    " multiple well files!";
    }
    else if(dir_list.size()==1){
        if (debug_level==2)
        { qDebug() << "dir_list: " << dir_list;  }

        well_dirs_paths << temp_dir.absolutePath();
        well_dirs_names << temp_dir.dirName();
        well_file_names << dir_list;
    }
    else{
        if (debug_level==2)
        { qDebug() << "???? ";  }
    }

    WellDataPCG_.well_dirs_paths = well_dirs_paths;
    WellDataPCG_.well_dirs_names = well_dirs_names;
    WellDataPCG_.well_file_names = well_file_names;

    return WellDataPCG_;
}


// Returns a WellDataPCG objects that includes a QStringList
// list of all directories within current directory that contain
// a well data file of the form tw*.xyz
WellDataPCG GetDirList(QString directory_path, int debug_level)
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

    qDebug() << "==> checking if directories in current "
                "path constain well data files...: \n";

    while (it.hasNext()) {

        QString dir_name = it.next();
        QDir temp_dir = it.fileName();
        QString file_path = it.filePath();

        if (debug_level==2)
        { qDebug() << "current folder [it.next()]: "
                   << dir_name;  }
        // Search given directory
        QStringList dir_list =
                temp_dir.entryList(QStringList() << "tw*xyz",
                                  QDir::AllEntries |
                                  QDir::Files |
                                  QDir::CaseSensitive |
                                  QDir::NoDotAndDotDot);

        if (dir_list.isEmpty() || dir_list.size() > 1){
            qDebug() << "==> directory" << temp_dir.dirName()
                     << "has no well file or has"
                        " multiple well files!";
        }
        else if(dir_list.size()==1){
            if (debug_level==2)
            { qDebug() << "dir_list: " << dir_list;  }

            well_dirs_paths << file_path;
            well_dirs_names << temp_dir.dirName();
            well_file_names << dir_list;
        }
        else{
            if (debug_level==2)
            { qDebug() << "???? ";  }
        }
    }

    WellDataPCG_.well_dirs_paths = well_dirs_paths;
    WellDataPCG_.well_dirs_names = well_dirs_names;
    WellDataPCG_.well_file_names = well_file_names;

    return WellDataPCG_;
}


int RunRMS(QString current_path, bool run_rms)
{
    /* bash /opt/roxar/rms/rms_2013.0.3_el5 -project \
     * rms_wi_benchmark.pro -batch EXPORT_TW01_MD -readonly
    */
    QString rms_command =
            "bash /opt/roxar/rms/rms_2013.0.3_el5 -project "
            + current_path + "/../rms/rms_wi_benchmark.pro"
            + " -batch EXPORT_TW01_MD -readonly";

    int ecode;
    if(run_rms)
    {
        qDebug() << "\n==> performing RMS command: " << rms_command;
        ecode = system(rms_command.toLatin1());
    }else
    {
        qDebug() << "\n==> not performing RMS command: ";
        ecode = -1;
    }
    return ecode;
}

bool CopyToFromWorkflowFolder(QString inputf, QString outputf)
{
    qDebug() << "\ninput file:" << inputf;
    qDebug() << "output file:" << outputf;

    if (QFile::exists(outputf))
    {
        QFile::remove(outputf);
    }
    bool ccode = QFile::copy(inputf,outputf);
    return ccode;
}



bool CopyCurrentWell(QString directory_path, QString well_name)
{

    QString source_file = directory_path + "/" + well_name;
    QString target_file = directory_path + "/TW01";
    qDebug() << "source_file " << source_file;
    qDebug() << "target_file " << target_file;

    return true;
}
