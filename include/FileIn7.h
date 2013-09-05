/*
 * FileIn7.h
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#ifndef FILEIN7_H
#define FILEIN7_H

#include "FileGeneral.h"

#include <iostream>
#include <vector>
#include <complex>
#include <Eigen/Core>

class FileIn7 : public FileGeneral {

private:

protected:

public:
  FileIn7(std::string fn);
  ~FileIn7();

  void read(Eigen::Vector3d& Nspace);
  void read(Eigen::Vector3d& Nspace, std::vector<Eigen::Vector3d >& selectedCell);
};

#endif
