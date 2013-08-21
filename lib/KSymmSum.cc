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
    
    Eigen::MatrixXcd OGOsumReduced;

    std::vector<std::vector<int> > combIndexReduced;

    int NcombIndexReduced = 0;
    for(unsigned int i = 0; i < NcombIndex; i++) {
		if(combIndex[i][1] == 0) {
			NcombIndexReduced++;
			combIndexReduced.resize(NcombIndexReduced);
			combIndexReduced[NcombIndexReduced-1].resize(4);
			combIndexReduced[NcombIndexReduced-1][0] = combIndex[i][0];
			combIndexReduced[NcombIndexReduced-1][1] = combIndex[i][1];
			combIndexReduced[NcombIndexReduced-1][2] = combIndex[i][2];
			combIndexReduced[NcombIndexReduced-1][3] = combIndex[i][3];
		}
	}
	GFlocal.resize(NcombIndexReduced, Nenergy);
    GFlocal.setZero();
	//std::cout << NcombIndexReduced << std::endl;
    OGOsumReduced.resize(NcombIndexReduced, NcombIndexReduced);
    
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
		Eigen::MatrixXcd temp;
		unsigned int mult;
		//std::cout << std::fixed << std::setprecision(3) << std::setw(3) << OGOsum << std::endl << std::endl;
		for(unsigned i = 0; i < NcombIndex; i++) {
			mult = combIndex[i][1];
			if(mult > 0) {
				//std::cout << "i " << i << std::endl;
				//std::cout <<  2*combIndex[i][2]+1 << std::endl;
				temp.resize(2*combIndex[i][2]+1, 2*combIndex[i][2]+1);
				temp.setZero();
				//std::cout << temp << std::endl;
				//std::cout << 2*combIndex[i][2]+1 << std::endl;
////std::cout << temp << std::endl << std::endl;
				temp = OGOsum.block(i,i,2*combIndex[i][2]+1,2*combIndex[i][2]+1);
				//std::cout << std::fixed << std::setprecision(3) << std::setw(3) << temp << std::endl << std::endl;
				//std::cout << std::fixed << std::setprecision(3) << std::setw(3) << OGOsum.block(i-(2*combIndex[i][2]+1),i-(2*combIndex[i][2]+1),2*combIndex[i][2]+1,2*combIndex[i][2]+1) << std::endl;
				//std::cout << i << std::endl;
				//std::cout << i-(2*combIndex[i][2]+1) << std::endl;
				//std::cout << 2*combIndex[i][2]+1 << std::endl;
				OGOsum.block(i-mult*(2*combIndex[i][2]+1),i-mult*(2*combIndex[i][2]+1),2*combIndex[i][2]+1,2*combIndex[i][2]+1) += temp;
				OGOsum.block(i,i,2*combIndex[i][2]+1,2*combIndex[i][2]+1).setZero();
			}
			
			i += 2*combIndex[i][2];
		}
		int j = 0;
		for(unsigned int i = 0; i < NcombIndex; i++) {
			if(combIndex[i][1] == 0) {
				OGOsumReduced.block(j,j,2*combIndex[i][2]+1,2*combIndex[i][2]+1) = OGOsum.block(i,i,2*combIndex[i][2]+1,2*combIndex[i][2]+1);
				j += 2*combIndex[i][2]+1;
			}
			i += 2*combIndex[i][2];
		}
		
		//std::cout << std::fixed << std::setprecision(3) << std::setw(3) << OGOsum << std::endl << std::endl;
		//std::cout << std::fixed << std::setprecision(3) << std::setw(3) << OGOsumReduced << std::endl << std::endl;
        GFlocal.col(ienergy) = OGOsumReduced.diagonal()/weightSum/Nsymm;

        
        
	}
	//for(int i = 0; i < combIndexReduced.size(); i++) {
		//std::cout << combIndexReduced[i][0] << " " << combIndexReduced[i][1] << " "<< combIndexReduced[i][2] << " "<< combIndexReduced[i][3] << " "<< std::endl;
	//}
    gflocal.initialize(gf.getEmin(), gf.getEmax(), gf.getDe(), gf.getEta(), gf.getEnergy(), combIndexReduced);
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
