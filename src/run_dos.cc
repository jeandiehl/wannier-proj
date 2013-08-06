/*
 * run_dos.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#include "WannierProj"

#include <unistd.h> // for getcwd
#include <complex>
#include <iostream>
#include <vector>
#include <fstream>
#include <Eigen/Core>

int main(int argc, char **argv) {

	// get current working directory
	char cwd[256];
	getcwd(cwd, sizeof(cwd));
	std::string path = std::string(cwd);

	unsigned pos = path.find_last_of("/");
	std::string w2kProjectName = path.substr(pos + 1, path.length() - (pos + 1) );
	
	std::vector<int> multiplicities;
	std::vector<std::string> atomNames;
	std::cout << ">> Read *.struct file" << std::endl;
	FileStruct fileStruct(w2kProjectName);
	fileStruct.read(multiplicities, atomNames);

	
	std::vector<std::vector<int> > energyIndex;
	std::vector<std::vector<std::vector<std::vector<int> > > > combinedIndex;

	std::vector<int> combinedIndexJAtom;
	std::vector<int> combinedIndexAtom;
	std::vector<int> combinedIndexL;
	std::vector<int> combinedIndexM;

	std::cout << ">> Read *.outputproj" << std::endl;
	FileOutputproj fileOutputproj(w2kProjectName);
	fileOutputproj.read(combinedIndex, energyIndex, combinedIndexJAtom, combinedIndexAtom, combinedIndexL, combinedIndexM);
	
	Projector proj;
	proj.initialize(combinedIndex, energyIndex, combinedIndexJAtom, combinedIndexAtom, combinedIndexL, combinedIndexM);

	std::cout << ">> Read *.proj" << std::endl;
	FileGeneral projFile(w2kProjectName,"proj");
	projFile.read<Projector>(proj);

	std::vector<std::vector<Eigen::MatrixXcd> > Symm;
	std::vector<std::vector<int> > alpha;
	
	std::cout << ">> Read *.symm" << std::endl;
	FileSymm fileSymm(w2kProjectName);
	fileSymm.read(Symm, alpha, atomNames);

	std::vector<std::vector<double> > energy;
	std::vector<double> weight;
	std::cout << ">> Read *.energy file" << std::endl;
	FileEnergy fileEnergy(w2kProjectName);
	fileEnergy.read(energy, weight);

	double emin, emax, de, eta;
	std::cout << ">> Read *.ingf" << std::endl;
	FileIngf fileIngf(w2kProjectName);
	fileIngf.read(emin, emax, de, eta);

	std::cout << ">> Write *.proj" << std::endl;
	projFile.write<Projector>(proj);
	
	std::cout << ">> Write *.outputproj" << std::endl;
	fileOutputproj.write(proj, atomNames);
	
	return 0;
}

