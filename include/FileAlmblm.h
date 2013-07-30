/*
 * FileAlmblm.h
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#ifndef FILEALMBLM_H
#define FILEALMBLM_H

#include "FileGeneral.h"
#include "GeneralCoefficient.h"

#include <string>
#include <complex>
#include <Eigen/Core>
#include <iostream>
#include <sstream>

/// class FileAlmblm - 
class FileAlmblm : public FileGeneral {
  // Operations
public:
  FileAlmblm (std::string fn);
  ~FileAlmblm ();
  void read (GeneralCoefficient<std::complex<double> >& Alm, GeneralCoefficient<Eigen::VectorXcd>& Clm, GeneralCoefficient<Eigen::VectorXcd>& O);

};

#endif
