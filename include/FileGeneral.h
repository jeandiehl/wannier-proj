/*
 * FileGeneral.h
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#ifndef FILEGENERAL_H
#define FILEGENERAL_H

#include <string>

/// class FileGeneral - 
class FileGeneral {
  // Attributes
protected:
  string filename;
  string filesuffix;
  // Operations
public:
  FileGeneral (string fn, string fs);
  ~FileGeneral ();
};

#endif
