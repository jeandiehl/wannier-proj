/*
 * Overlap.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#include "Overlap.h"

Overlap::Overlap() {}
Overlap::~Overlap() {}

void Overlap::set(int ikpoints, Eigen::MatrixXcd O) {
	over[ikpoints] = O;
}

Eigen::MatrixXcd Overlap::get(int ikpoints) { return over[ikpoints]; }

void Overlap::initialize(int Nkpoints) {
	over.resize(Nkpoints);
}

std::ostream& operator<<(std::ostream& Stream, Overlap& O) {
	unsigned int Nkpoints = O.over.size();
	for(unsigned int ikpoints = 0; ikpoints < Nkpoints; ikpoints++) {
		Stream << std::setw(12) << ikpoints+1 << "    (k-vector ID)"<< std::endl;
		unsigned int NcombIndex1 = O.over[ikpoints].rows();
		unsigned int NcombIndex2 = O.over[ikpoints].cols();
		for(unsigned int icombIndex1 = 0; icombIndex1 < NcombIndex1; icombIndex1++) {
			for(unsigned int icombIndex2 = 0; icombIndex2 < NcombIndex2; icombIndex2++) {
			Stream << " " << std::setprecision(5) << std::fixed << std::setw(8) << real(O.over[ikpoints](icombIndex1, icombIndex2)) << " " << std::setw(8) << imag(O.over[ikpoints](icombIndex1, icombIndex2));
			if(icombIndex2 < NcombIndex2-1) {
				Stream << "  ";
			}
			}
			Stream << std::endl;
		}
	}
	
    return Stream;
}
