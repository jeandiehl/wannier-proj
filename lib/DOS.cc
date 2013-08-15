/*
 * DOS.cc
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#include "DOS.h"

DOS::DOS(std::string nname, std::vector<std::string> aatomNames) : name(nname), atomNames(aatomNames) {}
DOS::~DOS() {}

void DOS::initialize(int Nomega, int NcombIndex, double emin, double emax, double de, std::vector<std::vector<int> > combIndex) {
    dos.resize(Nomega, NcombIndex);
    dos.setZero();
    energy.resize(Nomega);
    for (int i = 0; i < Nomega; i++) {
        energy(i) = emin + i*de;
        
    }
    combinedIndex = combIndex;
    //std::cout << energy << std::endl;
}

void DOS::set(Eigen::MatrixXd d) { dos = d; }

std::ostream& operator<<(std::ostream& Stream, DOS& D) {
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
    
    
	Stream << "# " << D.name << std::endl;
    Stream << "#EF=   0.00000     NDOS="<< std::setw(2) << D.dos.cols() << "     NENRG="<< std::setw(5) << D.dos.rows() << "    Gaussian bradening: 0.00000" << std::endl;
    Stream << "# ENERGY ";
    for (unsigned int i = 0; i < D.combinedIndex.size(); i++) {
        Stream << "   " << orbitalIrrM[D.combinedIndex[i][3-1]][D.combinedIndex[i][3]] << "-" << D.atomNames[D.combinedIndex[i][0]] << " ";
    }
    Stream << std::endl;
    for (int i = 0; i < D.energy.size(); i++) {
        Stream << std::fixed << std::setprecision(6) << std::setw(12) << D.energy[i];
        for (int j = 0; j < D.dos.cols(); j++) {
            Stream << "  " << std::setprecision(8) << std::setw(12) << D.dos(i,j);
        }
        Stream <<  std::endl;
    }
	
    return Stream;
}
