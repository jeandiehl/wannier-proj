/*
 * SpectralFunction.h
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#ifndef SPECTRALFUNCTION_H
#define SPECTRALFUNCTION_H

#include <iostream>
#include <vector>
#include <complex>
#include <iomanip> // setw

#include <Eigen/Core>

class SpectralFunction {

private:
  std::vector<Eigen::MatrixXd > SF;

protected:
  double emin;
  double emax;
  double de;
  int Ne;
  
  std::vector<std::vector<int> > combIndex;

  std::vector<std::string> kpath;
  std::vector<int> kpathIndex;

public:
  SpectralFunction(std::vector<std::string> kkpath, std::vector<int> kkpathIndex);
  ~SpectralFunction();

  void initialize(double eemin, double eemax, double dde,std::vector<std::vector<int> > ccombIndex, unsigned int Nkpoints);
  void set(int icombIndex, Eigen::MatrixXd sf);

  friend std::ostream& operator<<(std::ostream& Stream, SpectralFunction& sf);

};

#endif
