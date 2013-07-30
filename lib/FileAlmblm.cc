/*
 * FileAlmblm.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#include "FileAlmblm.h"
#include "FileGeneral.h"

FileAlmblm::FileAlmblm(std::string fn) : FileGeneral::FileGeneral(fn, "almblm") {}

FileAlmblm::~FileAlmblm() {}

void FileAlmblm::read(GeneralCoefficient<std::complex<double> >& Alm, GeneralCoefficient<Eigen::Vector3cd>& Clm, GeneralCoefficient<Eigen::Vector3cd>& O) {
	std::string line;
	std::string s;
	std::string str;

	unsigned int Nkpoints, Njatom, Natom, Nenergy;
	
	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);
			// save list of kpoints to kpoints Matrix
			if (line.length() > 73) {
				// look for lines identifiing a kpoint
				if (line.substr(2,7).compare("K-POINT") == 0) {
					std::stringstream s(line.substr(62,12));
					s >> Nkpoints;
				}
				
			}

            // save irreducible to reducible atom number conversion
            if (line.length() > 54) {
                if (line.substr(38,17).compare("jatom,nemin,nemax") == 0) {
					std::stringstream s(line);
					s >> Njatom;
					
				}
            }

			// check for atom number
			if (line.length() > 18) {
				if (line.substr(15,4).compare("ATOM") == 0) {
					std::stringstream s(line.substr(11,1));
					s >> Natom;
				}
			}

			// save energies for each kpoint to energy first; index 
			// k-point index, second band index from 0..n-1
			if (line.length() > 78) {
				// look for lines identifiing an energy
				if (line.substr(62,17).compare("NUM,energy,weight") == 0) {
					std::stringstream s(line.substr(0,12));
					s >> Nenergy;
				}
			}

			// save the alm
			if (line.length() > 225) {
				if (line.substr(0,3).compare("   ") == 0) {
					std::stringstream s(line.substr(3,222));
					std::cout << Nkpoints << " " << Njatom << " " << Natom << " " << Njatom << " " << Nenergy << " " << std::endl;

					int l, m;
					double alm_real, alm_imag, blm_real, blm_imag, clm_real, clm_imag, clmOver;
					s >> l;
					s >> m;

					
					s >> alm_real;
					s >> alm_imag;

					// skip blm since corresponding states are orthogonal
					s >> blm_real;
					s >> blm_imag;

					// save the 3 clm
					std::complex<double> temp;
					std::vector<std::complex<double> > tempVec;
					for(int i = 0; i < 3; i++) {
						s >> clm_real;
						s >> clm_imag;
						temp = std::complex<double> (clm_real, clm_imag);
						tempVec.push_back(temp);
					}
					

					
					// save the 3 overlaps between the clm's
					std::vector<double> tempVecOver;
					for(int i = 0; i < 3; i++) {
						s >> clmOver;
						tempVecOver.push_back(clmOver);
					}
					
				}

			}



				
		}
	}


}
