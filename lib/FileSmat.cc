/*
 * FileSmat.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#include "FileSmat.h"

FileSmat::FileSmat(std::string fn) : FileGeneral::FileGeneral(fn, "smat") {}
FileSmat::~FileSmat() {}

void FileSmat::read (std::vector<Eigen::MatrixXcd>& S) {
	std::string line;
	std::string s;

	unsigned int LMAX = 3;
	
	S.resize(LMAX+1);

	int l = 0;
	int row = 0;
	Eigen::MatrixXcd Sl(1,1);

	double S_real, S_imag;
	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);

			if (line.length() > 25) {
				// look for lines identifiing an orbital l
				if (line.substr(15,11).compare("(orbital l)") == 0) {
					//cout << Sl << endl;
					S[l] = Sl;
					std::stringstream s(line.substr(0,25));
					s >> l;
					//cout << l << endl;
					
					row = 0;
					Sl.resize(2*l+1,2*l+1);
				}

				if(line.substr(0,2).compare(" (") == 0) {
					std::stringstream s(line.substr(2,line.find(",")-2));
					s >> S_real;
					std::stringstream s2(line.substr(line.find(",")+1, line.find(")")-line.find(",")-1));
					s2 >> S_imag;
					//cout << line.substr(2,line.find(",")-2) << " " << line.substr(line.find(",")+1, line.find(")")-line.find(",")-1) << " " << row/(2*l+1) << " " << row%(2*l+1) << endl;
					Sl(row/(2*l+1), row%(2*l+1)) = std::complex<double> (S_real, S_imag);
					row++;
				}
			}
		}
		S[l] = Sl;
	}
	
	
	
}
