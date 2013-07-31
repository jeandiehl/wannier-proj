/*
 * FileRot.h
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */
 
#ifndef FILEROT_H
#define FILEROT_H

#include "FileGeneral.h"

#include <vector>
#include <string>
#include <Eigen/Core>

/// class FileRot - 
class FileRot : public FileGeneral {
  // Operations
public:
  FileRot (std::string fn);
  ~FileRot ();
  void read (std::vector<Eigen::MatrixXcd>& R);
};

#endif
