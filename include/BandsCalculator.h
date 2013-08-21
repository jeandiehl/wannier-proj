/*
 * BandsCalculator.h
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#ifndef BANDSCALCULATOR_H
#define BANDSCALCULATOR_H

#include <iostream>
#include <vector>
#include <complex>
#include <Eigen/Core>

#include "Bands.h"
#include "GreensFunction.h"

class BandsCalculator {

private:

protected:

public:
  BandsCalculator();
  ~BandsCalculator();

  void calculate(Bands& bands, GreensFunction& gf);

};

#endif
