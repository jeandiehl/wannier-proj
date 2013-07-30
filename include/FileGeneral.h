/*
 * FileGeneral.h
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#ifndef FILEGENERAL_H
#define FILEGENERAL_H

#include <string>
#include <fstream> // for write/read files
#include <sstream> // for stringstreams
#include <iostream>

/// class FileGeneral - 
class FileGeneral {
  // Attributes
protected:
  std::string filename;
  std::string filesuffix;
  std::string filenamesuffix;
  std::ifstream myfile;
  
  // Operations
public:
  FileGeneral (std::string fn, std::string fs);
  ~FileGeneral ();

};

#endif
