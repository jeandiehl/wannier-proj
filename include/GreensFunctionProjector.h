/*
 * GreensFunctionProjector.h
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#ifndef GREENSFUNCTIONPROJECTOR_H
#define GREENSFUNCTIONPROJECTOR_H

#include <iostream>
#include <vector>
#include <complex>
#include <iomanip>

#include "GreensFunction.h"
#include "Projector.h"
#include <Eigen/Core>

class GreensFunctionProjector {

private:

protected:

public:
  GreensFunctionProjector();
  ~GreensFunctionProjector();

  void calculate(GreensFunction& gf, GreensFunction& gfproj, Projector& proj);

};

#endif
