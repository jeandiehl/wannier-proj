/*
 * SpectralFunctionCalculator.cc
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#include "SpectralFunctionCalculator.h"

SpectralFunctionCalculator::SpectralFunctionCalculator() {}
SpectralFunctionCalculator::~SpectralFunctionCalculator() {}

void SpectralFunctionCalculator::calculate(SpectralFunction& sf, GreensFunction& gf) {
    Eigen::MatrixXcd bs;
	unsigned int Nkpoints = gf.getMaxNkpoints();
	unsigned int Nomega = gf.getMaxNomega();
	//std::cout << Nkpoints << std::endl;
	//std::cout << Nomega << std::endl;
    sf.initialize(gf.getEmin(), gf.getEmax(), gf.getDe(), gf.getCombinedIndex(), Nkpoints);
	
	bs.resize(Nomega, Nkpoints);
	bs.setZero();
    
    unsigned int NcombIndex = gf.getCombinedIndex().size();

    for(unsigned int k = 0; k < NcombIndex; k++) {
		
		for(unsigned int i = 0; i < Nkpoints; i++) {
			Eigen::MatrixXcd GFkpoint = gf.get(i);
			//unsigned int Nenergy = GFkpoint.rows();
			//std::cout << Nenergy << std::endl;
			//for(unsigned int j = 0; j < NcombIndex; j++) {
				bs.col(i) = GFkpoint.row(k);
				//bs.col(i) += GFkpoint.row(j);
			//}
		}
		Eigen::MatrixXd bsfinal;
		bsfinal.resize(Nomega, Nkpoints);
		bsfinal.setZero();
		bsfinal = -1.0/M_PI*bs.imag();
		sf.set(k,bsfinal);
	}
	//std::cout << bsfinal << std::endl;
}
