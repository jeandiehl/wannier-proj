/*
 * FileAlmblm.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#include "FileAlmblm.h"

FileAlmblm::FileAlmblm(std::string fn) : FileGeneral::FileGeneral(fn, "almblm") {}

FileAlmblm::~FileAlmblm() {}

void FileAlmblm::read(GeneralCoefficient<std::complex<double> >& Alm, GeneralCoefficient<Eigen::VectorXcd>& Clm, GeneralCoefficient<Eigen::VectorXcd>& O) {
	std::string line;
	std::string s;
	std::string str;
    int Nkpoints = -1;
	unsigned int Njatom, Natom, Nenergy;
	int Nl, Nm;
	double almReal, almImag, blmReal, blmImag, clmReal, clmImag, clmOver;
	
	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);
			// save list of kpoints to kpoints Matrix
			if (line.length() > 73) {
				// look for lines identifiing a kpoint
				if (line.substr(2,7).compare("K-POINT") == 0) {
					std::stringstream s(line.substr(62,12));
					//s >> Nkpoints;
                    //Nkpoints -= 1;
                    Nkpoints++;
					
				}
				
			}

            // save irreducible to reducible atom number conversion
            if (line.length() > 54) {
                if (line.substr(38,17).compare("jatom,nemin,nemax") == 0) {
					std::stringstream s(line);
					s >> Njatom;
					Njatom -= 1;
				}
            }

			// check for atom number
			if (line.length() > 18) {
				if (line.substr(15,4).compare("ATOM") == 0) {
					std::stringstream s(line.substr(11,1));
					s >> Natom;
					Natom -= 1;
					
				}
			}

			// save energies for each kpoint to energy first; index 
			// k-point index, second band index from 0..n-1
			if (line.length() > 78) {
				// look for lines identifiing an energy
				if (line.substr(62,17).compare("NUM,energy,weight") == 0) {
					std::stringstream s(line.substr(0,12));
					s >> Nenergy;
					Nenergy -= 1;
				}
			}

			// save the alm
			if (line.length() > 225) {
				if (line.substr(0,3).compare("   ") == 0) {
					std::stringstream s(line.substr(3,222));

					s >> Nl;
					s >> Nm;

					s >> almReal;
					s >> almImag;

					Alm.setCoefficient(Nkpoints, Njatom, Natom, Nenergy, Nl, Nl+Nm, std::complex<double> (almReal, almImag) );

					// skip blm since corresponding states are orthogonal
					s >> blmReal;
					s >> blmImag;

					// save the 3 clm
					Eigen::VectorXcd tempVec;
					tempVec.resize(3);
					for(int i = 0; i < 3; i++) {
						s >> clmReal;
						s >> clmImag;
						tempVec(i) = std::complex<double> (clmReal, clmImag);
					}
					//std::cout << tempVec << std::endl;
					Clm.setCoefficient(Nkpoints, Njatom, Natom, Nenergy, Nl, Nl+Nm, tempVec );
					
					
					// save the 3 overlaps between the clm's
					Eigen::VectorXcd tempVecOver;
					tempVecOver.resize(3);
					for(int i = 0; i < 3; i++) {
						s >> clmOver;
						tempVecOver(i) = std::complex<double> (clmOver,0.0);
					}
					O.setCoefficient(Nkpoints, Njatom, Natom, Nenergy, Nl, Nl+Nm, tempVecOver );
				}
			}



				
		}
	}


}
