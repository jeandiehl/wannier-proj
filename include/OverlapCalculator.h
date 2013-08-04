/*
 * OverlapCalculator.h
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#ifndef OVERLAPCALCULATOR_H
#define OVERLAPCALCULATOR_H


#include <Eigen/Core>
#include <iostream>
#include <complex>
#include "Projector.h"
#include "Overlap.h"

/// class OverlapCalculator - 
class OverlapCalculator {

private:
  int Nkpoints;
  // Operations
public:
  OverlapCalculator ();
  ~OverlapCalculator ();
  void calculate(Projector& P, Overlap& O);
};

#endif
