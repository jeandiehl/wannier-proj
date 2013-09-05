/*
 * FileStruct.h
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */
 
#ifndef FILESTRUCT_H
#define FILESTRUCT_H

#include "FileGeneral.h"

#include <vector>
#include <string>
#include <Eigen/Core>

/// class FileStruct - 
class FileStruct : public FileGeneral {
  // Operations
public:
  FileStruct (std::string fn);
  ~FileStruct ();
  void read (std::vector<int>& mult, std::vector<std::string>& atomNames);
  void read (std::vector<int>& mult, std::vector<std::string>& atomNames, std::vector<std::vector<Eigen::Vector3d> >& atomPositions);
  void read (std::vector<int>& mult, std::vector<std::string>& atomNames, std::vector<std::vector<Eigen::Vector3d> >& atomPositions, Eigen::MatrixXd& unitCell);
};

#endif
