#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QFileInfo>

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

/* \brief Gets the name of all files with a *.xyz extension
 * in given directory, stores file names in a QStringList
 * \param dir_path Path to directory
 * \return QStringList of file names
 */
QStringList GetWellList(QString directory_path);

/* \brief Makes a copy of files associated with a given well
 * naming this copy TW01 which is the well name used in the
 * rms workflow
 * \param well_name the name of the well
 * \return True if copy successful, otherwise False
 */
bool CopyCurrentWell(QString directory_path, QString well_name);



#endif // FILE_HANDLING_H
