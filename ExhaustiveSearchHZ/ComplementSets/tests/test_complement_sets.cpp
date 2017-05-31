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

#include "../../CombinationSets/src/utilities.hpp"

#include "../../../../FieldOpt/FieldOpt/Utilities/filehandling.hpp"
#include "../../../../FieldOpt/FieldOpt/Utilities/time.hpp"

#include <gtest/gtest.h>

using namespace Utilities::FileHandling;


namespace {

class complementSetsTest : public ::testing::Test {
 protected:
  complementSetsTest() {
  };

  virtual ~complementSetsTest() {}

  virtual void SetUp() {}

  virtual void TearDown() {}

};

TEST_F(complementSetsTest, Test_complementSetCreation) {

// test size of complement set (C) is equal to sum of
// superset (B) and subset (A)

}

}