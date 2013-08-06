/*
 * FileOutputproj.cc
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#include "FileOutputproj.h"

FileOutputproj::FileOutputproj(std::string fn) : FileGeneral::FileGeneral(fn, "outputproj") {}
FileOutputproj::~FileOutputproj() {}

void FileOutputproj::read(std::vector<std::vector<std::vector<std::vector<int> > > >& combIndex, std::vector<std::vector<int> >& energyInd, std::vector<int>& combIndexJAtom, std::vector<int>& combIndexAtom, std::vector<int>& combIndexL, std::vector<int>& combIndexM) {
	std::string line;

	unsigned int NcombIndex, NAtom, NJAtom, Nl, Nm, Nkpoints, Nenergy;
	int energyIndex = 0;
	
	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);

			
			if (line.length() > 11) {
				if (line.substr(0,4).compare("ATOM") == 0) {
					std::stringstream s(line.substr(5,7));
					s >> NAtom;
					s >> NJAtom;
					s >> Nl;
					s >> Nm;
					//std::cout << NAtom << " " << NJAtom << " " << Nl << " " << Nm << std::endl;
					
					combIndexJAtom.resize(NcombIndex+1);
					combIndexAtom.resize(NcombIndex+1);
					combIndexL.resize(NcombIndex+1);
					combIndexM.resize(NcombIndex+1);

					combIndexJAtom[NcombIndex] = NAtom;
					combIndexAtom[NcombIndex] = NJAtom;
					combIndexL[NcombIndex] = Nl;
					combIndexM[NcombIndex] = Nm;
					
					++NcombIndex;
				}
			}

			if (line.length() > 16) {
				if (line.substr(0,17).compare("(energy index ID)") == 0) {
					std::stringstream s(line.substr(18,line.length()-18));
					Nenergy = 0;
					s >> Nenergy;
					//std::cout << "Nenergy" << Nenergy << std::endl;
					energyInd[Nkpoints-1].resize(Nenergy);
					for(unsigned int i = 0; i < Nenergy; i++) {
						s >> energyIndex;
						//std::cout << i << " " << energyIndex << std::endl;
						energyInd[Nkpoints-1][i] = energyIndex - 1;
						//std::cout << energyInd[Nkpoints-1][i] << " ";
						
					}
					//std::cout << std::endl;
				}
				
			}
			
			if (line.length() > 28) {
				if (line.substr(16,13).compare("(k-vector ID)") == 0) {
					std::stringstream s(line.substr(0,12));
					s >> Nkpoints;
					energyInd.resize(Nkpoints);
				}
			}
		}
	}
}

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
		myfileOut << "ATOM ";
		for(unsigned int j = 0; j < NcombIndJ; j++) {
			myfileOut << combInd[i][j] << " ";
			
		}
		myfileOut << atomNames[combInd[i][1]] << " ";
			myfileOut << orbitalIrrM[combInd[i][3-1]][combInd[i][3]] << " ";
		myfileOut << std::endl;
	}
	
	myfileOut << std::endl;
	
	std::vector<std::vector<int> > energyInd = proj.getEnergyIndex();
	unsigned int NenergyIndex = energyInd.size();
	for(unsigned int i = 0; i < NenergyIndex; i++) {
		myfileOut << std::setw(12) << i+1 << "    (k-vector ID)"<< std::endl;
		myfileOut << "(energy index ID) ";
		unsigned int Nbands = energyInd[i].size();
		myfileOut << Nbands << "     ";
		for(unsigned int j = 0; j < Nbands; j++) {
			myfileOut << energyInd[i][j]+1 << " ";
		}
		myfileOut << std::endl;
	}
	
	myfileOut.close();
	myfile.open(filenamesuffix.c_str());
}
