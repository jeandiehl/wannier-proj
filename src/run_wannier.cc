/*
 * run_wannier.cc
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
	
    std::vector<std::vector<Eigen::Vector3d> > atomPositions;
	std::vector<int> multiplicities;
	std::vector<std::string> atomNames;
	Eigen::MatrixXd unitCell;
	std::cout << "# Read *.struct file" << std::endl;
	FileStruct fileStruct(w2kProjectName);
	fileStruct.read(multiplicities, atomNames, atomPositions, unitCell);
	
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


	double EF;
    double vol;
	std::cout << "# Read Fermi Energy and Unit Cell Volume from *.scf file" << std::endl;
	FermiEnergy fermi(w2kProjectName);
	fermi.read(EF,vol);

    std::vector<Eigen::Vector3d> kpoints;
    std::cout << "# Read *.klist" << std::endl;
    FileKlist fileklist(w2kProjectName);
    fileklist.read(kpoints);
    
    Eigen::Vector3d Nspace;
    std::vector<Eigen::Vector3d > selectedCell;
    std::cout << "# Read *.in7" << std::endl;
    FileIn7 filein7(w2kProjectName);
    filein7.read(Nspace, selectedCell);
    
    WaveFunction psi;
    psi.initialize(Nspace);
    std::cout << "# Read *.psink" << std::endl;
    FilePsink filepsink(w2kProjectName);
    filepsink.initialize(Nspace);
    filepsink.read(psi);
    
    std::vector<std::vector<Eigen::MatrixXcd> > Symm;
	std::vector<std::vector<int> > alpha;
    std::cout << "# Read *.symm" << std::endl;
    FileSymm fileSymm(w2kProjectName);
    fileSymm.read(Symm, alpha, atomNames);

    std::vector<std::vector<double> > energy;
    std::vector<double> weight;
    std::cout << "# Read *.energy file" << std::endl;
    FileEnergy fileEnergy(w2kProjectName);
    fileEnergy.read(energy, weight);
    
	std::vector<Eigen::MatrixXcd> R;
    std::cout << "# Read *.rot file" << std::endl;
    FileRot fileRot(w2kProjectName);
    fileRot.read(R);

	std::vector<Eigen::MatrixXcd> S;
    std::cout << "# Read *.smat file" << std::endl;
    FileSmat fileSmat(w2kProjectName);
    fileSmat.read(S);
    
    WannierFunctionCalculator wfcalc;
    WaveFunction wannier;
    std::cout << "# Calculate real space Wannier Functions" << std::endl;
    wfcalc.calculate(vol, kpoints, atomPositions, proj, psi, wannier);
    
    WaveFunction wannierLocal;
    KSymmSum ksum(Symm, alpha, S, R, weight);
	std::cout << "# Calculate symmetrized k-Sum over Wannier Function" << std::endl;
	ksum.calculate(wannier, wannierLocal);


	wannierLocal.setStructure(unitCell, atomNames, atomPositions, selectedCell);
	std::cout << "# Write *.xsf" << std::endl;
	FileGeneral wannierFile(w2kProjectName,"xsf");
	wannierFile.write<WaveFunction>(wannierLocal);
    
	return 0;
}

