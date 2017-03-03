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
   along with FieldOpt-Benchmarks. If not, see <http://www.gnu.org/licenses/>.
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

#include "../src/permutation_string_writer.h"
#include "../src/f_at_each_combination.h"
#include "../src/for_each_combination.h"
#include "../src/utilities.hpp"

#include "../../../../FieldOpt/FieldOpt/Utilities/filehandling.hpp"
#include "../../../../FieldOpt/FieldOpt/Utilities/time.hpp"

#include <gtest/gtest.h>

using namespace Utilities::FileHandling;

namespace {

class combinationFunctionTest : public ::testing::Test {
 protected:
  combinationFunctionTest() {
  };

  virtual ~combinationFunctionTest() {}

  virtual void SetUp() {}

  virtual void TearDown() {}

  bool comparedfSetData(QString fSetData_mat, QString fSetData_cpp,
                        QString mdir, QString cdir){

      // 0 Black
      // 1 Red
      // 2 Green
      // 3 Yellow
      // 4 Blue
      // 5 Magenta
      // 6 Cyan
      // 7 White

      string cbr = "\033[1;31m";
      string cbg = "\033[1;32m";
      string cbm = "\033[1;35m";
      string ce = "\033[0m";

      QString fSet_mat_path = mdir + fSetData_mat;
      QString fSet_cpp_path = cdir + fSetData_cpp;
      bool A = FileExists(fSet_mat_path);
      bool B = FileExists(fSet_cpp_path);
      bool success = true;

      if(A && B)
      {
          QStringList *fSet_mat_str = ReadFileToStringList(fSet_mat_path);
          QStringList *fSet_cpp_str = ReadFileToStringList(fSet_cpp_path);
          auto fSet_mat_sz = fSet_mat_str->size();
          auto fSet_cpp_sz = fSet_cpp_str->size();

          EXPECT_EQ(fSet_mat_sz, fSet_cpp_sz);

          cout << "Comparing content of files: "
               << cbr << fSetData_mat.toStdString()
               << " (sz=" << fSet_mat_sz << ")"
               << ce << " and "
               << cbg << fSetData_cpp.toStdString()
               << " (sz=" << fSet_cpp_sz << ")"
               << ce << "\n";

          int count = 0;
          for (int i= 0 ; i < fSet_cpp_sz; ++i){

              auto C = (fSet_mat_str->at(i).split(" ")[0].toInt()
                == fSet_cpp_str->at(i).split(" ")[0].toInt());

              auto D = (fSet_mat_str->at(i).split(" ")[1].toInt()
                  == fSet_cpp_str->at(i).split(" ")[1].toInt());

              // Debug
              // auto C = fSet_mat_str->at(i).compare(fSet_cpp_str->at(i)); // returns 0 ??
              // cout << "True?" << C << endl;

              if ( !C || !D ){
                  cout << "Row " << i << ": "
                       << cbr << fSet_mat_str->at(i).toStdString() << ce << " and "
                       << cbg << fSet_cpp_str->at(i).toStdString() << ce << " differ... \n";
              }

              ++count;
          }
          cout << "Checked " << cbm << count << " out of "
               << fSet_mat_sz << ce << " rows.\n";

          // log time for looping through these sets
          // log memory used by variables read in

      }
      else if(!A || !B)
      {
          if(A && !B)
          {
              cout << "File: " << cbr
                   << fSetData_cpp.toStdString()
                   << ce << " is missing.\n";
          }
          else if(!A && B)
          {
              cout << "File: " << cbr
                   << fSetData_mat.toStdString()
                   << ce << " is missing.\n";
          }
          else{
              cout << "Both file: " << cbr
                   << fSetData_mat.toStdString() << ce
                   << " and " << "file: " << cbg
                   << fSetData_cpp.toStdString() << ce
                   << " are missing.\n";
          }

      }

      return success;

  }
};

TEST_F(combinationFunctionTest, MATLABnchoosek_comparison) {

    // MATLAB fSet data sets
    QString mdir = "../../combinations/fSets-matlab/";
    QString n002_mat = "n002_mat.fSet";
    QString n003_mat = "n003_mat.fSet";
    QString n009_mat = "n009_mat.fSet";
    QString n040_mat = "n040_mat.fSet";
    QString n080_mat = "storage/n080_mat.fSet";
    QString n100_mat = "storage/n100_mat.fSet";

    // cpp fSet data sets
    QString cdir = "../../combinations/fSets-cpp/";
    QString n002_cpp = "n002-Z6E+00_cpp.fSet";
    QString n003_cpp = "n003-Z4E+01_cpp.fSet";
    QString n009_cpp = "n009-Z3E+03_cpp.fSet";
    QString n040_cpp = "n040-Z1E+06_cpp.fSet";
    QString n080_cpp = "storage/n080-Z2E+07_cpp.fSet";
    QString n100_cpp = "storage/n100-Z5E+07_cpp.fSet";

    // --------------------------------------------------------
    EXPECT_TRUE(comparedfSetData(n002_mat, n002_cpp, mdir, cdir));
    EXPECT_TRUE(comparedfSetData(n003_mat, n003_cpp, mdir, cdir));
    EXPECT_TRUE(comparedfSetData(n009_mat, n009_cpp, mdir, cdir));
    EXPECT_TRUE(comparedfSetData(n040_mat, n040_cpp, mdir, cdir));

    if( startPrompt(2)==1 ) {
        EXPECT_TRUE(comparedfSetData(n080_mat, n080_cpp, mdir, cdir));
        EXPECT_TRUE(comparedfSetData(n100_mat, n100_cpp, mdir, cdir));
    }
}

TEST_F(combinationFunctionTest,
       Test_PermutationStringWriter) {

    int r, n, N, Z;
    r = 2;          // selection
    n = 9;          // sampling grid, 1D
    N = pow(n,2.0); // sampling grid, 2D
    Z = (N-1)*N/2;  // # of possible combinations (w/reverse)

    auto output_file = getSetFilename(n,Z) + "-test";
    PermutationStringWriter *writer =
        new PermutationStringWriter(output_file);

    writer->addPermutation("");
    EXPECT_FALSE(writer->temp_str_.size()>0);

    writer->addPermutation("1 0");
    EXPECT_TRUE(writer->temp_str_.size()>0);

    writer->flushToDisk();
    EXPECT_TRUE(writer->temp_str_.size()==0);
}

//TEST_F(combinationFunctionTest, MATLABnchoosek_comparison) {
//
//    int r, n, N, Z;
//    r = 2;          // selection
//    n = 9;          // sampling grid, 1D
//    N = pow(n,2.0); // sampling grid, 2D
//    Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
//
//
//    Prepare selection vector
//    std::vector<int> v(N);
//    std::iota(v.begin(), v.end(), 0);
//
//    Compute combinations: prints to disk after each combination
//    std::uint64_t count =
//        for_each_reversible_permutation(
//            v.begin(),
//            v.begin() + r,
//            v.end(),
//            f_at_each_combination(v.size(), writer));
//
//}

}
