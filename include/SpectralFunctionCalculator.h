/*
 * SpectralFunctionCalculator.h
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#ifndef SPECTRALFUNCTIONCALCULATOR_H
#define SPECTRALFUNCTIONCALCULATOR_H

#include <iostream>
#include <vector>
#include <complex>

#include "SpectralFunction.h"
#include "GreensFunction.h"

class SpectralFunctionCalculator {

private:

protected:

public:
  SpectralFunctionCalculator();
  ~SpectralFunctionCalculator();
  
  void calculate(SpectralFunction& sf, GreensFunction& gf) ;

};

#endif
