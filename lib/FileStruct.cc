/*
 * FileStruct.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#include "FileStruct.h"

FileStruct::FileStruct(std::string fn) : FileGeneral::FileGeneral(fn, "struct") {}
FileStruct::~FileStruct() {}

void FileStruct::read (std::vector<int>& mult, std::vector<std::string>& atomNames) {
	int Natom = 0;
	unsigned int Nmult = 0;
	std::string atomName = "";
	std::string line;
	
	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);
			
			if (line.length() > 7) {
				if (line.substr(0,4).compare("ATOM") == 0) {
					std::stringstream s(line.substr(4,4));
					
					s >> Natom;
					if(Natom < 0) {
						Natom *= -1;
					}
					mult.resize(Natom);
					atomNames.resize(Natom);
				}
			}

			if (line.length() > 16) {
				if (line.substr(10,4).compare("MULT") == 0) {
					std::stringstream s(line.substr(15,2));
					
					s >> Nmult;
					mult[Natom-1] = Nmult;
				}
			}

			if (line.length() > 16) {
				if (line.substr(11,4).compare("NPT=") == 0) {
					atomName = line.substr(0,2);
					atomNames[Natom-1] = atomName;
				}
			}

		}
	}

}


void FileStruct::read (std::vector<int>& mult, std::vector<std::string>& atomNames, std::vector<std::vector<Eigen::Vector3d> >& atomPositions) {
	int Natom = 0;
	unsigned int Nmult = 0;
	std::string atomName = "";
	std::string line;
	
	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);
			
			if (line.length() > 7) {
				if (line.substr(0,4).compare("ATOM") == 0) {
					std::stringstream s(line.substr(4,4));
					
					s >> Natom;
					if(Natom < 0) {
						Natom *= -1;
					}
					mult.resize(Natom);
					atomNames.resize(Natom);
				}
			}

			if (line.length() > 16) {
				if (line.substr(10,4).compare("MULT") == 0) {
					std::stringstream s(line.substr(15,2));
					
					s >> Nmult;
					mult[Natom-1] = Nmult;
				}
			}

			if (line.length() > 16) {
				if (line.substr(11,4).compare("NPT=") == 0) {
					atomName = line.substr(0,2);
					atomNames[Natom-1] = atomName;
				}
			}
            
			if (line.length() > 46) {
				if (line.substr(8,4).compare(": X=") == 0) {
                    std::stringstream s1(line.substr(12,12));
					double temp1;
                    s1 >> temp1;
                    
                    std::stringstream s2(line.substr(25,12));
					double temp2;
                    s2 >> temp2;
                    
                    std::stringstream s3(line.substr(38,12));
					double temp3;
                    s3 >> temp3;
                    
                    Eigen::Vector3d tempVec;
                    tempVec(0) = temp1;
                    tempVec(1) = temp2;
                    tempVec(2) = temp3;
                    
                    atomPositions.resize(Natom);
                    atomPositions[Natom-1].push_back(tempVec);
                    //std::cout << atomPositions[Natom-1] << std::endl << std::endl;
				}
			}

		}
	}

}
