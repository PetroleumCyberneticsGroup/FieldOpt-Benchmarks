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

    QString time_str, t_ms, t_s, t_m, t_h, t_d;
    auto t_duration_ms = (double)time_since_milliseconds(t_start);

    t_ms = QString("%1 milliseconds\n").arg(t_duration_ms,12,'f',1);
    t_s  = QString("%1 seconds\n").arg(t_duration_ms/1000,12,'f',1);
    t_m  = QString("%1 minutes\n").arg(t_duration_ms/1000/60,12,'f',1);
    t_h  = QString("%1 hours\n").arg(t_duration_ms/1000/60,12,'f',1);
    t_d  = QString("%1 days\n").arg(t_duration_ms/1000/60/60/24,12,'f',1);

    time_str = "Elapsed time: \n" + t_ms + t_s + t_m  + t_h  + t_d;

    return time_str;
}

// ============================================================
QString getDateStr(QDateTime t_start){
    auto log_str = t_start.toString("ddd dd.MM.yyyy hh:mm:ss") + "\n";
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

    fs_B   = QString("%1 bytes(B)\n").arg(file_sz,12,'f',0);
    fs_KiB = QString("%1 KiB \n").arg(file_sz/pow(1024,1),12,'f',1); // (1 kibiB = 1024 B)
    fs_MiB = QString("%1 MiB \n").arg(file_sz/pow(1024,2),12,'f',1); // (1 mebiB = 1024^2 B)
    fs_GiB = QString("%1 GiB \n").arg(file_sz/pow(1024,3),12,'f',1); // (1 gebiB = 1024^3 B)

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
QString getSetInfo(int r, int n, int N, int Z){

    QString r_str, n_str, N_str, Z_str;

    r_str = QString("Selection, r = %1\n")
        .arg((double)r,1,'f',0);
    n_str = QString("Sampling grid (1D), n = %1\n")
        .arg((double)n,1,'f',0);
    N_str = QString("Sampling grid (2D), N = n^2 = %1\n")
        .arg((double)N,1,'f',0);
    Z_str = QString("# of combinations (reverse), Z = (N-1)*N/2 = %1\n")
        .arg((double)Z,6,'E',3);

    QString set_str = r_str + n_str + N_str + Z_str;
    return set_str;
}

// ============================================================
QString getLogName(){

    auto host_str = getHostname();
    QString log_file =
        "../../combinations/runtimes-" + host_str[0] + ".log";
    Utilities::FileHandling::CreateFile(log_file, true);

    return log_file;
}

// ============================================================
QDateTime printToLog(int r, int n, int N, int Z, QString &log_file){

    // --------------------------------------------------------
    // hostname
    auto host_str = getHostname();

    // --------------------------------------------------------
    // date
    auto t_start = QDateTime::currentDateTime();
    auto date_str = getDateStr(t_start);

    // --------------------------------------------------------
    // cpu info
    auto cpu_str = getCpuInfo();

    // --------------------------------------------------------
    // combination set info
    auto set_str = getSetInfo(r, n, N, Z);

    // --------------------------------------------------------
    // print to log file
    QString log_str = QString(50, '-') + "\n"
            + date_str + host_str[1] + cpu_str + set_str;
    Utilities::FileHandling::WriteLineToFile(log_str, log_file, false);

    // --------------------------------------------------------
    // return start time
    return t_start;
}

// ============================================================
QString getSetFilename(const int n, int Z){

    QString n_str, Z_str;

    n_str = QString("n%1").arg((double)n,3,'f',0,'0');
    Z_str = QString("-Z%1").arg((double)Z,4,'E',0,'0');

    QString file_path = "../../combinations/"
        + n_str + Z_str + "_cpp.cSet";

    return file_path;
}

#endif //COMBINATIONSETS_UTILITIES_HPP
