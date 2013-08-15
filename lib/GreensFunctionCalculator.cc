/*
 * GreensFunctionCalculator.cc
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#include "GreensFunctionCalculator.h"

GreensFunctionCalculator::GreensFunctionCalculator(double eemin, double eemax, double dde, double eeta) : emin(eemin), emax(eemax), de(dde), eta(eeta) {}
GreensFunctionCalculator::~GreensFunctionCalculator() {}

void GreensFunctionCalculator::calculate(GreensFunction& gf, std::vector<std::vector<double> >& energy, double EF) {
	gf.initialize(emin, emax, de, eta, energy);

	Eigen::MatrixXcd green;

	int Ne = floor( (emax - emin)/de ) + 1;
	
	unsigned int Nkpoints = energy.size();
	double e;
	
	for(unsigned int i = 0; i < Nkpoints; i++) {
		unsigned int Nenergy = energy[i].size();
		
		green.resize(Nenergy, Ne);
		green.setZero();
		for(unsigned int j = 0; j < Nenergy; j++) {
			
			e = emin;
			for(int k = 0; k < Ne; k++) {
				green(j,k) = calculateNoninteractingGF(e, energy[i][j], EF);
				e += de;
			}
		}
		gf.set(i, green);
	}
}

std::complex<double> GreensFunctionCalculator::calculateNoninteractingGF(double e, double enu, double EF) {
	return 1.0 / ( e - RyEv*(enu - EF) + std::complex<double> (0.0, eta));
}
