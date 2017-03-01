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

#include "src/for_each_permutation.h"
#include "src/utilities.hpp"
#include "../../../FieldOpt/FieldOpt/Utilities/filehandling.hpp"


using namespace std;

// ============================================================
class f_at_each_combination
{
  unsigned len;
  std::uint64_t count;
  QString file_path;

 public:

  explicit f_at_each_combination(unsigned l, QString file_path_) : len(l), count(0) {
      file_path = file_path_;
      Utilities::FileHandling::CreateFile(file_path, true);
  }

  operator std::uint64_t() const {return count;}

  template <class It> bool operator()(It first, It last)
  {
      ++count;
      QString str;

      if (first != last)
      {
          str = QString::number(*first);
          for (++first; first != last; ++first)
          {
              str = str + " " + QString::number(*first);
          }
      }
      // \todo Collect all data into one str, then call WriteLineToFile
      // only once. ?? >> This can only be done after the main function
      // has stopped calling iter_func.operator(), which means we may
      // have to implement at the template level of the main function.
      // Whether to do this depends on whether there is a performance
      // gain from avoiding setting up the file pointer and printing to
      // disc for each combination, in compasison to storing all
      // combinations into one large string, and only print to disc
      // at the end of this process
      Utilities::FileHandling::WriteLineToFile(str, file_path);
      return false;
  }
};



// ============================================================
int main() {

    // --------------------------------------------------------
    // Select combination attributes
    const int r = 2;   // selection
    const int n = 9;   // sampling grid, 1D
    const int N = pow(n,2.0); // sampling grid, 2D
    const int Z = (N-1)*N/2; // # of possible combinations (w/reverse)

    std::vector<int> v(N);
    std::iota(v.begin(), v.end(), 0);

    auto file_path = getSetFilename(n,Z);

    // ------------------------------------------------------------
    // Print to log
    auto host_str = getHostname();
    QString log_file = "../../combinations/runtimes-" + host_str[0] + ".log";
    std::cout << "selection, r = " << r << std::endl
              << "sampling grid (1D), n = " << n << std::endl
              << "sampling grid (2D), N = n^2 = " << N << std::endl
              << "# of combinations (reverse), Z = (N-1)*N/2 = " << Z << std::endl;

    auto t_start = QDateTime::currentDateTime();
    print_to_log(log_file, t_start, file_path);

    // ------------------------------------------------------------
    // Find combinations

    std::uint64_t count =
        for_each_reversible_permutation(v.begin(),
                                        v.begin() + r,
                                        v.end(),
                                        f_at_each_combination(v.size(),file_path));

    auto elapsed_time = get_elapsed_time(t_start);
    Utilities::FileHandling::WriteLineToFile(elapsed_time, log_file);

    // ------------------------------------------------------------
    // Sanity check
    assert(count == count_each_reversible_permutation(v.begin(),
                                                      v.begin() + r,
                                                      v.end()));

    // ------------------------------------------------------------
    // Summary
    std::cout << "Found " << count << " permutations of " << v.size()
              << " objects taken " << r << " at a time.\n\n";



}