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
#include <iomanip>
#include <complex>

/// class ProjectorCalculator - 
class ProjectorCalculator {
private:
  double Emin;
  double Emax;
  double const static RyEv = 13.60569253;
  
  std::vector<std::vector<std::vector<int > > > selectedOrbitals;
  std::vector<std::vector<int> > selectedEnergies;
  std::vector<int> multiplicities;
  
  std::vector<std::vector<int> > energyIndex;
  std::vector<std::vector<std::vector<std::vector<int> > > > combinedIndex;

  std::vector<int> combinedIndexJAtom;
  std::vector<int> combinedIndexAtom;
  std::vector<int> combinedIndexL;
  std::vector<int> combinedIndexM;

  Eigen::MatrixXcd U;
  // Operations

  void getSelectedEnergies(std::vector<std::vector<double> >& energy, double EF);
  void generateUMatrix(std::vector<Eigen::MatrixXcd>& R, std::vector<Eigen::MatrixXcd>& S, Eigen::MatrixXcd& U);
  void initialize();
public:
  ProjectorCalculator (double Emin, double Emax, std::vector<std::vector<std::vector<int > > > selOrb, std::vector<std::vector<double> >& energy, std::vector<int>& mult, double EF);
  ~ProjectorCalculator ();
  void calculate (GeneralCoefficient<std::complex<double> >& Alm, GeneralCoefficient<Eigen::VectorXcd>& Clm, GeneralCoefficient<Eigen::VectorXcd>& O, std::vector<Eigen::MatrixXcd>& R, std::vector<Eigen::MatrixXcd>& S, Projector& Proj, Projector& ProjTilde);
  

};

#endif
