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

	std::cout << ">> Read *.almblm file" << std::endl;
	FileAlmblm fileAlmBlm(w2kProjectName);
	fileAlmBlm.read(alm, clm, overClm);
	
	std::vector<Eigen::MatrixXcd> R;
	std::vector<Eigen::MatrixXcd> S;

	std::cout << ">> Read *.rot file" << std::endl;
	FileRot fileRot(w2kProjectName);
	fileRot.read(R);

	std::cout << ">> Read *.smat file" << std::endl;
	FileSmat fileSmat(w2kProjectName);
	fileSmat.read(S);

	double Emin;
	double Emax;
	std::vector<std::vector<std::vector<int > > > selectedOrbitals;
	
	std::vector<int> multiplicities;
	std::vector<std::string> atomNames;
	std::cout << ">> Read *.struct file" << std::endl;
	FileStruct fileStruct(w2kProjectName);
	fileStruct.read(multiplicities, atomNames);


	std::cout << ">> Read *.inproj file" << std::endl;
	FileInproj fileInproj(w2kProjectName);
	fileInproj.read(Emin, Emax, selectedOrbitals);

	std::vector<std::vector<double> > energy;
	std::cout << ">> Read *.energy file" << std::endl;
	FileEnergy fileEnergy(w2kProjectName);
	fileEnergy.read(energy);

	double EF;
	std::cout << ">> Read Fermi Energy from *.scf file" << std::endl;
	FermiEnergy fermi(w2kProjectName);
	fermi.read(EF);

	Projector proj;
	Projector projTilde;
	Overlap over;
	Overlap overTilde;

	std::cout << ">> Calculate Projectors" << std::endl;
	ProjectorCalculator projCalc(Emin, Emax, selectedOrbitals, energy, multiplicities, EF);
	projCalc.calculate(alm, clm, overClm, R, S, proj, projTilde, over, overTilde);

	std::cout << ">> Write *.projtilde" << std::endl;
	FileGeneral overtildeFile(w2kProjectName,".projtilde");
	overtildeFile.write<Projector>(projTilde);

	std::cout << ">> Write *.overtilde" << std::endl;
	FileGeneral projtildeFile(w2kProjectName,".overtilde");
	overtildeFile.write<Overlap>(overTilde);
	
	std::cout << ">> Write *.proj" << std::endl;
	FileGeneral projFile(w2kProjectName,".proj");
	projFile.write<Projector>(proj);

	std::cout << ">> Write *.over" << std::endl;
	FileGeneral overFile(w2kProjectName,".over");
	overFile.write<Overlap>(over);
	
	return 0;
}

