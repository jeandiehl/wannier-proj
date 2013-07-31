/*
 * run_proj.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#include "FileInproj.h"
#include "FileAlmblm.h"
#include "FileRot.h"
#include "FileSmat.h"
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
	
	std::vector<Eigen::MatrixXcd> R;
	std::vector<Eigen::MatrixXcd> S;

	FileRot fileRot(w2kProjectName);
	fileRot.read(R);

	FileSmat fileSmat(w2kProjectName);
	fileSmat.read(S);

	double Emin;
	double Emax;
	double dE;
	std::vector<std::vector<std::vector<int > > > selectedOrbitals;
	
	FileInproj fileInproj(w2kProjectName);
	fileInproj.read(Emin, Emax, dE, selectedOrbitals);
	return 0;
}

