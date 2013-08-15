/*
 * KSymmSum.h
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#ifndef KSYMMSUM_H
#define KSYMMSUM_H

#include <iostream>
#include <vector>
#include <complex>

#include "GreensFunction.h"
#include "Projector.h"

class KSymmSum {

private:
  std::vector<std::vector<Eigen::MatrixXcd> > L;
  std::vector<Eigen::MatrixXcd> U;
  std::vector<double> weight;
  std::vector<std::vector<int> > alpha;
  
  void generateUMatrix(std::vector<Eigen::MatrixXcd>& R, std::vector<Eigen::MatrixXcd>& S, std::vector<Eigen::MatrixXcd>& U);
  void generateLMatrix(std::vector<std::vector<Eigen::MatrixXcd> >& Symm, std::vector<Eigen::MatrixXcd>& U, std::vector<std::vector<Eigen::MatrixXcd> >& L);
  
protected:

public:
  KSymmSum(std::vector<std::vector<Eigen::MatrixXcd> >& Symm, std::vector<std::vector<int> >& aalpha, std::vector<Eigen::MatrixXcd>& R, std::vector<Eigen::MatrixXcd>& S, std::vector<double>& wweight);
  ~KSymmSum();

  void calculate(GreensFunction& gf, GreensFunction& gflocal);

};

#endif
