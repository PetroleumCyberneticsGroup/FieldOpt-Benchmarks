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
std::vector<double> get_elapsed_time(QDateTime t_start){

    auto t_duration_ms = (double)time_since_milliseconds(t_start);
    std::vector<double> time_vector;

    time_vector.push_back(t_duration_ms); // milliseconds
    time_vector.push_back(t_duration_ms/1000); // seconds
    time_vector.push_back(t_duration_ms/1000/60); // minutes
    time_vector.push_back(t_duration_ms/1000/60/60); // hours
    time_vector.push_back(t_duration_ms/1000/60/60/24); // days

    return time_vector;
}

// ============================================================
QString getDateStr(QDateTime t_start){
    auto log_str = t_start.toString("dd.mm.yyyy HH:MM:SS") + "\n";
    return log_str;
}


// ============================================================
QString getCpuInfo(){

    QString cpu_str = "cat /proc/cpuinfo | grep "
        "\"model name\" -m1 | awk -F \":\" '{print $2}' ";

    QProcess process;
    process.start("bash", QStringList() << "-c" << cpu_str);

    process.waitForFinished(10);

    QString stdout = process.readAllStandardOutput();
    QString stderr = process.readAllStandardError();

    // debug
    // cout << "stdout: " << stdout.toStdString() << endl;
    // cout << "stderr: " << stderr.toStdString() << endl;

    if (stdout.startsWith(" "));
    stdout = stdout.mid(1) + "\n";

    return stdout;
}

// ============================================================
void print_to_log(QString log_file, QDateTime t_start){

    QString log_str;

    // --------------------------------------------------------
    // date
    auto date_str = getDateStr(t_start);

    // --------------------------------------------------------
    // cpu info
    auto cpu_str = getCpuInfo();

    // --------------------------------------------------------
    // print to log file
    log_str = date_str + cpu_str + "\n";
    Utilities::FileHandling::WriteLineToFile(log_str, log_file);
}

// ============================================================
QString getSetFilename(const int n, int Z){

    QString n_str, Z_str;
    n_str.sprintf("n%03.0f",(double)n);
    Z_str.sprintf("-Z%07.3E",(double)Z);

    QString file_path = "../combinations/"
        + n_str + Z_str + "_cpp.cSet";

    return file_path;
}

#endif //COMBINATIONSETS_UTILITIES_HPP
