/*
 * plot_dos.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */


#include <complex>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <cstdlib>

void deleteMultipleSpaces(std::string& input) {
	while (input.find("  ") >= 0 && input.find("  ") < input.length()) {
		input.replace(input.find("  "),2," ");
	}
	if(input.substr(0,1).compare(" ") == 0) {
		input = input.substr(1,input.length()-1);
	}
	if(input.substr(input.length()-1,1).compare(" ") == 0) {
		input = input.substr(0,input.length()-1);
	}
}

int main(int argc, char **argv) {

	//std::cout << argv[1] << std::endl;

	// read plot file options
	std::ifstream infile;
	std::string filenameinput = argv[1];
	
	infile.open(filenameinput.c_str());
	std::string line;

	std::string name;
	int ndos = 0;
	int nenrg = 0;
	double EF = 0.0;
	std::vector<std::string> partialNames;
	
	
	
	if (infile.is_open()) {
		
			getline (infile,line);
			if(line.substr(0,1).compare("#") == 0) {
				//std::cout << "." << line << "." << std::endl;
				name = line.substr(2,line.length()-2);
				deleteMultipleSpaces(name);
			}
			getline (infile,line);
			if(line.substr(0,1).compare("#") == 0) {
				std::stringstream s2(line.substr(4,15));
				s2 >> EF;
				std::stringstream s(line.substr(24,7));
				s >> ndos;
				std::stringstream s1(line.substr(37,9));
				s1 >> nenrg;
			}
			getline (infile,line);
			if(line.substr(0,1).compare("#") == 0) {
				partialNames.resize(ndos);
				for(int i = 0; i < ndos; i++) {
					partialNames[i] = line.substr(12+14*i,14);
					deleteMultipleSpaces(partialNames[i]);
					//std::cout << "." << partialNames[i] << "." << std::endl;
				}
				

			}
		
	}
	//std::cout << name << std::endl;
	//std::cout << ndos << std::endl;
	//std::cout << nenrg << std::endl;
	//std::cout << EF << std::endl;
	
	
	infile.close();

	std::string plt = ".plt";

	std::string pltfilename = argv[1] + plt;
	std::ofstream outfile;
	
	outfile.open(pltfilename.c_str());
    outfile << "#!/usr/bin/gnuplot -persist" << std::endl;
    outfile << "set terminal epslatex color newstyle size 15cm, 10cm standalone" << std::endl;
    std::string texfile = argv[1];
    //std::cout << texfile.replace(texfile.find("."),1,"_") << std::endl;
    outfile << "set output \"" << texfile.replace(texfile.find("."),1,"_") <<".tex\"" << std::endl << std::endl;
    
    outfile << "set xrange[-3:5]" << std::endl;
    outfile << "set xlabel \"energy / eV\"" << std::endl << std::endl;

    outfile << "set ylabel \"DOS states/eV/spin\"" << std::endl;
    outfile << "set title \"" << name << "\"" << std::endl << std::endl;

    outfile << "set mxtics 5" << std::endl;
    outfile << "set style line 20 lt 1 lw 3 lc rgb \"#808080\"" << std::endl;
    outfile << "set style line  1 lt 1 lw 3 lc rgb \"#ee4035\"" << std::endl;
    outfile << "set style line  3 lt 1 lw 3 lc rgb \"#b04c6e\"" << std::endl;
    outfile << "set style line  5 lt 1 lw 3 lc rgb \"#6a51a2\"" << std::endl;
    outfile << "set style line  7 lt 1 lw 3 lc rgb \"#256fb8\"" << std::endl;
    outfile << "set style line  9 lt 1 lw 3 lc rgb \"#0086cf\"" << std::endl;
    outfile << "set style line 11 lt 1 lw 3 lc rgb \"#019c96\"" << std::endl;
    outfile << "set style line  2 lt 1 lw 3 lc rgb \"#3cb74f\"" << std::endl;
    outfile << "set style line  4 lt 1 lw 3 lc rgb \"#aece3c\"" << std::endl;
    outfile << "set style line  6 lt 1 lw 3 lc rgb \"#ffeb01\"" << std::endl;
    outfile << "set style line  8 lt 1 lw 3 lc rgb \"#febb12\"" << std::endl;
    outfile << "set style line 10 lt 1 lw 3 lc rgb \"#f78f1e\"" << std::endl;
    outfile << "set style line 12 lt 1 lw 3 lc rgb \"#f36b2d\"" << std::endl << std::endl;

	outfile << "plot";
	
    if(argc > 3) {
		std::string compareSwitch = argv[2];
		if(compareSwitch.compare("-c") == 0) {
			for(int i = 0; i < ndos; i++) {
				outfile << " '" << argv[3] << "' using 1:" << i+2 << " with lines notitle '" << partialNames[i] << "' ls 20, ";
			}
			for(int i = 0; i < ndos; i++) {
				if(argc > 4) {
					std::string compareSwitch2 = argv[4];
					if(compareSwitch2.compare("-dsymm") == 0) {
						if(i == ndos-2) {
							outfile << " '" << argv[1] << "' using 1:($" << i+2 << " + $" << i+3 << ") with lines title '" << partialNames[i] << "' ls " << i+1;
							i++;
						}  else {
							outfile << " '" << argv[1] << "' using 1:" << i+2 << " with lines title '" << partialNames[i] << "' ls " << i+1;
							if(i < ndos-1) {
								outfile << ",";
							}  else {
								outfile << std::endl;
							}
						}
					}
				}  else {
					outfile << " '" << argv[1] << "' using 1:" << i+2 << " with lines title '" << partialNames[i] << "' ls " << i+1;
					if(i < ndos-1) {
						outfile << ",";
					}  else {
						outfile << std::endl;
					}
				}
			}
		}
	}  else {
		for(int i = 0; i < ndos; i++) {
			outfile << " '" << argv[1] << "' using 1:" << i+2 << " with lines title '" << partialNames[i] << "' ls " << i+1;
			if(i < ndos-1) {
				outfile << ",";
			}  else {
				outfile << std::endl;
			}
		}
	}


	

	outfile.close();

	std::string cmd = "gnuplot " + pltfilename;
	system(cmd.c_str());

	cmd = "sed '3i\\\\\\renewcommand{\\\\familydefault}{\\\\sfdefault}' " + texfile + ".tex > " + texfile +".tex-tmp";
	std::cout << cmd << std::endl;
	system(cmd.c_str());
	cmd = "rm " + texfile + ".tex";
	system(cmd.c_str());
	cmd = "cp " + texfile + ".tex-tmp " + texfile + ".tex";
	system(cmd.c_str());

	cmd = "pdflatex " + texfile + ".tex";
	system(cmd.c_str());

	cmd = "rm " + texfile + ".aux";
	system(cmd.c_str());
	cmd = "rm " + texfile + ".log";
	system(cmd.c_str());
	cmd = "rm " + texfile + "-inc.eps";
	system(cmd.c_str());
	cmd = "rm " + texfile + "-inc-eps-converted-to.pdf";
	system(cmd.c_str());
	
	cmd = "evince " + texfile + ".pdf";
	system(cmd.c_str());
	return 0;
}

