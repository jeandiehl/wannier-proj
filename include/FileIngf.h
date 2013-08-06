/*
 * FileIngf.h
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#ifndef FILEINGF_H
#define FILEINGF_H

#include "FileGeneral.h"

#include <iostream>
#include <vector>
#include <complex>

class FileIngf : public FileGeneral {

private:

protected:

public:
  FileIngf(std::string fn);
  ~FileIngf();

  void read(double& emin, double& emax, double& de, double& eta);
};

#endif
