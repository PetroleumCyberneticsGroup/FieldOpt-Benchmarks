#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <QDebug>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDirIterator>
#include <QRegularExpression>
#include "./src/well_data_pcg.h"

/* \brief Check if file exists
 * \param file_path Path to file
 * \return True if file exist, otherwise False
 */
bool FileExists(QString file_path);

/* \brief Check if directory exists
 * \param directory_path Path to directory
 * \return True if file exist, otherwise False
 */
bool DirectoryExists(QString directory_path);

/* \brief Get current directory
 * \param none
 * \return QString of absolute current path
 */
QString GetCurrentPath();

int RunRMS(QString model, QString current_path, bool run_rms);

bool CopyToFromWorkflowFolder(QString inputf, QString outputf);

/* \brief Gets the name of all files with a *.xyz extension
 * in given directory, stores file names in a QStringList
 * \param dir_path Path to directory
 * \return QStringList of file names
 */
WellDataPCG GetDirList(QString directory_path, int debug_level);

WellDataPCG GetDirListSingle(QString directory_path,
                             QString dir_name, int debug_level);


/* \brief Makes a copy of files associated with a given well
 * naming this copy TW01 which is the well name used in the
 * rms workflow
 * \param well_name the name of the well
 * \return True if copy successful, otherwise False
 */
bool CopyCurrentWell(QString directory_path, QString well_name);



#endif // FILE_HANDLING_H
