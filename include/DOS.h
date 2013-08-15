/*
 * DOS.h
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#ifndef DOS_H
#define DOS_H

#include <iostream>
#include <vector>
#include <complex>
#include <iomanip> // setw

#include <Eigen/Core>

class DOS {

private:
  Eigen::MatrixXd dos;
  Eigen::VectorXd energy;
  
  std::string name;
  std::vector<std::string> atomNames;
  std::vector<std::vector<int> > combinedIndex;
  
protected:

public:
  DOS(std::string nname, std::vector<std::string> aatomNames);
  ~DOS();

  void initialize(int Nomega, int NcombIndex, double emin, double emax, double de, std::vector<std::vector<int> > combIndex);
  void set(Eigen::MatrixXd d);
  
  friend std::ostream& operator<<(std::ostream& Stream, DOS& D);
};

#endif
