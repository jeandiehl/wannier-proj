/*
 * Projector.h
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#ifndef PROJECTOR_H
#define PROJECTOR_H

#include "GeneralCoefficient.h"

#include <Eigen/Core>
#include <iostream>
#include <complex>
#include <iomanip> // setw

/// class Projector -

class Projector {
  // Attributes
protected:
  std::vector<Eigen::MatrixXcd> proj;

  std::vector<std::vector<int> > energyIndex;
  std::vector<std::vector<std::vector<std::vector<int> > > > combinedIndex;

  std::vector<int> combinedIndexJAtom;
  std::vector<int> combinedIndexAtom;
  std::vector<int> combinedIndexL;
  std::vector<int> combinedIndexM;
  // Operations
public:
  Projector ();
  ~Projector ();

  void initialize(std::vector<std::vector<std::vector<std::vector<int> > > > combIndex, std::vector<std::vector<int> > energyInd, std::vector<int> combIndexJAtom, std::vector<int> combIndexAtom, std::vector<int> combIndexL, std::vector<int> combIndexM);
  void set(int i, int j, int ikpoints, std::complex<double> value);
  void set(int ikpoints, Eigen::MatrixXcd P);
  Eigen::MatrixXcd get(int ikpoints);

  int getMaxKpoints();
  std::vector<std::vector<int> > getCombinedIndex();
  std::vector<std::vector<int> > getEnergyIndex();

  int getMaxCombinedIndex();
  
  friend std::ostream& operator<<(std::ostream& Stream, Projector& P);
  friend std::istream& operator>>(std::istream& Stream, Projector& Proj);
};

#endif
