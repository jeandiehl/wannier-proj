/*
 * FileEnergy.h
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */
 
#ifndef FILEENERGY_H
#define FILEENERGY_H

#include "FileGeneral.h"

#include <vector>
#include <string>
#include <boost/lexical_cast.hpp> // for recognition of 3 digt exponential

/// class FileEnergy - 
class FileEnergy : public FileGeneral {
  // Operations
public:
  FileEnergy (std::string fn);
  ~FileEnergy ();
  void read (std::vector<std::vector<double> >& energy);
};

#endif
