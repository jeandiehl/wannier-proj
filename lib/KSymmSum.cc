/*
 * KSymmSum.cc
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#include "KSymmSum.h"

KSymmSum::KSymmSum(std::vector<std::vector<Eigen::MatrixXcd> >& Symm, std::vector<std::vector<int> >& alpha, std::vector<Eigen::MatrixXcd>& R, std::vector<Eigen::MatrixXcd>& S, std::vector<double>& wweight) : weight(wweight) {
	generateUMatrix(R, S, U);
	generateLMatrix(Symm, U, L);
}
KSymmSum::~KSymmSum() {}

void KSymmSum::calculate(GreensFunction& gf, GreensFunction& gflocal) {
	
	Eigen::MatrixXcd O;
	std::vector<std::vector<int> > combIndex = gf.getCombinedIndex();
	
	unsigned int NcombIndex = combIndex.size();
	std::cout << NcombIndex << std::endl;
	O.resize(NcombIndex,NcombIndex);
	
	unsigned int Nkpoints = gf.getMaxNkpoints();
	unsigned int Nsymm = L[0].size();
	for(unsigned int ikpoints = 0; ikpoints < 1; ikpoints++) {
		for(unsigned int isymm = 0; isymm < 1; isymm++) {
				O.setZero();
				unsigned int i = 0;
				unsigned int mmax = 0;
				while(i < NcombIndex) {
					//std::cout << S[combinedIndexL[i]] << std::endl;
					//std::cout << R[combinedIndexL[i]] << std::endl;
					mmax = 2*combIndex[i][4]+1;
					O.block(i,i,mmax,mmax) = L[combIndex[i][4]][isymm];
					i += mmax;
				}
				std::cout << O << std::endl;
		}
	}
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
