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
#include <QFileInfo>
#include <QTextStream>
#include <QDateTime>

#include "src/permutation_string_writer.h"
#include "src/f_at_each_combination.h"
#include "src/for_each_combination.h"
#include "src/utilities.hpp"

using namespace std;

// ============================================================
QString compute_combinations(int r, int n, int N, int Z,
                             QString &log_file){

    // ------------------------------------------------------------
    // Print to log: date, hostname, cpu info, combination set info
    auto t_start = printToLog(r, n, N, Z, log_file);

    // ------------------------------------------------------------
    // Prepare selection vector
    std::vector<int> v(N);
    std::iota(v.begin(), v.end(), 1); // Notice we're starting from 1

    // ------------------------------------------------------------
    // Prepare output file and and permutation writer
    auto output_file = getSetFilename(n,Z);
    PermutationStringWriter *writer =
        new PermutationStringWriter(output_file);

    // ------------------------------------------------------------
    // Compute combinations: prints to disk after each combination
    std::uint64_t count =
        for_each_reversible_permutation(
            v.begin(),
            v.begin() + r,
            v.end(),
            f_at_each_combination(v.size(), writer));

    // ------------------------------------------------------------
    // Flush remaining data, if any
    if (writer->temp_str_.size()>0)
        writer->flushToDisk();

    // ------------------------------------------------------------
    // Print to log: file size + elapsed time
    Utilities::FileHandling::WriteLineToFile(
        getFileSize(output_file) + get_elapsed_time(t_start),
        log_file);

    // ------------------------------------------------------------
    // Sanity check
    // assert(count == count_each_reversible_permutation(v.begin(),
    //                                                   v.begin() + r,
    //                                                   v.end()));

    // ------------------------------------------------------------
    // Summary
    // std::cout << "Found " << count << " permutations of " << v.size()
    //           << " objects taken " << r << " at a time.\n\n";

    return output_file;
}


// ============================================================
int main() {

    // --------------------------------------------------------
    // log file name
    auto log_file = getLogName();

    /*
         => # points| Set | # of combinations
         => N = n^2 |  |  | Z = (N-1)*N/2
    % TEST SPACES   |  v  |
    n002 =>     4   |     | 6
    n003 =>     9   |     | 36
    n009 =>    81   |     | 3240
    % SUBSPACES: 40|80|100
    n040 =>  1600   | {A} | 1279200   ~=   1.3*1e6
    n080 =>  6400   | {B} | 20476800  ~=  20.5*1e6
    n100 => 10000   | {C} | 49995000  ~=  50.0*1e6
    % SUBSPACES: 120|140|160
    n120 => 14400   | {D} | 103672800 ~= 103.7*1e6
    n140 => 19600   | {E} | 192070200 ~= 192.1*1e6
    n160 => 25600   | {F} | 327667200 ~= 327.7*1e6
    % SUBSPACES: 180|190|200
    n180 => 32400   | {G} | 524863800 ~= 524.9*1e6
    n190 => 36100   | {H} | 651586950 ~= 651.6*1e6
    n200 => 40000   | {I} | 799980000 ~= 800.0*1e6
    */

    int r, n, N, Z;

    // --------------------------------------------------------
    // TEST SPACE: n002
    // Select combination attributes:
    r = 2;          // selection
    n = 2;          // sampling grid, 1D
    N = pow(n,2.0); // sampling grid, 2D
    Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
    compute_combinations(r, n, N, Z, log_file);

    // --------------------------------------------------------
    // TEST SPACE: n003
    // Select combination attributes
    r = 2;          // selection
    n = 3;          // sampling grid, 1D
    N = pow(n,2.0); // sampling grid, 2D
    Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
    compute_combinations(r, n, N, Z, log_file);

    // --------------------------------------------------------
    // TEST SPACE: n009
    // Select combination attributes
    r = 2;          // selection
    n = 9;          // sampling grid, 1D
    N = pow(n,2.0); // sampling grid, 2D
    Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
    compute_combinations(r, n, N, Z, log_file);

    // --------------------------------------------------------
    // SET {A}: n040
    // Select combination attributes
    r = 2;          // selection
    n = 40;         // sampling grid, 1D
    N = pow(n,2.0); // sampling grid, 2D
    Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
    compute_combinations(r, n, N, Z, log_file);

    if( startPrompt(1)==1 ){

        // --------------------------------------------------------
        // SET {B}: n080
        // Select combination attributes
        r = 2;          // selection
        n = 80;         // sampling grid, 1D
        N = pow(n,2.0); // sampling grid, 2D
        Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
        compute_combinations(r, n, N, Z, log_file);

        // --------------------------------------------------------
        // SET {C}: n100
        // Select combination attributes
        r = 2;          // selection
        n = 100;        // sampling grid, 1D
        N = pow(n,2.0); // sampling grid, 2D
        Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
        compute_combinations(r, n, N, Z, log_file);

        // --------------------------------------------------------
        // SET {D}: n120
        // Select combination attributes
        r = 2;          // selection
        n = 120;        // sampling grid, 1D
        N = pow(n,2.0); // sampling grid, 2D
        Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
        compute_combinations(r, n, N, Z, log_file);

        // --------------------------------------------------------
        // SET {E}: n140
        // Select combination attributes
        r = 2;          // selection
        n = 140;        // sampling grid, 1D
        N = pow(n,2.0); // sampling grid, 2D
        Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
        compute_combinations(r, n, N, Z, log_file);

        // --------------------------------------------------------
        // SET {F}: n160
        // Select combination attributes
        r = 2;          // selection
        n = 160;        // sampling grid, 1D
        N = pow(n,2.0); // sampling grid, 2D
        Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
        compute_combinations(r, n, N, Z, log_file);

        // --------------------------------------------------------
        // SET {G}: n180
        // Select combination attributes
        r = 2;          // selection
        n = 180;        // sampling grid, 1D
        N = pow(n,2.0); // sampling grid, 2D
        Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
        compute_combinations(r, n, N, Z, log_file);

        // --------------------------------------------------------
        // SET {H}: n190
        // Select combination attributes
        r = 2;          // selection
        n = 190;        // sampling grid, 1D
        N = pow(n,2.0); // sampling grid, 2D
        Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
        compute_combinations(r, n, N, Z, log_file);

        // --------------------------------------------------------
        // SET {I}: n200
        // Select combination attributes
        r = 2;          // selection
        n = 200;        // sampling grid, 1D
        N = pow(n,2.0); // sampling grid, 2D
        Z = (N-1)*N/2;  // # of possible combinations (w/reverse)
        compute_combinations(r, n, N, Z, log_file);

    }

    return 0;
}