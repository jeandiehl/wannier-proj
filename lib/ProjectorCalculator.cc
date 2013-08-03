/*
 * ProjectorCalculator.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#include "ProjectorCalculator.h"

ProjectorCalculator::ProjectorCalculator (double emin, double emax, std::vector<std::vector<std::vector<int > > > selOrb, std::vector<std::vector<double> >& energy, std::vector<int>& mult, double EF) : Emin(emin), Emax(emax), selectedOrbitals(selOrb), multiplicities(mult) {
	getSelectedEnergies(energy, EF);
}

ProjectorCalculator::~ProjectorCalculator () {}

void ProjectorCalculator::calculate (GeneralCoefficient<std::complex<double> >& Alm, GeneralCoefficient<Eigen::VectorXcd>& Clm, GeneralCoefficient<Eigen::VectorXcd>& O, std::vector<Eigen::MatrixXcd>& R, std::vector<Eigen::MatrixXcd>& S, Projector& Proj, Projector& ProjTilde) {
	initialize();
	Proj.initialize(combinedIndex, energyIndex, combinedIndexJAtom, combinedIndexAtom, combinedIndexL, combinedIndexM);
	unsigned int NcombIndex = combinedIndexAtom.size();
	unsigned int Nkpoints = energyIndex.size();
	std::complex<double> temp1, temp2;
	Eigen::MatrixXcd P;
	Eigen::MatrixXcd PPrime;
	
	generateUMatrix(R, S, U);
	
	for(unsigned int ikpoints = 0; ikpoints < Nkpoints; ikpoints++) {
		unsigned int NenergyIndex = energyIndex[ikpoints].size();
		P.resize(NcombIndex, NenergyIndex);
		PPrime.resize(NcombIndex, NenergyIndex);
		P.setZero();
		PPrime.setZero();
		for(unsigned int i = 0; i < NcombIndex; i++) {
			for(unsigned int j = 0; j < NenergyIndex; j++) {
				temp1 = Alm.getCoefficient(ikpoints, combinedIndexJAtom[i], combinedIndexAtom[i], energyIndex[ikpoints][j], combinedIndexL[i], combinedIndexM[i]);
				temp2 = Clm.getCoefficient(ikpoints, combinedIndexJAtom[i], combinedIndexAtom[i], energyIndex[ikpoints][j], combinedIndexL[i], combinedIndexM[i]).transpose()
				* O.getCoefficient(ikpoints, combinedIndexJAtom[i], combinedIndexAtom[i], energyIndex[ikpoints][j], combinedIndexL[i], combinedIndexM[i]);
				P(i,j) = temp1 + temp2;
				//Proj.set(j,i,ikpoints, temp1+temp2);
			}
		}
		
		PPrime = U*P;
		//PPrime = P;
		Proj.set(ikpoints,PPrime.transpose());
		//std::cout << std::fixed << std::setprecision(5) << Proj.get(ikpoints) << std::endl << std::endl;
	}
	

}


void ProjectorCalculator::getSelectedEnergies(std::vector<std::vector<double> >& energy, double EF) {
	unsigned int Nkpoints = energy.size();
	selectedEnergies.resize(Nkpoints);
	for(unsigned int i = 0; i < Nkpoints; i++) {
		unsigned int Nenergy = energy[i].size();
		selectedEnergies[i].resize(Nenergy);
		for(unsigned int j = 0; j < Nenergy; j++) {
			if( ( (Emin/RyEv + EF) <= energy[i][j]) && ( (Emax/RyEv + EF) >= energy[i][j]) ) {
				selectedEnergies[i][j] = 1;
			}  else {
				selectedEnergies[i][j] = 0;
			}
		}
	}
}

void ProjectorCalculator::initialize() {
	unsigned int Nkpoints = selectedEnergies.size();
	energyIndex.resize(Nkpoints);
	for(unsigned int i = 0; i < Nkpoints; i++) {
		unsigned int Nenergy = selectedEnergies[i].size();
		
		for(unsigned int j = 0; j < Nenergy; j++) {
			if(selectedEnergies[i][j] == 1) {
				energyIndex[i].push_back(j);
				//std::cout << i << " " << energyIndex[i][energyIndex[i].size()-1] << std::endl;
			}
		}
	}
	
	int index = 0;
	unsigned int Njatom = selectedOrbitals.size();
	for(unsigned int ijatom = 0; ijatom < Njatom; ijatom++) {
		unsigned int Natom = multiplicities[ijatom];
		for(unsigned int iatom = 0; iatom < Natom; iatom++) {
			unsigned int Nl = selectedOrbitals[ijatom].size();
			for(unsigned int il = 0; il < Nl; il++) {
				unsigned int Nm = selectedOrbitals[ijatom][il].size();
				for(unsigned int im = 0; im < Nm; im++) {
					if(selectedOrbitals[ijatom][il][im] == 1) {
						combinedIndexJAtom.resize(index+1);
						combinedIndexJAtom[index] = ijatom;
						combinedIndexAtom.resize(index+1);
						combinedIndexAtom[index] = iatom;
						combinedIndexL.resize(index+1);
						combinedIndexL[index] = il;
						combinedIndexM.resize(index+1);
						combinedIndexM[index] = im;
						index += 1;
					}
						
				}
			}
		}
	}
	//std::cout << index << std::endl;

}


void ProjectorCalculator::generateUMatrix(std::vector<Eigen::MatrixXcd>& R, std::vector<Eigen::MatrixXcd>& S, Eigen::MatrixXcd& U) {
	unsigned int NcombIndex = combinedIndexAtom.size();
	U.resize(NcombIndex,NcombIndex);
	U.setZero();
	unsigned int i = 0;
	unsigned int mmax = 0;
	while(i < NcombIndex) {
		//std::cout << S[combinedIndexL[i]] << std::endl;
		//std::cout << R[combinedIndexL[i]] << std::endl;
		mmax = 2*combinedIndexL[i]+1;
		U.block(i,i,mmax,mmax) = S[combinedIndexL[i]]*R[combinedIndexL[i]];
		i += mmax;
	}

}
