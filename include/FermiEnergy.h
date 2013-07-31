/*
 * FermiEnergy.h
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */
 
#ifndef FERMIENERGY_H
#define FERMIENERGY_H

#include "FileGeneral.h"

#include <vector>
#include <string>
#include <Eigen/Core>

/// class FermiEnergy - 
class FermiEnergy : public FileGeneral {
  // Operations
public:
  FermiEnergy (std::string fn);
  ~FermiEnergy ();
  void read (double& EF);
};

#endif
