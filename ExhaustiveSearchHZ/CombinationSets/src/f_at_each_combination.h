/******************************************************************************

   ?????

   Original copyright from (C) Copyright Howard Hinnant 2005-2011.
   Use, modification and distribution are subject to the Boost Software
   License, Version 1.0.

   ?????
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

#ifndef COMBINATIONSETS_F_AT_EACH_COMBINATION_H
#define COMBINATIONSETS_F_AT_EACH_COMBINATION_H

#include "../../../../FieldOpt/FieldOpt/Utilities/filehandling.hpp"

using namespace std;


// ============================================================
class f_at_each_combination
{
  unsigned len;
  std::uint64_t count;

 private:
  QString file_path;
  QStringList *str_TEST;
 public:

  explicit f_at_each_combination(unsigned l,
                                 QString file_path_,
                                 QStringList *str_TEST_) : len(l), count(0) {
      file_path = file_path_;
      str_TEST = str_TEST_;
      std::cout << "helloe" << std::endl;
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
      // disc for each combination, in comparison to storing all
      // combinations into one large string, and only print to disc
      // at the end of this process
//      Utilities::FileHandling::WriteLineToFile(str, file_path);

      str_TEST_ << str;
      for (int i = 0; i < str_TEST.size(); ++i)
          std::cout << str_TEST[i].toStdString() << std::endl;
      return false;
  }
};

#endif //COMBINATIONSETS_F_AT_EACH_COMBINATION_H
