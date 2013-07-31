/*
 * FileSmat.h
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */
 
#ifndef FILESMAT_H
#define FILESMAT_H

#include "FileGeneral.h"

#include <vector>
#include <string>
#include <Eigen/Core>

/// class FileSmat - 
class FileSmat : public FileGeneral {
  // Operations
public:
  FileSmat (std::string fn);
  ~FileSmat ();
  void read (std::vector<Eigen::MatrixXcd>& S);
};

#endif
