/*
 * FileGeneral.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#include "FileGeneral.h"

FileGeneral::FileGeneral(std::string fn, std::string fs) : filename(fn), filesuffix(fs), filenamesuffix(fn + "." + fs) {
	myfile.open(filenamesuffix.c_str());
}

FileGeneral::~FileGeneral() {
	myfile.close();
}

