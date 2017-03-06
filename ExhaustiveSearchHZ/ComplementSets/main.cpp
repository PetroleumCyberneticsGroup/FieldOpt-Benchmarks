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

#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDateTime>
#include "src/combination_set.h"

#include "../CombinationSets/src/permutation_string_writer.h"
#include "../CombinationSets/src/utilities.hpp"

using namespace std;

int main() {

    QString fSubSetA_file = "n002-Z6E+00_cpp.fSet";
    QString fSuperSetB_file = "n003-Z4E+01_cpp.fSet";

    QString dir = "../../../CombinationSets/combinations/fSets-cpp";
    QString fSubSetA_path = dir + "/" + fSubSetA_file;
    QString fSuperSetB_path = dir + "/" + fSuperSetB_file;

    QString cSetC_path = getcSetFilename(fSuperSetB_file, fSubSetA_file);
    PermutationStringWriter *writer =
        new PermutationStringWriter(cSetC_path);

    CombinationSet *fSubSetA = new CombinationSet(fSubSetA_path);
    CombinationSet *fSuperSetB = new CombinationSet(fSuperSetB_path);

    debug_colors clrs;

    cout << clrs.cbr << "Building complement set C = B \\ A" << clrs.ce << endl;
    cout << clrs.cbr << "Size of subset A: "
         << fSubSetA->get_fSet_size() << clrs.ce << endl;
    cout << clrs.cbr << "Size of superset B: "
         << fSuperSetB->get_fSet_size() << clrs.ce << endl;

    intersection_SetB_SetA *iSetBSetA = new intersection_SetB_SetA;

    // Check each row of superset B against all row of subset A
    // size(B) > size(A)
    for (int i = 0; i < fSuperSetB->get_fSet_size(); ++i) {

        cout << "Checking superset B row " << i + 1 << " out of "
             << fSuperSetB->get_fSet_size() << " rows." << endl;
        // Combination i (row i) from superset B becomes an element (row)
        // in complement set C = B\A (cSetBnotA) if an equal row (or its
        // reverse row [test: this is strictly not necessary since no
        // reverse rows exist within each set -- however, they could
        // potentially exist equal-reverse between the sets]) is NOT
        // found in subset A.
        auto intersect = fSubSetA->find_fSubSet_intersect(
            fSuperSetB->get_combination_int(i), iSetBSetA);

        if (intersect) {
            // Note: the intersect_rows_fSubSetA.back() index is only
            // accurate with respect to the original fSubSetA row index
            // if the remove row option is false.
            iSetBSetA->intersect_rows_fSuperSetB.push_back(i);
            cout << "Intersect summary: row " << i + 1
                 << " in superset B is equal to row "
                 << iSetBSetA->intersect_rows_fSubSetA.back() + 1
                 << " in subset A.\n";
        } else {
            // add combination to writer
            writer->addPermutation(fSuperSetB->get_combination_str(i));
        }
    }

    if (writer->temp_str_.size()>0)
        writer->flushToDisk();

    return 0;
}
