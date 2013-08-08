/*
 * GreensFunction.h
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#ifndef GREENSFUNCTION_H
#define GREENSFUNCTION_H

#include <iostream>
#include <vector>
#include <complex>
#include <Eigen/Core>
#include <cmath>

class GreensFunction {

private:

protected:
  double emin;
  double emax;
  double de;
  double eta;
  int Ne;

  std::vector<Eigen::MatrixXcd > GF;
  std::vector<std::vector<double> > Energy;

  std::vector<std::vector<std::vector<std::vector<int> > > > combinedIndex;

  std::vector<std::vector<int> > combIndex;
  

public:
  GreensFunction();
  ~GreensFunction();

  void initialize(double eemin, double eemax, double dde, double eeta, std::vector<std::vector<double> >& energy);
  void initialize(double eemin, double eemax, double dde, double eeta, std::vector<std::vector<double> >& energy, std::vector<std::vector<int> > combInd);
  void set(int ikpoints, Eigen::MatrixXcd G);
  Eigen::MatrixXcd get(int ikpoints, int ienergy);
  int getMaxNomega();

  std::vector<std::vector<int> > getCombinedIndex();

  double getEmin();
  double getEmax();
  double getDe();
  double getEta();
  std::vector<std::vector<double> >& getEnergy();
  Eigen::MatrixXcd get(int ikpoints);
  int getMaxNkpoints();
};

#endif
