/******************************************************************************

   Copyright (C) 2017 Mathias C. Bellout <mathias.bellout@ntnu.no>

   This file is part of the FieldOpt-Benchmarks project,
   an NTNU Petroleum Cybernetics Group project.

   ?????
   HOW DO WE DO THIS...
   This class builds upon class f by Howard Hinnant 2005-2011.
   Use, modification and distribution are subject to the Boost
   Software License, Version 1.0.
   ?????

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

/*!
 * \brief
 */
class f_at_each_combination
{
  unsigned len;
  std::uint64_t count;

 public:
  PermutationStringWriter *writer_;

  explicit
  f_at_each_combination(
      unsigned l, PermutationStringWriter *writer) : len(l), count(0) {
      writer_ = writer;
  }


  operator std::uint64_t() const {return count;}

  /*!
   * \brief
   * \param
   * \return
   */
  template <class It> bool operator()(It first, It last)
  {
      ++count;
      QString perm_str;

      if (first != last)
      {
          perm_str = QString::number(*first);
          for (++first; first != last; ++first)
          {
              perm_str = perm_str + " " + QString::number(*first) + "\n";
          }
      }
      writer_->addPermutation(perm_str);

      return false;
  }
};

#endif //COMBINATIONSETS_F_AT_EACH_COMBINATION_H
