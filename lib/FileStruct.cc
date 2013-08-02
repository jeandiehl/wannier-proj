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
