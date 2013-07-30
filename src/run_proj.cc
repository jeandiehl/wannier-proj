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
	GeneralCoefficient<Eigen::VectorXcd> Clm;
	GeneralCoefficient<Eigen::VectorXcd> OverClm;

	FileAlmblm fileAlmBlm(w2kProjectName);
	fileAlmBlm.read(Alm, Clm, OverClm);
std::cout << Alm.getCoefficient(0, 1, 0, 23, 1, 1) << std::endl;
std::cout << Clm.getCoefficient(5, 1, 0, 2, 1, 1) << std::endl;
	return 0;
}

