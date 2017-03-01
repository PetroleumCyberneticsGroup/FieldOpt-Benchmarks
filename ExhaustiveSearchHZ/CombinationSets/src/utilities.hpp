/******************************************************************************
   Copyright (C) 2015-2017 Mathias C. Bellout <mathias.bellout@ntnu.no>

   This file is part of the FieldOpt-Benchmarks project,
   an NTNU Petroleum Cybernetics Group project.

   FieldOpt-Benchmarks is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   FieldOpt-Benchmarks is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with FieldOpt.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#ifndef COMBINATIONSETS_UTILITIES_HPP
#define COMBINATIONSETS_UTILITIES_HPP

#include <QFile>
#include <QString>
#include <QFileInfo>
#include <QTextStream>
#include <QDateTime>
#include <QProcess>

#include "../../../../FieldOpt/FieldOpt/Utilities/time.hpp"
#include "../../../../FieldOpt/FieldOpt/Utilities/filehandling.hpp"

// ============================================================
QString get_elapsed_time(QDateTime t_start){

    QString time_str;
    auto t_duration_ms = (double)time_since_milliseconds(t_start);
    // std::vector<double> time_vector;

    // time_vector.push_back(t_duration_ms); // milliseconds
    // time_vector.push_back(t_duration_ms/1000); // seconds
    // time_vector.push_back(t_duration_ms/1000/60); // minutes
    // time_vector.push_back(t_duration_ms/1000/60/60); // hours
    // time_vector.push_back(t_duration_ms/1000/60/60/24); // days

    // time_str = "Elapsed time: \n"
    //           + QString::number(t_duration_ms,'E',3) + " "
    //           + QString::number(time_vector[1],'E',3) + " seconds\n"
    //           + QString::number(time_vector[2],'E',3) + " minutes\n"
    //           + QString::number(time_vector[3],'E',3) + " hours\n"
    //           + QString::number(time_vector[4],'E',3) + " days\n";

    QString t_ms, t_s, t_m, t_h, t_d;

    t_ms = QString("%6.1f milliseconds\n").arg(t_duration_ms);
    t_s  = QString("%6.1f seconds\n").arg(t_duration_ms/1000);
    t_m  = QString("%6.1f minutes\n").arg(t_duration_ms/1000/60);
    t_h  = QString("%6.1f hours\n").arg(t_duration_ms/1000/60);
    t_d  = QString("%6.1f days\n").arg(t_duration_ms/1000/60/60/24);

    time_str = "Elapsed time: \n" + t_ms + t_s + t_m  + t_h  + t_d;

    return time_str;
}

// ============================================================
QString getDateStr(QDateTime t_start){
    auto log_str = t_start.toString("dd.mm.yyyy HH:MM:SS") + "\n";
    return log_str;
}

// ============================================================
QString getFileSize(QString file_path){
    auto file_sz = (double)Utilities::FileHandling::GetFileSize(file_path.toStdString());

    // Conversions
    // 1 kB = 1 kilo byte = 1000 B
    // 1 KB (eller KiB) = 1 kibi byte = 1024 B
    // 1 mB = 1 mega byte = 1000^2 B
    // 1 MB (eller MiB) = 1 mebi byte = 1024^2 B

    QString fs_B, fs_KiB, fs_MiB, fs_GiB;

    fs_B   = QString("%6.0f bytes (B)\n").arg(file_sz);
    fs_KiB = QString("%6.0f KiB \n").arg(file_sz/pow(1024,1)); // (1 kibiB = 1024 B)
    fs_MiB = QString("%6.0f MiB \n").arg(file_sz/pow(1024,2)); // (1 mebiB = 1024^2 B)
    fs_GiB = QString("%6.0f MiB \n").arg(file_sz/pow(1024,3)); // (1 gebiB = 1024^3 B)

    QString size_str = "File Size:\n" + fs_B + fs_KiB + fs_MiB + fs_GiB;

    return size_str;
}

// ============================================================
QStringList getHostname(){

    QStringList host_strs;
    QProcess process;
    process.start("bash", QStringList() << "-c" << "hostname");

    process.waitForFinished(10);

    QString stdout = process.readAllStandardOutput();
    QString stderr = process.readAllStandardError();

    stdout.remove(QRegExp("\n"));
    QString host_str = "Hostname: " + stdout + "\n";

    host_strs << stdout;
    host_strs << host_str;

    return host_strs;
}

// ============================================================
QString getCpuInfo(){

    QString cmd_str = "cat /proc/cpuinfo | grep "
        "\"model name\" -m1 | awk -F \":\" '{print $2}' ";

    QProcess process;
    process.start("bash", QStringList() << "-c" << cmd_str);

    process.waitForFinished(10);

    QString stdout = process.readAllStandardOutput();
    QString stderr = process.readAllStandardError();

    if (stdout.startsWith(" "));
    stdout = stdout.mid(1);

    QString cpu_str = "Processor: " + stdout;
    return cpu_str;
}

// ============================================================
void print_to_log(QString log_file,
                  QDateTime t_start,
                  QString file_path){

    QString log_str;

    // --------------------------------------------------------
    // date
    auto date_str = getDateStr(t_start);

    // --------------------------------------------------------
    // cpu info
    auto cpu_str = getCpuInfo();

    // --------------------------------------------------------
    // hostname
    auto host_str = getHostname();

    // --------------------------------------------------------
    // file size
    auto size_str = getFileSize(file_path);

    // --------------------------------------------------------
    // print to log file
    log_str = QString(50, '-') + "\n"
        + date_str + host_str[1] + cpu_str + size_str;
    Utilities::FileHandling::WriteLineToFile(log_str, log_file, false);
}

// ============================================================
QString getSetFilename(const int n, int Z){

    QString n_str, Z_str;
    n_str.sprintf("n%03.0f",(double)n);
    Z_str.sprintf("-Z%07.3E",(double)Z);

    QString file_path = "../../combinations/"
        + n_str + Z_str + "_cpp.cSet";

    return file_path;
}

#endif //COMBINATIONSETS_UTILITIES_HPP
