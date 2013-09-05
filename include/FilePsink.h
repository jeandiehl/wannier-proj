/*
 * FilePsink.h
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#ifndef FILEPSINK_H
#define FILEPSINK_H

#include "FileGeneral.h"

#include <iostream>
#include <vector>
#include <complex>
#include <Eigen/Core>

#include "WaveFunction.h"

class FilePsink : public FileGeneral {

private:
  Eigen::Vector3d Nspace;
  int NspaceTotal;
protected:

public:
  FilePsink(std::string fn);
  ~FilePsink();

  void read(WaveFunction& psi);
  void initialize(Eigen::Vector3d NNspace);
};

#endif
