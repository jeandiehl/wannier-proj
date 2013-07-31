/*
 * run_proj.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#include "WannierProj"

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

	GeneralCoefficient<std::complex<double> > alm;
	GeneralCoefficient<Eigen::VectorXcd> clm;
	GeneralCoefficient<Eigen::VectorXcd> overClm;

	FileAlmblm fileAlmBlm(w2kProjectName);
	fileAlmBlm.read(alm, clm, overClm);
	
	std::vector<Eigen::MatrixXcd> R;
	std::vector<Eigen::MatrixXcd> S;

	FileRot fileRot(w2kProjectName);
	fileRot.read(R);

	FileSmat fileSmat(w2kProjectName);
	fileSmat.read(S);

	double Emin;
	double Emax;
	std::vector<std::vector<std::vector<int > > > selectedOrbitals;
	
	FileInproj fileInproj(w2kProjectName);
	fileInproj.read(Emin, Emax, selectedOrbitals);

	std::vector<std::vector<double> > energy;
	FileEnergy fileEnergy(w2kProjectName);
	fileEnergy.read(energy);

	double EF;
	FermiEnergy fermi(w2kProjectName);
	fermi.read(EF);

	Projector proj;
	Projector projTilde;

	ProjectorCalculator projCalc(Emin, Emax, selectedOrbitals, energy, EF);
	projCalc.calculate(alm, clm, overClm, proj, projTilde);
	
	return 0;
}

