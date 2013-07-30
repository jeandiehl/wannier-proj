/*
 * run_proj.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */
 
#include "FileAlmblm.h"
#include "GeneralCoefficient.h"

#include <unistd.h> // for getcwd
#include <complex>
#include <Eigen/Core>

int main(int argc, char **argv) {
	
	// get current working directory
	char cwd[256];
	getcwd(cwd, sizeof(cwd));
	std::string path = std::string(cwd);
    
    unsigned pos = path.find_last_of("/");
	std::string w2kProjectName = path.substr(pos + 1, path.length() - (pos + 1) );

	GeneralCoefficient<std::complex<double> > Alm;
	GeneralCoefficient<Eigen::Vector3cd> Clm;
	GeneralCoefficient<Eigen::Vector3cd> OverClm;

    FileAlmblm fileAlmBlm(w2kProjectName);
    fileAlmBlm.read(Alm, Clm, OverClm);
    
	return 0;
}

