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

  void read(std::vector<std::vector<std::vector<std::vector<int> > > >& combIndex, std::vector<std::vector<int> >& energyInd, std::vector<int>& combIndexJAtom, std::vector<int>& combIndexAtom, std::vector<int>& combIndexL, std::vector<int>& combIndexM);
  void write(Projector& proj, std::vector<std::string> atomNames);

};

#endif
