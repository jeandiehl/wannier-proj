/*
 * WaveFunction.h
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#ifndef WAVEFUNCTION_H
#define WAVEFUNCTION_H

#include <iostream>
#include <vector>
#include <complex>
#include <iomanip>

#include <Eigen/Core>

class WaveFunction {

private:
  std::vector<Eigen::MatrixXcd > WF;
  Eigen::Vector3d Nspace;
  int NspaceTotal;

  std::vector<std::vector<int> > combIndex;

  Eigen::MatrixXd unitCell;
  std::vector<std::string> atomNames;
  std::vector<std::vector<Eigen::Vector3d> > atomPositions;
  std::vector<Eigen::Vector3d > selectedCell;
  
protected:

public:
  WaveFunction();
  ~WaveFunction();
  
  void initialize(Eigen::Vector3d NNspace);
  void initialize(Eigen::Vector3d NNspace, std::vector<std::vector<int> > combinedIndex);
  void initialize(WaveFunction& wf);
  void setStructure(Eigen::MatrixXd uunitCell, std::vector<std::string> aatomNames, std::vector<std::vector<Eigen::Vector3d> > aatomPositions, std::vector<Eigen::Vector3d > sselectedCell);
  
  void set(int ikpoints, Eigen::MatrixXcd w);
  Eigen::MatrixXcd get(int ikpoints);
  
  int getNspaceTotal();
  Eigen::Vector3d getNspace();
  int getMaxNkpoints();
  Eigen::MatrixXcd get(int ikpoints, int inspace);

  std::vector<std::vector<int> > getCombinedIndex();

  friend std::ostream& operator<<(std::ostream& Stream, WaveFunction& W);
};

#endif
