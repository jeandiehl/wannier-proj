/*
 * FileInproj.h
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */
 
#ifndef FILEINPROJ_H
#define FILEINPROJ_H

#include "FileGeneral.h"

#include <vector>
#include <string>

/// class FileInproj - 
class FileInproj : public FileGeneral {
  // Operations
public:
  FileInproj (std::string fn);
  ~FileInproj ();
  void read (double& Emin, double& Emax, double& dE, std::vector<std::vector<std::vector<int > > >& selectedOrbitals);
};

#endif
