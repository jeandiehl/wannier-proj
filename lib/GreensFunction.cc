/*
 * GreensFunction.cc
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#include "GreensFunction.h"

GreensFunction::GreensFunction() {}
GreensFunction::~GreensFunction() {}

void GreensFunction::initialize(double eemin, double eemax, double dde, double eeta, std::vector<std::vector<double> >& energy) {
	emin = eemin;
	emax = eemax;
	de = dde;
	eta = eeta;
	Energy = energy;
	Ne = floor( (emax - emin)/de ) + 1;

	unsigned int Nkpoints = energy.size();
	GF.resize(Nkpoints);
	for(unsigned int i = 0; i < Nkpoints; i++) {
		GF[i].resize(energy[i].size(), Ne);
		GF[i].setZero();
	}
	
}

void GreensFunction::initialize(double eemin, double eemax, double dde, double eeta, std::vector<std::vector<double> >& energy, std::vector<std::vector<int> > combInd) {
	initialize(eemin, eemax, dde, eeta, energy);
	combIndex = combInd;
}

void GreensFunction::set(int ikpoints, Eigen::MatrixXcd G) {
	GF[ikpoints] = G;
}

Eigen::MatrixXcd GreensFunction::get(int ikpoints, int ienergy) {
	return GF[ikpoints].col(ienergy).asDiagonal();
}

int GreensFunction::getMaxNomega() {return Ne;}

std::vector<std::vector<int> > GreensFunction::getCombinedIndex() {
	return combIndex;
}

double GreensFunction::getEmin() {return emin; }
double GreensFunction::getEmax() {return emax; }
double GreensFunction::getDe() {return de; }
double GreensFunction::getEta() {return eta; }

std::vector<std::vector<double> >& GreensFunction::getEnergy() {return Energy; }

Eigen::MatrixXcd GreensFunction::get(int ikpoints) {return GF[ikpoints]; }

int GreensFunction::getMaxNkpoints() {return GF.size(); }
