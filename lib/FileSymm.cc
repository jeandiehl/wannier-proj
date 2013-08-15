/*
 * FileSymm.cc
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#include "FileSymm.h"

FileSymm::FileSymm(std::string fn) : FileGeneral::FileGeneral(fn, "symm") {}
FileSymm::~FileSymm() {}

void FileSymm::read(std::vector<std::vector<Eigen::MatrixXcd> >& Symm, std::vector<std::vector<int> >& alpha, std::vector<std::string>& atomNames) {
	std::string line;
	unsigned int Nl, Nsymm;
    Nl = 0;
    Nsymm = 0;
    int row = 0;
    
    Eigen::MatrixXcd Symm1;
    Symm1.resize(1,1);
    Symm1(0,0) = std::complex<double> (1.0,0.0);
    double Symm_real, Symm_imag;
    
    Symm.resize(1);
    Symm[0].resize(1);
    Symm[0][0] = Symm1;
    std::string atomName1 = "";
    int atomIndex = -1;
    int SymmAtomIndex1 = -1;
	
	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);
            
            if (line.length() > 25) {
				// look for lines identifiing an orbital l
				if (line.substr(15,11).compare("(orbital l)") == 0) {
                    std::stringstream s(line);
                    
                    s >> Nl;
                    //cout << Nl << endl;
                    row = 0;
                    //cout << Symm1 << endl;
                    if (Nl > 1) {
                        //cout << "Nl " << Nl-1 << " Nsymm " << Nsymm-1 << endl;
                        Symm[Nl-1][Nsymm-1] = Symm1;
                        //cout << fixed << setprecision(4) << Symm[Nl-1][Nsymm-1] << endl;
                    }
                    
					Symm1.resize(2*Nl+1,2*Nl+1);
                    Symm.resize(Nl+1);
                }
            }
            
            if (line.length() > 27) {
				// look for lines identifiing an orbital l
				if (line.substr(15,13).compare("(symmetry ID)") == 0) {
                    std::stringstream s(line);
                    
                    s >> Nsymm;
                    if (Nsymm>1) {
                        //cout << "Nl " << Nl << " Nsymm " << Nsymm-2 << endl;
                        Symm[Nl][Nsymm-2] = Symm1;
                        //cout << fixed << setprecision(4) << Symm[Nl][Nsymm-2] << endl;
                    }
                    
                    //Symm[Nl][Nsymm] = Symm1;
                    //cout << Nsymm << endl;
                    
                    row = 0;
                    
                    Symm[Nl].resize(Nsymm);
                }
            
            
                if(line.substr(0,2).compare(" (") == 0) {
					std::stringstream s(line.substr(2,line.find(",")-2));
					s >> Symm_real;
					std::stringstream s2(line.substr(line.find(",")+1, line.find(")")-line.find(",")-1));
					s2 >> Symm_imag;
					//cout << line.substr(2,line.find(",")-2) << " " << line.substr(line.find(",")+1, line.find(")")-line.find(",")-1) << " " << row/(2*Nl+1) << " " << row%(2*Nl+1) << endl;
					Symm1(row/(2*Nl+1), row%(2*Nl+1)) = std::complex<double> (Symm_real, Symm_imag);
					row++;
				}
            }
            if (line.length() > 20) {
                
                if (line.substr(12,9).compare("(atom ID)") == 0) {
                    std::stringstream s(line);
                    s >> atomName1;
                    //std::cout << atomName1 << std::endl;
                    atomIndex = getAtomIndex(atomName1, atomNames);
                    
                    //std::cout << atomIndex << std::endl;
                    alpha.resize(atomIndex+1);
                    alpha[atomIndex].resize(Nsymm);
                    getline (myfile,line);
                    std::stringstream s1(line);
                    for (unsigned int i = 0; i < Nsymm; i++) {
                        s1 >> SymmAtomIndex1;
                        //std::cout << SymmAtomIndex1 << std::endl;
                        alpha[atomIndex][i] = SymmAtomIndex1 - 1;
                        //std::cout << alpha[atomIndex][i] << std::endl;
                    }
                }
            }
        }
    }
    //cout << "Nl " << Nl << " Nsymm " << Nsymm-1 << endl;
    Symm[Nl][Nsymm-1] = Symm1;
    //cout << fixed << setprecision(4) << Symm[Nl][Nsymm-1] << endl;
    
    

}

int FileSymm::getAtomIndex(std::string atomName, std::vector<std::string>& atomNames) {
	int value = -1;
	unsigned int NatomNames = atomNames.size();
	for(unsigned int i = 0; i < NatomNames; i++) {
		if(atomName.compare(atomNames[i]) == 0) {
			value = i;
			break;
		}  else {
			value = -1;
		}
	}
	return value;
}
