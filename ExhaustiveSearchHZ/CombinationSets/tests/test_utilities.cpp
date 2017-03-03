/******************************************************************************
   Copyright (C) 2017 Mathias C. Bellout <mathias.bellout@ntnu.no>

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
   along with FieldOpt-Benchmarks.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

#include <QFile>
#include <QString>
#include <QFileInfo>
#include <QTextStream>
#include <QDateTime>
#include <QProcess>

#include "../src/for_each_combination.h"
#include "../src/utilities.hpp"
#include "../../../../FieldOpt/FieldOpt/Utilities/filehandling.hpp"
#include "../../../../FieldOpt/FieldOpt/Utilities/time.hpp"

#include <gtest/gtest.h>
using namespace std;

namespace {

class utilitiesTest : public ::testing::Test {
 protected:
  utilitiesTest() {
  };

  const int r = 2;   // selection
  const int n = 9;   // sampling grid, 1D
  const int N = pow(n,2.0); // sampling grid, 2D
  const int Z = (N-1)*N/2; // # of possible combinations (w/reverse)
  virtual ~utilitiesTest() {}

  virtual void SetUp() {}

  virtual void TearDown() {}
};

TEST_F(utilitiesTest,getSetFilenameTest_Test) {

    int n, N, Z;
    QString file_path;

    n = 9;
    N = pow(n,2.0);
    Z = (N-1)*N/2;
    file_path = getSetFilename(n,Z);
    cout << Z << ": " << file_path.toStdString() << endl;

    n = 25;
    N = pow(n,2.0);
    Z = (N-1)*N/2;
    file_path = getSetFilename(n,Z);
    cout << Z << ": " << file_path.toStdString() << endl;

    n = 200;
    N = pow(n,2.0);
    Z = (N-1)*N/2;
    file_path = getSetFilename(n,Z);
    cout << Z << ": " << file_path.toStdString() << endl;

}

TEST_F(utilitiesTest,getHostname_Test) {
    auto host_str = getHostname();

    for (int i; i < host_str.size(); ++i){
        if (host_str[i].startsWith(" "))
            host_str[i] = host_str[i].mid(1);
        host_str[i].remove(QRegExp("\n"));
        cout << host_str[i].toStdString() << " ";
    }
    cout << endl;

    // override hostname to test snippet
    host_str[0] = "compute-1-0.local";
    if ( host_str[0].contains("compute") )
        cout << "host_str contains \"compute\"? => "
             << host_str[0].contains("compute")
             << endl;

}

}
