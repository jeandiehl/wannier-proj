/*
 * FileInproj.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#include "FileInproj.h"

FileInproj::FileInproj(std::string fn) : FileGeneral::FileGeneral(fn, "inproj") {}
FileInproj::~FileInproj() {}

void FileInproj::read (double& Emin, double& Emax, std::vector<std::vector<std::vector<int > > >& selOrb) {
	int LMAX = 3;
	int ATOMMAX = 4;
	
	selOrb.resize(ATOMMAX);
    for (int i = 0; i < ATOMMAX; i++) {
        selOrb[i].resize(LMAX+1);
        for (int j = 0; j < LMAX+1; j++) {
            selOrb[i][j].resize(2*j + 1, 0);
        }
    }
    
	std::string line;
	

	int Natom, iatom, jmax, il, Nm;
	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);
			std::stringstream s(line);
			s >> Natom;
			//cout << Natom << endl;
			
			for(int i = 0; i < Natom; i++) {
				getline (myfile,line);
				std::stringstream s1(line);
				s1 >> iatom;
				//cout << iatom << endl;

				s1 >> jmax;
				for(int j = 0; j < jmax; j++) {
					s1 >> il;
					//cout << "il " << il << endl;
					Nm = selOrb[iatom-1][il].size();
					for(int im = 0; im < Nm; im++) {
						selOrb[iatom-1][il][im] = 1;
					}
					
				}
			}
			getline (myfile,line);
			std::stringstream s2(line);
			s2 >> Emin;
			s2 >> Emax;
			break;
		}
	}
}
