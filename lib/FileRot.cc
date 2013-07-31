/*
 * FileRot.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#include "FileRot.h"

FileRot::FileRot(std::string fn) : FileGeneral::FileGeneral(fn, "rot") {}
FileRot::~FileRot() {}

void FileRot::read (std::vector<Eigen::MatrixXcd>& R) {
	std::string line;
	std::string s;

	unsigned int LMAX = 3;
	
	R.resize(LMAX+1);




	// resize in advance to avoid problems if not all orbitals
	// with quantum number l are listed
	for (unsigned int i = 0; i < LMAX+1; i++) {
		for (unsigned int j1 = -i; j1 < i+1; j1++) {
			for (unsigned int j2 = -i; j2 < i+1; j2++) {
				R[i].resize(2*i+1,2*i+1);
				R[i](j1+i,j2+i) = std::complex<double> (0.0,0.0);
			}
			R[i](j1+i,j1+i) = std::complex<double> (1.0,0.0);
		}
	}

	int l = 0;
	int row = 0;
	Eigen::MatrixXcd Rl(1,1);
	Rl(0,0) = std::complex<double> (1.0,0.0);
	R[0] = Rl;

	double R_real, R_imag;
	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);

			if (line.length() > 25) {
				// look for lines identifiing an orbital l
				if (line.substr(15,11).compare("(orbital l)") == 0) {
					//cout << Rl << endl;
					R[l] = Rl;
					std::stringstream s(line.substr(0,25));
					s >> l;
					//cout << l << endl;
					
					row = 0;
					Rl.resize(2*l+1,2*l+1);
				}

				if(line.substr(0,2).compare(" (") == 0) {
					std::stringstream s(line.substr(2,line.find(",")-2));
					s >> R_real;
					std::stringstream s2(line.substr(line.find(",")+1, line.find(")")-line.find(",")-1));
					s2 >> R_imag;
					//cout << line.substr(2,line.find(",")-2) << " " << line.substr(line.find(",")+1, line.find(")")-line.find(",")-1) << " " << row/(2*l+1) << " " << row%(2*l+1) << endl;
					Rl(row/(2*l+1), row%(2*l+1)) = std::complex<double> (R_real, R_imag);
					row++;
				}
			}
		}
		R[l] = Rl;
		// following not needed anymore, because implemented at the beginning
		// of this function
		Rl.resize(7,7);
		for(int i = 0; i < 7; i++) {
			for(int j = 0; j < 7; j++) {
				Rl(i,j) = std::complex<double> (0.0,0.0); 
			}
			Rl(i,i) = std::complex<double> (1.0,0.0);
		}
		R[l+1] = Rl;
		}
	
	
}
