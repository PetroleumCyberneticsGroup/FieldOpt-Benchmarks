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

namespace {

class combinationFunctionTest : public ::testing::Test {
 protected:
  combinationFunctionTest() {

  };

  virtual ~combinationFunctionTest() {}

  virtual void SetUp() {}

  virtual void TearDown() {}
};

TEST_F(combinationFunctionTest, MATLABnchoosek_comparison) {


}

TEST_F(combinationFunctionTest,
       Check_str_empty_after_flush_PermutationStringWriter) {

    int r, n, N, Z;
    r = 2;          // selection
    n = 9;          // sampling grid, 1D
    N = pow(n,2.0); // sampling grid, 2D
    Z = (N-1)*N/2;  // # of possible combinations (w/reverse)

    // Prepare selection vector
    std::vector<int> v(N);
    std::iota(v.begin(), v.end(), 0);

    auto output_file = getSetFilename(n,Z) + "-test";
    PermutationStringWriter *writer =
        new PermutationStringWriter(output_file);

    writer->addPermutation("");
    writer->flushToDisk();

    // Compute combinations: prints to disk after each combination
//    std::uint64_t count =
//        for_each_reversible_permutation(
//            v.begin(),
//            v.begin() + r,
//            v.end(),
//            f_at_each_combination(v.size(), writer));

// check


}


}
