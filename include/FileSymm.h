/*
 * FileSymm.h
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#ifndef FILESYMM_H
#define FILESYMM_H

#include "FileGeneral.h"

#include <iostream>
#include <vector>
#include <complex>
#include <Eigen/Core>


class FileSymm : public FileGeneral {

private:

protected:

public:
  FileSymm(std::string fn);
  ~FileSymm();
	
  void read(std::vector<std::vector<Eigen::MatrixXcd> >& Symm, std::vector<std::vector<int> >& alpha, std::vector<std::string>& atomNames);
  int getAtomIndex(std::string atomName, std::vector<std::string>& atomNames);
};

#endif
