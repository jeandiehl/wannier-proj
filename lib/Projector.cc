/*
 * Projector.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#include "Projector.h"

Projector::Projector () {}
Projector::~Projector () {}

void Projector::initialize(std::vector<std::vector<std::vector<std::vector<int> > > > combIndex, std::vector<std::vector<int> > energyInd, std::vector<int> combIndexJAtom, std::vector<int> combIndexAtom, std::vector<int> combIndexL, std::vector<int> combIndexM) {
	energyIndex = energyInd;
	combinedIndex = combIndex;
	combinedIndexJAtom = combIndexJAtom;
	combinedIndexAtom = combIndexAtom;
	combinedIndexL = combIndexL;
	combinedIndexM = combIndexM;

	proj.resize(energyIndex.size());
	for(unsigned int i = 0; i < energyIndex.size(); i++) {
		proj[i].resize(energyIndex[i].size(), combinedIndexJAtom.size());
        //std::cout <<combinedIndexJAtom.size() << " " << proj[i].cols() << " " << proj[i].rows() << std::endl;
		proj[i].setZero();
	}
	
}

void Projector::set(int i, int j, int ikpoints, std::complex<double> value) {
	proj[ikpoints](i,j) = value;
}
void Projector::set(int ikpoints, Eigen::MatrixXcd P) {
	proj[ikpoints] = P;
}

Eigen::MatrixXcd Projector::get(int ikpoints) {
return proj[ikpoints];
}

int Projector::getMaxKpoints() { return energyIndex.size(); }

std::vector<std::vector<int> > Projector::getCombinedIndex() {
	std::vector<std::vector<int> > combIndex;
	combIndex.resize(combinedIndexJAtom.size());

	unsigned int NcombIndex = combIndex.size();
	for(unsigned int i = 0; i < NcombIndex; i++) {
		combIndex[i].resize(4);
		combIndex[i][0] = combinedIndexJAtom[i];
		combIndex[i][1] = combinedIndexAtom[i];
		combIndex[i][2] = combinedIndexL[i];
		combIndex[i][3] = combinedIndexM[i];
	}

	return combIndex;
}

int Projector::getMaxCombinedIndex() {return combinedIndexJAtom.size(); }

std::vector<std::vector<int> > Projector::getEnergyIndex() {
	return energyIndex;
}


std::ostream& operator<<(std::ostream& Stream, Projector& P) {
	unsigned int Nkpoints = P.energyIndex.size();
	unsigned int NcombIndex = P.combinedIndexJAtom.size();
	
	for(unsigned int ikpoints = 0; ikpoints < Nkpoints; ikpoints++) {
		Stream << std::setw(12) << ikpoints+1 << "    (k-vector ID)"<< std::endl;
		unsigned int Nenergy = P.energyIndex[ikpoints].size();
		for(unsigned int ienergy = 0; ienergy < Nenergy; ienergy++) {
			for(unsigned int icombIndex = 0; icombIndex < NcombIndex; icombIndex++) {
			Stream << " " << std::setprecision(5) << std::fixed << std::setw(8) << real(P.proj[ikpoints](ienergy, icombIndex)) << " " << std::setw(8) << imag(P.proj[ikpoints](ienergy, icombIndex));
			//Stream << " " <<std::scientific  << std::setw(13) << real(P.proj[ikpoints](ienergy, icombIndex)) << " " << std::setw(13) << imag(P.proj[ikpoints](ienergy, icombIndex));
			if(icombIndex < NcombIndex-1) {
				Stream << "  ";
			}
			}
			Stream << std::endl;
		}
	}
	
    return Stream;
}

std::istream& operator>>(std::istream& Stream, Projector& Proj) {
	std::string line;
	unsigned int Nkpoints;
	Eigen::MatrixXcd P;
	double realP, imagP;

	while ( Stream.good() ) {
		getline (Stream,line);

		if (line.length() > 28) {
			if (line.substr(16,13).compare("(k-vector ID)") == 0) {
				std::stringstream s(line.substr(0,12));
				s >> Nkpoints;
			}
			if (line.substr(16,13).compare("(k-vector ID)") != 0) {
				
				unsigned int Nenergy = Proj.energyIndex[Nkpoints-1].size();
				unsigned int NcombIndex = Proj.combinedIndexJAtom.size();
				P.resize(Nenergy, NcombIndex);
				P.setZero();
				for(unsigned int i = 0; i < Nenergy; i++) {
					std::stringstream s(line);
					for(unsigned int j = 0; j < NcombIndex; j++) {
						
						realP = 0.0;
						imagP = 0.0;
						s >> realP;
						s >> imagP;
						//std::cout << realP << " " << imagP << std::endl;
						P(i,j) = std::complex<double> (realP, imagP);
						
					}
					//std::string test;
					//std::cin >> test;
					if(i < Nenergy-1) {
						getline(Stream, line);
					}
				}
				//std::cout << std::fixed << std::setprecision(4) << P << std::endl << std::endl;
				Proj.set(Nkpoints-1, P);
				//std::cout << Proj.get(Nkpoints-1) << std::endl;
			}
		}
			
	}
	
	return Stream;
}
