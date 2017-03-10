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

#ifndef COMBINATIONSETS_SAMPLE_POINT_RANGES_H
#define COMBINATIONSETS_SAMPLE_POINT_RANGES_H

#include <vector>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// ============================================================
/*!
 * \brief
 */
class sample_point_ranges
{

 private:

  int p_, r_, n_, N_, Z_;

  int main_grid_n_;

  Matrix<int,Dynamic,Dynamic> v_ranges_;
  Matrix<int,Dynamic,Dynamic> range_vec_;
  bool debug=false;

 public:

  vector<int> range_vec_std_;

  explicit sample_point_ranges(int p, int r, int n, int N, int Z);

  /*!
   * \brief
   * \param
   * \return
   */
  vector<int> get_sample_point_ranges();

  /*!
   * \brief
   * \param
   * \return
   */
  bool debug_get_check_main_grid_n(){return main_grid_n_;};

};

#endif //COMBINATIONSETS_SAMPLE_POINT_RANGES_H
