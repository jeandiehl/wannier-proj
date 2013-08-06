/*
 * FileOutputproj.h
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#ifndef FILEOUTPUTPROJ_H
#define FILEOUTPUTPROJ_H

#include "FileGeneral.h"
#include "Projector.h"

#include <iostream>
#include <vector>
#include <complex>

class FileOutputproj : public FileGeneral {

private:

protected:

public:
  FileOutputproj(std::string fn);
  ~FileOutputproj();

  void write(Projector& proj, std::vector<std::string> atomNames);

};

#endif
