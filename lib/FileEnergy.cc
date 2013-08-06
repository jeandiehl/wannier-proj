/*
 * FileEnergy.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#include "FileEnergy.h"

FileEnergy::FileEnergy(std::string fn) : FileGeneral::FileGeneral(fn, "energy") {}
FileEnergy::~FileEnergy() {}

void FileEnergy::read (std::vector<std::vector<double> >& energy) {
unsigned int Nkpoints = 0; // indexing the kpoints

	std::string line;
	
	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);
			
			if (line.length() > 84) {
				
				if (line.substr(0,1).compare(" ") == 0 && line.substr(57,6).compare("      ") == 0) {
					std::stringstream s(line.substr(57,10));
					
					s >> Nkpoints;
					energy.resize(Nkpoints);
				}
				
				
			}
			
			if (line.length() > 30) {
				if (line.substr(0,8).compare("        ") == 0) {
					std::stringstream s(line.substr(0,31));
					
					int temp1 = 0;
					s >> temp1;
					
					double temp2 = 0.0;
					
					std::string temp3 = line.substr(13,23);

					unsigned int size = temp3.length();
					// collapse multiple spaces to one
					while (temp3.find("  ") >= 0 && temp3.find("  ") < size) {
						//cout << temp3.find("  ") << endl;
						temp3.replace(temp3.find("  "), 2, " ");
					}

					if (temp3.substr(0,1).compare(" ") == 0) {
						temp3 = temp3.substr(1,temp3.length());
					}

					if (temp3.substr(temp3.length()-1,1).compare(" ") == 0) {
						temp3 = temp3.substr(0,temp3.length()-2);

					}

					temp2 = boost::lexical_cast<double>(temp3);
					
					//cout << temp1 << " " << temp2 << endl;
					//energy[Nkpoints-1].resize(temp1);
					//energy[Nkpoints-1][temp1] = temp2;
					energy[Nkpoints-1].push_back(temp2);
					//cout << energy[Nkpoints-1][temp1] << endl;
				}
			}

		}
	}

}

void FileEnergy::read (std::vector<std::vector<double> >& energy, std::vector<double>& weight) {
unsigned int Nkpoints = 0; // indexing the kpoints
double Nweight = 0.0;
	std::string line;
	
	if (myfile.is_open()) {
		while ( myfile.good() ) {
			getline (myfile,line);
			
			if (line.length() > 84) {
				
				if (line.substr(0,1).compare(" ") == 0 && line.substr(57,6).compare("      ") == 0) {
					std::stringstream s(line.substr(57,10));
					
					s >> Nkpoints;
					energy.resize(Nkpoints);
					weight.resize(Nkpoints);

					std::stringstream s1(line.substr(79,8));
					s1 >> Nweight;
					weight[Nkpoints-1] = Nweight;
				}
				
				
			}
			
			if (line.length() > 30) {
				if (line.substr(0,8).compare("        ") == 0) {
					std::stringstream s(line.substr(0,31));
					
					int temp1 = 0;
					s >> temp1;
					
					double temp2 = 0.0;
					
					std::string temp3 = line.substr(13,23);

					unsigned int size = temp3.length();
					// collapse multiple spaces to one
					while (temp3.find("  ") >= 0 && temp3.find("  ") < size) {
						//cout << temp3.find("  ") << endl;
						temp3.replace(temp3.find("  "), 2, " ");
					}

					if (temp3.substr(0,1).compare(" ") == 0) {
						temp3 = temp3.substr(1,temp3.length());
					}

					if (temp3.substr(temp3.length()-1,1).compare(" ") == 0) {
						temp3 = temp3.substr(0,temp3.length()-2);

					}

					temp2 = boost::lexical_cast<double>(temp3);
					
					//cout << temp1 << " " << temp2 << endl;
					//energy[Nkpoints-1].resize(temp1);
					//energy[Nkpoints-1][temp1] = temp2;
					energy[Nkpoints-1].push_back(temp2);
					//cout << energy[Nkpoints-1][temp1] << endl;
				}
			}

		}
	}

}
