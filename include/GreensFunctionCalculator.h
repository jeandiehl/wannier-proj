/*
 * GreensFunctionCalculator.h
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#ifndef GREENSFUNCTIONCALCULATOR_H
#define GREENSFUNCTIONCALCULATOR_H

#include <iostream>
#include <vector>
#include <complex>
#include <Eigen/Core>

#include "GreensFunction.h"

class GreensFunctionCalculator {

private:
  double const static RyEv = 13.60569253;
protected:
  double emin;
  double emax;
  double de;
  double eta;

public:
  GreensFunctionCalculator(double eemin, double eemax, double dde, double eeta);
  ~GreensFunctionCalculator();

  void calculate(GreensFunction& gf, std::vector<std::vector<double> >& energy, double EF);

  std::complex<double> calculateNoninteractingGF(double e, double enu, double EF);
};

#endif
