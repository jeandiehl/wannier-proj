/*
 * ProjectorCalculator.h
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#ifndef PROJECTORCALCULATOR_H
#define PROJECTORCALCULATOR_H

#include "Projector.h"

#include <vector>
#include <Eigen/Core>
#include <iostream>

/// class ProjectorCalculator - 
class ProjectorCalculator {
private:
  double Emin;
  double Emax;
  double const static RyEv = 13.60569253;
  
  std::vector<std::vector<std::vector<int > > > selectedOrbitals;
  std::vector<std::vector<int> > selectedEnergies;
  
  std::vector<std::vector<int> > energyIndex;
  std::vector<std::vector<std::vector<std::vector<int> > > > combinedIndex;
  // Operations

  void getSelectedEnergies(std::vector<std::vector<double> >& energy, double EF);
public:
  ProjectorCalculator (double Emin, double Emax, std::vector<std::vector<std::vector<int > > > selOrb, std::vector<std::vector<double> >& energy, double EF);
  ~ProjectorCalculator ();
  void calculate (GeneralCoefficient<std::complex<double> >& Alm, GeneralCoefficient<Eigen::VectorXcd>& Clm, GeneralCoefficient<Eigen::VectorXcd>& O, Projector& Proj, Projector& ProjTilde);
};

#endif
