/*
 * FileAlmblm.h
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#ifndef FILEALMBLM_H
#define FILEALMBLM_H

#include "FileGeneral.h"
#include "GeneralCoefficient.h"

#include <string>

/// class FileAlmblm - 
class FileAlmblm : public FileGeneral {
  // Operations
public:
  FileAlmblm (string fn);
  ~FileAlmblm ();
  void read (GeneralCoefficient<complex<double> >& Alm, GeneralCoefficient<Vector3cd>& Clm, GeneralCoefficient<Vector3cd>& O);
};

#endif
