/*
 * BandsCalculator.cc
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#include "BandsCalculator.h"

BandsCalculator::BandsCalculator() {}
BandsCalculator::~BandsCalculator() {}


void BandsCalculator::calculate(Bands& bands, GreensFunction& gf) {
	Eigen::MatrixXcd bs;
	unsigned int Nkpoints = gf.getMaxNkpoints();
	unsigned int Nomega = gf.getMaxNomega();
	//std::cout << Nkpoints << std::endl;
	//std::cout << Nomega << std::endl;
	
	bs.resize(Nomega, Nkpoints);
	bs.setZero();

	for(unsigned int i = 0; i < Nkpoints; i++) {
		Eigen::MatrixXcd GFkpoint = gf.get(i);
		unsigned int Nenergy = GFkpoint.rows();
		for(unsigned int j = 0; j < Nenergy; j++) {
			bs.col(i) = GFkpoint.row(2);
            //bs.col(i) += GFkpoint.row(j);
		}
	}
	Eigen::MatrixXd bsfinal;
	bsfinal.resize(Nomega, Nkpoints);
	bsfinal.setZero();
	bsfinal = -1.0/M_PI*bs.imag();
	std::cout << bsfinal << std::endl;
}
