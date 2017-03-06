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

#include "../../CombinationSets/src/permutation_string_writer.h"
#include "../../CombinationSets/src/utilities.hpp"
#include "../../../../FieldOpt/FieldOpt/Utilities/filehandling.hpp"

#ifndef COMPLEMENTSETS_COMBINATION_SET_H
#define COMPLEMENTSETS_COMBINATION_SET_H

using namespace std;
using namespace Utilities::FileHandling;

struct intersection_SetB_SetA {
  vector<int> intersect_rows_fSuperSetB;
  vector<int> intersect_rows_fSubSetA;
  bool remove_intersected_rows = true;
};

struct debug_colors {
  string cbr = "\033[1;31m";
  string cbg = "\033[1;32m";
  string cbm = "\033[1;35m";
  string ce = "\033[0m";
};

class CombinationSet {

 private:
  QStringList *fSet_str_;

 public:
  CombinationSet(QString file_path){
      fSet_str_ = ReadFileToStringList(file_path);
  };

  int get_fSet_size(){
      return fSet_str_->size();
  }

  QString get_combination_str(int i){
      return fSet_str_->at(i) + "\n";
  }

  vector<int> get_combination_int(int i){
      vector<int> fSet_comb (2);
      fSet_comb.at(0) = fSet_str_->at(i).split(" ")[0].toInt();
      fSet_comb.at(1) = fSet_str_->at(i).split(" ")[1].toInt();
      return fSet_comb;
  }

  bool find_fSubSet_intersect(vector<int> fSuperSet_combination,
                              intersection_SetB_SetA *iSetBSetA){

      // Forward and reverse intersecting rows b/e the two sets
      bool FWR_INTERSECT = false;
      // bool REV_INTERSECT = false; // [Save for ref]

      // Loop through all rows of fSubSet (the logic in this
      // function defines 'this' current object as the fSubSet)
      // This logic extends beyond this function and applies to
      // the entire object if the option to remove the intersected
      // rows from the original set is ON.
      cout << "Number of rows in fSubSet: "
           << this->get_fSet_size() << endl;

      for (int j = 0; j < this->get_fSet_size(); ++j) {

          auto current_fSubSet_combination = this->get_combination_int(j);

          // Define logic variables
          auto SUB_L = current_fSubSet_combination[0];
          auto SUB_R = current_fSubSet_combination[1];

          auto SUPER_L = fSuperSet_combination[0];
          auto SUPER_R = fSuperSet_combination[1];

          // Perform logic
          FWR_INTERSECT = (SUB_L == SUPER_L)
              && (SUB_R == SUPER_R);

          // debug
          print_test(j, SUB_L, SUB_R,
                     SUPER_L, SUPER_R,
                     FWR_INTERSECT);

          // [Save for ref]
          // REV_INTERSECT = (SUB_L == SUPER_R)
          //    && (SUB_R == SUPER_L);

          // debug [Save for ref]
          //print_test(j, SUB_L, SUB_R,
          //           SUPER_R, SUPER_L,
          //           REV_INTERSECT);

          // Return
          if (FWR_INTERSECT){ // || REV_INTERSECT [Save for ref]

              // Remove intersected row such that subsequent searches
              // for equal combinations loop over a smaller combination
              // subset. This is doable since we know both the super and
              // the subset contain only unique elements.
              //
              // This reduced size of the subset should improve the overall
              // efficiency of building the complement set, however, proper
              // unit test are needed to comfirm/quantify the postulated
              // performance increase. \todo
              if (iSetBSetA->remove_intersected_rows){

                  // Note: the j index is only accurate with respect to
                  // the original fSubSetA row index if the remove row
                  // option is false. Invalid number is set to -1.
                  iSetBSetA->intersect_rows_fSubSetA.push_back(j);

                  // remove element
                  this->fSet_str_->removeAt(j);
                  cout << "=> removed row " << j+1
                       << "; subset now has "
                       << this->get_fSet_size() << " rows.\n";
              }else{
                  iSetBSetA->intersect_rows_fSubSetA.push_back(-1);
              }
              return true;
          }
      }
      return false;
  }

  void print_test(int j, int a, int b, int c, int d, bool T){
      cout << "\tTesting row " << j+1
           << " of subset: (" << a << " vs " << b
           << ") against (" << c << " vs " << d << ")"
           << "-> true? [" << T << "]\n";
  }

};

#endif //COMPLEMENTSETS_COMBINATION_SET_H
