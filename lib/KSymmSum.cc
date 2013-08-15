/*
 * KSymmSum.cc
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#include "KSymmSum.h"

KSymmSum::KSymmSum(std::vector<std::vector<Eigen::MatrixXcd> >& Symm, std::vector<std::vector<int> >& aalpha, std::vector<Eigen::MatrixXcd>& R, std::vector<Eigen::MatrixXcd>& S, std::vector<double>& wweight) : weight(wweight), alpha(aalpha) {
	generateUMatrix(R, S, U);
	generateLMatrix(Symm, U, L);
}
KSymmSum::~KSymmSum() {}

void KSymmSum::calculate(GreensFunction& gf, GreensFunction& gflocal) {
	
	Eigen::MatrixXcd O;
	std::vector<std::vector<int> > combIndex = gf.getCombinedIndex();
	
	unsigned int NcombIndex = combIndex.size();
	//std::cout << NcombIndex << std::endl;
	O.resize(NcombIndex,NcombIndex);
	
	unsigned int Nkpoints = gf.getMaxNkpoints();
	unsigned int Nsymm = L[1].size();
	//std::cout << Nsymm << std::endl;
	Eigen::MatrixXcd temp;
	Eigen::MatrixXcd OGO;
    unsigned int Nenergy = gf.getMaxNomega();
    //std::cout << gf.get(0, 0) << std::endl;
    
    Eigen::MatrixXcd OGOsum;
    OGOsum.resize(NcombIndex, NcombIndex);
    Eigen::MatrixXcd GFlocal;
    GFlocal.resize(NcombIndex, Nenergy);
    GFlocal.setZero();
    
    double weightSum = 0.0;
    for (unsigned int i = 0; i < weight.size(); i++) {
        weightSum += weight[i];
    }
    
	for(unsigned int ienergy = 0; ienergy < Nenergy; ienergy++) {
        OGOsum.setZero();
        for(unsigned int ikpoints = 0; ikpoints < Nkpoints; ikpoints++) {
            //std::cout << Nenergy << std::endl;
			for(unsigned int isymm = 0; isymm < Nsymm; isymm++) {
                O.setZero();
                unsigned int i = 0;
                unsigned int mmax = 0;
                while(i < NcombIndex) {
                    //std::cout << S[combinedIndexL[i]] << std::endl;
                    //std::cout << R[combinedIndexL[i]] << std::endl;
                    mmax = 2*combIndex[i][2]+1;
                    //std::cout << combIndex[i][0] << std::endl;
                    //std::cout << alpha[combIndex[i][0]][isymm] << std::endl;
                    //std::cout << L[combIndex[i][2]][isymm] << std::endl;
                    //std::cout << alpha[combIndex[i][0]][isymm] << std::endl;
                    if( alpha[combIndex[i][0]][isymm] == combIndex[i][1] ) {
                        O.block(i,i,mmax,mmax) = L[combIndex[i][2]][isymm];
                    }
                    i += mmax;
                }
                Eigen::MatrixXcd G = gf.get(ikpoints, ienergy);
                //std::cout << std::fixed << std::setprecision(1) << O << std::endl;
                OGO.setZero();
                OGO = O.adjoint()*G*O;
                //temp = OGO + temp;
                //std::cout << OGO << std::endl;
                OGOsum += OGO*weight[ikpoints];
			}
            
		}
        GFlocal.col(ienergy) = OGOsum.diagonal()/weightSum;
        
	}
    gflocal.initialize(gf.getEmin(), gf.getEmax(), gf.getDe(), gf.getEta(), gf.getEnergy(), gf.getCombinedIndex());
    gflocal.set(0, GFlocal);
    //std::cout << std::fixed << std::setprecision(3) << std::setw(3) << gflocal.get(0) << std::endl;
}

void KSymmSum::generateLMatrix(std::vector<std::vector<Eigen::MatrixXcd> >& Symm, std::vector<Eigen::MatrixXcd>& U, std::vector<std::vector<Eigen::MatrixXcd> >& L) {
	unsigned int Nl, Nsymm;
	Nl = Symm.size();
    L.resize(Nl);
    for (unsigned int il = 0; il < Nl; il++) {
        Nsymm = Symm[il].size();
        L[il].resize(Nsymm);
        for (unsigned int isymm = 0; isymm < Nsymm; isymm++) {
            L[il][isymm] = U[il]*Symm[il][isymm]*U[il].adjoint();
            //cout << L[il][isymm] << endl;
        }
    }
}

void KSymmSum::generateUMatrix(std::vector<Eigen::MatrixXcd>& R, std::vector<Eigen::MatrixXcd>& S, std::vector<Eigen::MatrixXcd>& U) {

	U.resize(S.size());

	for(unsigned int i = 0; i < S.size(); i++) {
		U[i] = S[i]*R[i];
	}

}
