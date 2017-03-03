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

#ifndef COMBINATIONSETS_PERMUTATION_STRING_WRITER_H
#define COMBINATIONSETS_PERMUTATION_STRING_WRITER_H

#include <iostream>
#include "../../../../FieldOpt/FieldOpt/Utilities/filehandling.hpp"

using namespace std;

class PermutationStringWriter {

 public:
  QString temp_str_;

 private:
  QString file_path_;
  int perms_in_str_;
  int perms_pr_file_limit_ = 25e6;

 public:
  PermutationStringWriter(QString file_path){
      file_path_ = file_path;
      Utilities::FileHandling::CreateFile(file_path_, true);
  };

  void addPermutation(QString perm_str){
      temp_str_ += perm_str;
      ++perms_in_str_;
      if(perms_in_str_ > perms_pr_file_limit_){
          flushToDisk();
          perms_in_str_ = 0;
      }
  };

  void flushToDisk(){
      Utilities::FileHandling::WriteLineToFile(temp_str_,
                                               file_path_);
      temp_str_ = ""; // reset temp str
  }
};

#endif //COMBINATIONSETS_PERMUTATION_STRING_WRITER_H
