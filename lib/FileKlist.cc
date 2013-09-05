/*
 * FileKlist.cc
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#include "FileKlist.h"

FileKlist::FileKlist(std::string fn) : FileGeneral::FileGeneral(fn, "klist") {}
FileKlist::~FileKlist() {}

void FileKlist::read(std::vector<Eigen::Vector3d>& kpoints) {
    int Nkpoints = 0;
    std::string line;
	
	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);
			
			if (line.length() > 54) {
				if (line.substr(0,3).compare("END") != 0) {
					std::stringstream s(line.substr(0,50));
                    s >> Nkpoints;
                    double xi, yi, zi;
                    double div;
                    s >> xi;
                    s >> yi;
                    s >> zi;
                    s >> div;
                    //std::cout << Nkpoints << " " << xi << " " << yi << " " << zi << " " << div << std::endl;
					
                    kpoints.resize(Nkpoints);
                    Eigen::Vector3d tempVec;
                    tempVec(0) = xi/div;
                    tempVec(1) = yi/div;
                    tempVec(2) = zi/div;
                    kpoints[Nkpoints-1] = tempVec;
				}
			}



		}
	}

}
