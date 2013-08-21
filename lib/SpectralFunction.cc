/*
 * SpectralFunction.cc
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#include "SpectralFunction.h"

SpectralFunction::SpectralFunction() {}
SpectralFunction::~SpectralFunction() {}

void SpectralFunction::initialize(double eemin, double eemax, double dde,std::vector<std::vector<int> > ccombIndex, unsigned int Nkpoints) {
	emin = eemin;
	emax = eemax;
	de = dde;
	Ne = floor( (emax - emin)/de ) + 1;
    combIndex = ccombIndex;
    
	unsigned int NcombIndex = combIndex.size();
	SF.resize(NcombIndex);
    
	for(unsigned int i = 0; i < NcombIndex; i++) {
        //std::cout << Ne << std::endl;
		SF[i].resize(Ne, Nkpoints);
		SF[i].setZero();
	}
	
}

void SpectralFunction::set(int icombIndex, Eigen::MatrixXd sf) {
	SF[icombIndex] = sf;
}


std::ostream& operator<<(std::ostream& Stream, SpectralFunction& sf) {
    unsigned int MAXL = 4;

	std::vector<std::vector<std::string > > orbitalIrrM;
	orbitalIrrM.resize(MAXL);
	for(unsigned int i = 0; i < MAXL; i++) {
		unsigned int maxJ = 2*i + 1;
		orbitalIrrM[i].resize(maxJ);
	}
	orbitalIrrM[0][0] = "      s";
	orbitalIrrM[1][0] = "     px";
	orbitalIrrM[1][1] = "     py";
	orbitalIrrM[1][2] = "     pz";
	orbitalIrrM[2][0] = "    dz2";
	orbitalIrrM[2][1] = "dx2-dy2";
	orbitalIrrM[2][2] = "    dxy";
	orbitalIrrM[2][3] = "    dxz";
	orbitalIrrM[2][4] = "    dyz";
    
    unsigned int Nkpoints = sf.SF[0].cols();
    unsigned int Nomega = sf.SF[0].rows();
    unsigned int NcombIndex = sf.SF.size();

    for(unsigned int i = 0; i < Nkpoints; i++) {
		for(unsigned int j = 0; j < Nomega; j++) {
			Stream << i << "   " << j << "   ";
			for(unsigned int k = 0; k < NcombIndex; k++) {
				Stream << sf.SF[k](j,i) << " ";
			}
			Stream << std::endl;
		}
	}

	
    return Stream;
}
