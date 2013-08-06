/*
 * FileIngf.cc
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#include "FileIngf.h"

FileIngf::FileIngf(std::string fn) : FileGeneral::FileGeneral(fn, "ingf") {}
FileIngf::~FileIngf() {}


void FileIngf::read(double& emin, double& emax, double& de, double& eta) {
	std::string line;

	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);
			std::stringstream s(line);
			s >> emin;
			s >> emax;
			s >> de;
			s >> eta;
		}
	}

}
