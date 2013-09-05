/*
 * FilePsink.cc
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#include "FilePsink.h"

FilePsink::FilePsink(std::string fn) : FileGeneral::FileGeneral(fn, "psink") {}
FilePsink::~FilePsink() {}

void FilePsink::read(WaveFunction& psi) {
    int Nkpoints = 1;
    int Nenergy = 0;
    int NspaceIndex = 0;
    
    std::string line;
    Eigen::MatrixXcd wf;
    wf.resize(1,NspaceTotal);
    wf.setZero();
    
    Eigen::VectorXcd wfRow;
	wfRow.resize(NspaceTotal);
    wfRow.setZero();
    
	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);
			
			if (line.length() > 66) {
				if (line.substr(0,3).compare("k =") == 0) {
                    //std::cout << wfRow << std::endl << std::endl;
					std::stringstream s(line.substr(3,6));
                    int NkpointsNew;
                    s >> NkpointsNew;
                    if (NkpointsNew != Nkpoints) {
                        psi.set(Nkpoints-1, wf);
                        wf.resize(1,NspaceTotal);
                        wf.setZero();
                        Nkpoints = NkpointsNew;
                        //std::cout << "test" << std::endl;
                    }
                    std::stringstream s1(line.substr(14,6));
                    s1 >> Nenergy;
                    NspaceIndex = 0;
                    wf.conservativeResize(Nenergy,NspaceTotal);
				}
			}

            if (line.length() > 66) {
				if (line.substr(0,1).compare(" ") == 0 && line.substr(32,4).compare("    ") == 0) {
					std::stringstream s(line);
                    double tempReal, tempImag;
                    NspaceIndex++;
                    s >> tempReal;
                    s >> tempImag;
                    
                    //std::cout << Nenergy-1 << " " << NspaceIndex-1 << std::endl;
                    wf(Nenergy-1,NspaceIndex-1) = std::complex<double> (tempReal, tempImag);
                    NspaceIndex++;
                    s >> tempReal;
                    s >> tempImag;
                    
                    //std::cout << Nenergy-1 << " " << NspaceIndex-1 << std::endl;
                    wf(Nenergy-1,NspaceIndex-1) = std::complex<double> (tempReal, tempImag);
                    
                    //wf.conservativeResize(Nenergy,Nspace);
                    //wf.row(Nenergy-1) = wfRow;
				}
			}
            
		}
	}
    //std::cout << Nkpoints << std::endl;
    psi.set(Nkpoints-1, wf);
}

void FilePsink::initialize(Eigen::Vector3d NNspace) {
    Nspace = NNspace;
    NspaceTotal = 1;
    for (int i = 0; i < 3; i++) {
        NspaceTotal *= Nspace(i);
    }
    //std::cout << NspaceTotal << std::endl;
}
