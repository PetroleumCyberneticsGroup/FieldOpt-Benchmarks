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

#ifndef COMBINATIONSETS_SAMPLE_POINT_RANGES_CPP
#define COMBINATIONSETS_SAMPLE_POINT_RANGES_CPP

#include <vector>
#include <iostream>
#include <Eigen/Dense>
#include "sample_point_ranges.h"

using namespace std;
using namespace Eigen;

sample_point_ranges::sample_point_ranges(
    int p, int r, int n, int N, int Z){
    p_=p;
    r_=r;
    n_=n;
    N_=N;
    Z_=Z;
};

vector<int> sample_point_ranges::get_sample_point_ranges(){

    // ------------------------------------------------------------
    // Prepare range vector of points, i.e., subspace within overall
    // point grid
    if (p_ > 1) {

        v_ranges_.resize(n_,r_);
        v_ranges_.fill(0);

        // square point grid selection size n x n
        range_vec_.resize(n_,n_);
        range_vec_.fill(0);

        // define first row endpoints
        main_grid_n_ = (n_+2*p_);
        v_ranges_(0,0) = (p_+1) + (p_+1) * main_grid_n_;
        v_ranges_(0,1) = v_ranges_(0,0) + (n_-1);

        // make linearly spaced vector using row endpoints
        // use LinSpaced(size, low, high) (similar to MATLAB's
        // low:step:high); see AsciiQuickReference.txt
        range_vec_.row(0) = VectorXi::LinSpaced(n_,
                                                v_ranges_(0,0),
                                                v_ranges_(0,1));

        // find endpoints for subsequent rows
        for (int i=1; i < n_; ++i){
            v_ranges_(i,0) = v_ranges_(i-1,1) + 2*p_ + 1;
            v_ranges_(i,1) = v_ranges_(i,0) + (n_-1);

            // make linearly spaced vector using row endpoints
            range_vec_.row(i) = VectorXi::LinSpaced(n_,
                                                    v_ranges_(i,0),
                                                    v_ranges_(i,1));
        }

        // convert to column vector
        range_vec_.resize(N_,1);

        // ------ MATLAB CODE: keep for ref. ------
        // % make first subgrid / region row
        // a(1) = p + 1 + (p + 1) * (n + 2 * p);
        // % remember: n + 2 * p = main_n = n201
        // b(1) = a(1) + (n - 1);

        // % fill in:
        // T(1,:) = [ a(1) b(1) ];
        // s(1) = {T(1, 1) : T(1, 2)};

        // % iterate for each region row, global indexing top to bottom
        // for ii = 2 : n
        //     a(ii) = b(ii - 1) + 2 * p + 1;
        //     b(ii) = a(ii) + (n - 1);

        //     % fill in:
        //     T(ii,:) = [a(ii) b(ii)];
        //     s(ii) = {T(ii, 1) : T(ii, 2)};
        // end

    }else{

        // For selection ranges starting from corner point (1,1)
        range_vec_.resize(N_,1);
        range_vec_.col(0) = VectorXi::LinSpaced(N_, p_, N_);
        // Notice we're starting from p which is effectively 1
        // for the cases that enter this part of the loop

    }

    // map Eigen to std vector
    range_vec_std_.resize((ulong)range_vec_.size()); // eigen_v to std_v
    Matrix<int,Dynamic,1>::Map(&range_vec_std_[0], range_vec_.size()) = range_vec_;

    // std_v to eigen_v (keep for ref.)
    // Array<int,Dynamic,1> eigen_v = Map<Array<int,Dynamic,1>>(v.data(), v.size());

    // debug
    if (debug){
        cout << "\n=> v_ranges.size(): "
             << v_ranges_.size() << endl;
        cout << v_ranges_;

        cout << "\n=> range_vec.size(): "
             << range_vec_.size() << endl;
        cout << range_vec_;
    }

    return range_vec_std_;

}

#endif //COMBINATIONSETS_SAMPLE_POINT_RANGES_CPP







