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
#include <ctime>

int main(int argc, char **argv) {
	double time = 0.0;
	double tstart = clock();
	
	// get current working directory
	char cwd[256];
	getcwd(cwd, sizeof(cwd));
	std::string path = std::string(cwd);

	unsigned pos = path.find_last_of("/");
	std::string w2kProjectName = path.substr(pos + 1, path.length() - (pos + 1) );
		
	std::vector<std::vector<Eigen::MatrixXcd> > Symm;
	std::vector<std::vector<int> > alpha;
	std::vector<Eigen::MatrixXcd> S;
	std::vector<Eigen::MatrixXcd> R;
	std::vector<double> weight;

	std::vector<std::string> atomNames;
	
	GreensFunction gfProj;

	{
		std::vector<int> multiplicities;
		
		std::cout << "# Read *.struct file" << std::endl;
		FileStruct fileStruct(w2kProjectName);
		fileStruct.read(multiplicities, atomNames);

		
		std::vector<std::vector<int> > energyIndex;
		std::vector<std::vector<std::vector<std::vector<int> > > > combinedIndex;

		std::vector<int> combinedIndexJAtom;
		std::vector<int> combinedIndexAtom;
		std::vector<int> combinedIndexL;
		std::vector<int> combinedIndexM;

		std::cout << "# Read *.outputproj" << std::endl;
		FileOutputproj fileOutputproj(w2kProjectName);
		fileOutputproj.read(combinedIndex, energyIndex, combinedIndexJAtom, combinedIndexAtom, combinedIndexL, combinedIndexM);
		
		Projector proj;
		proj.initialize(combinedIndex, energyIndex, combinedIndexJAtom, combinedIndexAtom, combinedIndexL, combinedIndexM);

		std::cout << "# Read *.proj" << std::endl;
		FileGeneral projFile(w2kProjectName,"proj");
		projFile.read<Projector>(proj);


		
		std::cout << "# Read *.symm" << std::endl;
		FileSymm fileSymm(w2kProjectName);
		fileSymm.read(Symm, alpha, atomNames);

		std::vector<std::vector<double> > energy;
		
		std::cout << "# Read *.energy file" << std::endl;
		FileEnergy fileEnergy(w2kProjectName);
		fileEnergy.read(energy, weight);

		double emin, emax, de, eta;
		std::cout << "# Read *.ingf" << std::endl;
		FileIngf fileIngf(w2kProjectName);
		fileIngf.read(emin, emax, de, eta);

		double EF;
		std::cout << "# Read Fermi Energy from *.scf file" << std::endl;
		FermiEnergy fermi(w2kProjectName);
		fermi.read(EF);


		std::cout << "# Read *.rot file" << std::endl;
		FileRot fileRot(w2kProjectName);
		fileRot.read(R);

		
		std::cout << "# Read *.smat file" << std::endl;
		FileSmat fileSmat(w2kProjectName);
		fileSmat.read(S);


		GreensFunction gf;
		std::cout << "# Calculate Greens Function" << std::endl;
		GreensFunctionCalculator gfCalc(emin, emax, de, eta);
		gfCalc.calculate(gf, energy, EF);

		
		std::cout << "# Project Greens Function" << std::endl;
		GreensFunctionProjector gfProjector;
		gfProjector.calculate(gf, gfProj, proj);
	}

	KSymmSum ksum(Symm, alpha, S, R, weight);
	GreensFunction gfLocal;
	std::cout << "# Calculate symmetrized k-Sum over Greens Function" << std::endl;
	ksum.calculate(gfProj, gfLocal);
    
    DOS dos(w2kProjectName, atomNames);
    DOSCalculator doscalc;
    std::cout << "# Calculate DOS from projected Greens Function" << std::endl;
	doscalc.calculate(gfLocal, dos);
    
	std::cout << "# Write *.dosproj" << std::endl;
	FileGeneral overFile(w2kProjectName,"dosproj");
	overFile.write<DOS>(dos);

	time += clock() - tstart;
	std::cout << ":TIME " << time/CLOCKS_PER_SEC << std::endl;
	return 0;
}

