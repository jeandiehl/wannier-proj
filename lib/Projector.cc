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


std::ostream& operator<<(std::ostream& Stream, Projector& P) {
	unsigned int Nkpoints = P.energyIndex.size();
	unsigned int NcombIndex = P.combinedIndexJAtom.size();
	
	for(unsigned int ikpoints = 0; ikpoints < Nkpoints; ikpoints++) {
		Stream << std::setw(12) << ikpoints+1 << "    (k-vector ID)"<< std::endl;
		unsigned int Nenergy = P.energyIndex[ikpoints].size();
		for(unsigned int ienergy = 0; ienergy < Nenergy; ienergy++) {
			for(unsigned int icombIndex = 0; icombIndex < NcombIndex; icombIndex++) {
			Stream << std::setprecision(5) << std::fixed << std::setw(8) << real(P.proj[ikpoints](ienergy, icombIndex)) << " " << std::setw(8) << imag(P.proj[ikpoints](ienergy, icombIndex));
			if(icombIndex < NcombIndex-1) {
				Stream << "  ";
			}
			}
			Stream << std::endl;
		}
	}
	
    return Stream;
}
