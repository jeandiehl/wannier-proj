/*
 * init_smat.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */
 
#include <unistd.h> // for getcwd
#include <fstream> // read/write file
#include <iomanip> // setw
#include <complex>
#include <Eigen/Core>
#include <vector>

int main(int argc, char **argv) {

	int LMAX = 4;
	
	// get current working directory
	char cwd[256];
	getcwd(cwd, sizeof(cwd));
	std::string path = std::string(cwd);
    
    unsigned pos = path.find_last_of("/");
	std::string w2kProjectName = path.substr(pos + 1, path.length() - (pos + 1) );

	std::string filename = w2kProjectName + ".smat";
	std::ofstream myfile(filename.c_str());

	std::vector<Eigen::MatrixXcd > S; 
	Eigen::MatrixXcd Sl(1,1);
	S.resize(LMAX+1);

	Sl(0,0) = std::complex<double> (1.0,0.0);
	S[0] = Sl;
	//cout << S[0] << endl;

	Sl.resize(3,3);
	Sl(0,0) = std::complex<double> (1.0/sqrt(2),0.0);
	Sl(0,1) = std::complex<double> (0.0,0.0);
	Sl(0,2) = std::complex<double> (-1.0/sqrt(2),0.0);
	Sl(1,0) = std::complex<double> (0.0,1.0/sqrt(2));
	Sl(1,1) = std::complex<double> (0.0,0.0);
	Sl(1,2) = std::complex<double> (0.0,1.0/sqrt(2));
	Sl(2,0) = std::complex<double> (0.0,0.0);
	Sl(2,1) = std::complex<double> (1.0,0.0);
	Sl(2,2) = std::complex<double> (0.0,0.0);
	S[1] = Sl;
	//cout << S[1] << endl;

	Sl.resize(5,5);
	Sl(0,0) = std::complex<double> (0.0,0.0);
	Sl(0,1) = std::complex<double> (0.0,0.0);
	Sl(0,2) = std::complex<double> (1.0,0.0);
	Sl(0,3) = std::complex<double> (0.0,0.0);
	Sl(0,4) = std::complex<double> (0.0,0.0);
	Sl(1,0) = std::complex<double> (1.0/sqrt(2),0.0);
	Sl(1,1) = std::complex<double> (0.0,0.0);
	Sl(1,2) = std::complex<double> (0.0,0.0);
	Sl(1,3) = std::complex<double> (0.0,0.0);
	Sl(1,4) = std::complex<double> (1.0/sqrt(2),0.0);
	Sl(2,0) = std::complex<double> (0.0,1.0/sqrt(2));
	Sl(2,1) = std::complex<double> (0.0,0.0);
	Sl(2,2) = std::complex<double> (0.0,0.0);
	Sl(2,3) = std::complex<double> (0.0,0.0);
	Sl(2,4) = std::complex<double> (0.0,-1.0/sqrt(2));
	Sl(3,0) = std::complex<double> (0.0,0.0);
	Sl(3,1) = std::complex<double> (1.0/sqrt(2),0.0);
	Sl(3,2) = std::complex<double> (0.0,0.0);
	Sl(3,3) = std::complex<double> (-1.0/sqrt(2),0.0);
	Sl(3,4) = std::complex<double> (0.0,0.0);
	Sl(4,0) = std::complex<double> (0.0,0.0);
	Sl(4,1) = std::complex<double> (0.0,1.0/sqrt(2));
	Sl(4,2) = std::complex<double> (0.0,0.0);
	Sl(4,3) = std::complex<double> (0.0,1.0/sqrt(2));
	Sl(4,4) = std::complex<double> (0.0,0.0);
	S[2] = Sl;
	//cout << S[2] << endl;

	Sl.resize(7,7);
	for(int i = 0; i < 7; i++) {
		for(int j = 0; j < 7; j++) {
			Sl(i,j) = std::complex<double> (0.0,0.0); 
		}
		Sl(i,i) = std::complex<double> (1.0,0.0);
	}
	S[3] = Sl;

	for(int i = 0; i < LMAX; i++) {
		myfile << std::setw(12) << i << "   (orbital l)" << std::endl;
		for(int j = 0; j < 2*i + 1; j++) {
			for(int k = 0; k < 2*i + 1; k++) {
				myfile << " (" << std::setw(15) << std::setprecision(15) << std::scientific << real(S[i](j,k)) << ", " << imag(S[i](j,k)) << ")" <<std::endl;
			}
		}
		
		
	}
	
	myfile.close();
    
	return 0;
}

