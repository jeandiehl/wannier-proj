/*
 * FileIn7.cc
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#include "FileIn7.h"

FileIn7::FileIn7(std::string fn) : FileGeneral::FileGeneral(fn, "in7") {}
FileIn7::~FileIn7() {}

void FileIn7::read(Eigen::Vector3d& Nspace) {
    std::string line;

	if (myfile.is_open()) {
        for (int i = 0; i < 6; i++) {
            getline (myfile,line);
            
        }
        //std::cout << line << std::endl;
        std::stringstream s(line);
        for (int i = 0; i < 3; i++) {
            double temp;
            s >> temp;
            Nspace(i) = temp;
        }
            
		
	}
    
}

void FileIn7::read(Eigen::Vector3d& Nspace, std::vector<Eigen::Vector3d >& selectedCell) {
    std::string line;
    selectedCell.resize(4);

	if (myfile.is_open()) {
		double temp = 0.0;
        getline(myfile, line);

        for(int j = 0; j < 4; j++) {
			getline(myfile, line);
			std::stringstream s1(line);
			for (int i = 0; i < 3; i++) {
				s1 >> temp;
				selectedCell[j](i) = temp;
			}
			s1 >> temp;
			selectedCell[j] /= temp;
		}

		getline(myfile, line);
        //std::cout << line << std::endl;
        std::stringstream s(line);
        for (int i = 0; i < 3; i++) {
            s >> temp;
            Nspace(i) = temp;
        }
            
		
	}
    
}
