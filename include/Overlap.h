/*
 * Overlap.h
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#ifndef OVERLAP_H
#define OVERLAP_H


#include <Eigen/Core>
#include <iostream>
#include <complex>
#include <vector>

#include "Projector.h"

/// class Overlap - 
class Overlap {

private:
  std::vector<Eigen::MatrixXcd> over;
  // Operations
public:
  Overlap ();
  ~Overlap ();

  void set(int ikpoints, Eigen::MatrixXcd O);
  Eigen::MatrixXcd get(int ikpoints);
  void initialize(int Nkpoints);

  friend std::ostream& operator<<(std::ostream& Stream, Overlap& O);
};

#endif
