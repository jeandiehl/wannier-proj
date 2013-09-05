/*
 * FileKlist.h
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#ifndef FILEKLIST_H
#define FILEKLIST_H

#include "FileGeneral.h"

#include <iostream>
#include <vector>
#include <complex>
#include <Eigen/Core>

class FileKlist : public FileGeneral {

private:

protected:

public:
  FileKlist(std::string fn);
  ~FileKlist();

  void read(std::vector<Eigen::Vector3d>& kpoints);
};

#endif
