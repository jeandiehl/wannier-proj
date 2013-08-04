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
	
	std::vector<int> multiplicities;
	std::vector<std::string> atomNames; 
	FileStruct fileStruct(w2kProjectName);
	fileStruct.read(multiplicities, atomNames);


	
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
	Overlap over;
	Overlap overTilde;

	ProjectorCalculator projCalc(Emin, Emax, selectedOrbitals, energy, multiplicities, EF);
	projCalc.calculate(alm, clm, overClm, R, S, proj, projTilde, over, overTilde);

	std::string filename = w2kProjectName + ".projtilde";
	std::ofstream myfile(filename.c_str());
	myfile << projTilde << std::endl;
	myfile.close();

	std::string filename1 = w2kProjectName + ".overtilde";
	std::ofstream myfile1(filename1.c_str());
	myfile1 << overTilde << std::endl;
	myfile1.close();

	std::string filename2 = w2kProjectName + ".proj";
	std::ofstream myfile2(filename2.c_str());
	myfile2 << proj << std::endl;
	myfile2.close();

	std::string filename3 = w2kProjectName + ".over";
	std::ofstream myfile3(filename3.c_str());
	myfile3 << over << std::endl;
	myfile3.close();
	
	return 0;
}

