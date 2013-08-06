/*
 * FileOutputproj.cc
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#include "FileOutputproj.h"

FileOutputproj::FileOutputproj(std::string fn) : FileGeneral::FileGeneral(fn, "outputproj") {}
FileOutputproj::~FileOutputproj() {}

void FileOutputproj::write(Projector& proj, std::vector<std::string> atomNames) {
	std::vector<std::string> orbitalL;
	unsigned int MAXL = 4;
	orbitalL.resize(MAXL);
	orbitalL[0] = "s";
	orbitalL[1] = "p";
	orbitalL[2] = "d";
	orbitalL[3] = "f";

	std::vector<std::vector<std::string > > orbitalIrrM;
	orbitalIrrM.resize(MAXL);
	for(unsigned int i = 0; i < MAXL; i++) {
		unsigned int maxJ = 2*i + 1;
		orbitalIrrM[i].resize(maxJ);
	}
	orbitalIrrM[0][0] = "s";
	orbitalIrrM[1][0] = "px";
	orbitalIrrM[1][1] = "py";
	orbitalIrrM[1][2] = "pz";
	orbitalIrrM[2][0] = "dz2";
	orbitalIrrM[2][1] = "dx2-dy2";
	orbitalIrrM[2][2] = "dxy";
	orbitalIrrM[2][3] = "dxz";
	orbitalIrrM[2][4] = "dyz";
	
	myfile.close();
	std::ofstream myfileOut;
	myfileOut.open(filenamesuffix.c_str());

	myfileOut << ">> ATOM Name, Multiplicity Index, Orbital l, Irreducible Orbital m" << std::endl;
	std::vector<std::vector<int> > combInd = proj.getCombinedIndex();
	unsigned int NcombInd = combInd.size();
	for(unsigned int i = 0; i < NcombInd; i++) {
		unsigned int NcombIndJ = combInd[i].size();
		for(unsigned int j = 0; j < NcombIndJ; j++) {
			if(j == 0) {
				myfileOut << atomNames[combInd[i][j]] << " ";
			} else if(j == 2) {
				myfileOut << orbitalL[combInd[i][j]] << " ";
			} else if(j == 3) {
				myfileOut << orbitalIrrM[combInd[i][j-1]][combInd[i][j]] << " ";
			} else {
				myfileOut << combInd[i][j] << " ";
			}
			
		}
		myfileOut << std::endl;
	}
	
	myfileOut << std::endl;
	
	std::vector<std::vector<int> > energyInd = proj.getEnergyIndex();
	unsigned int NenergyIndex = energyInd.size();
	for(unsigned int i = 0; i < NenergyIndex; i++) {
		myfileOut << std::setw(12) << i << "    (k-vector ID)"<< std::endl;
		myfileOut << energyInd[i].front() << " " << energyInd[i].back() << "    (energy index ID)" << std::endl;
	}
	
	myfileOut.close();
	myfile.open(filenamesuffix.c_str());
}
