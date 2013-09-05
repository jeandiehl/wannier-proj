/*
 * WannierFunctionCalculator.h
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#ifndef WANNIERFUNCTIONCALCULATOR_H
#define WANNIERFUNCTIONCALCULATOR_H

#include <iostream>
#include <vector>
#include <complex>
#include <Eigen/Core>
#include <cmath>

#include "WaveFunction.h"
#include "Projector.h"
#include "KSymmSum.h"

class WannierFunctionCalculator {

private:

protected:

public:
  WannierFunctionCalculator();
  ~WannierFunctionCalculator();
  void calculate(double vol, std::vector<Eigen::Vector3d>& kpoints, std::vector<std::vector<Eigen::Vector3d> >& atomPositions, Projector& proj, WaveFunction& psi, WaveFunction& wannier);
};

#endif
