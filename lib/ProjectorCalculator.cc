/*
 * ProjectorCalculator.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#include "ProjectorCalculator.h"

ProjectorCalculator::ProjectorCalculator (double emin, double emax, std::vector<std::vector<std::vector<int > > > selOrb, std::vector<std::vector<double> >& energy, double EF) : Emin(emin), Emax(emax), selectedOrbitals(selOrb) {
	getSelectedEnergies(energy, EF);
}

ProjectorCalculator::~ProjectorCalculator () {}

void ProjectorCalculator::calculate (GeneralCoefficient<std::complex<double> >& Alm, GeneralCoefficient<Eigen::VectorXcd>& Clm, GeneralCoefficient<Eigen::VectorXcd>& O, Projector& Proj, Projector& ProjTilde) {}


void ProjectorCalculator::getSelectedEnergies(std::vector<std::vector<double> >& energy, double EF) {
	unsigned int Nkpoints = energy.size();
	selectedEnergies.resize(Nkpoints);
	for(unsigned int i = 0; i < 1; i++) {
		unsigned int Nenergy = energy[i].size();
		selectedEnergies[i].resize(Nenergy);
		for(unsigned int j = 0; j < Nenergy; j++) {
			if( ( (Emin/RyEv + EF) <= energy[i][j]) && ( (Emax/RyEv + EF) >= energy[i][j]) ) {
				selectedEnergies[i][j] = 1;
			}  else {
				selectedEnergies[i][j] = 0;
			}
			std::cout << j << " " << selectedEnergies[i][j] << std::endl;
		}
	}
}
