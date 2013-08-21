/*
 * plot_bands.cc
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
	std::vector<std::string> xticsName;
    std::vector<double> xticsPos;
    std::string xlabel = "k-path";
    std::string ylabel = "energy / eV";
    double EF;
    std::string title;
	
	
	int i = 0;
	if (infile.is_open()) {
		while (infile.good()) {
            getline (infile,line);
			if(line.substr(0,19).compare("@ xaxis  tick major") == 0) {
                //std::cout << line << std::endl;
				std::stringstream s(line.substr(19,4));
                
                s >> i;
                //std::cout << i << std::endl;
                xticsName.resize(i+1);
                xticsPos.resize(i+1);
                std::stringstream s1(line.substr(24,8));
                double tmp;
                s1 >> tmp;
                
                xticsPos[i] = tmp;
                //std::cout << xticsPos[i] << std::endl;
			}
            if(line.substr(0,21).compare(" @ xaxis  ticklabel  ") == 0) {
                //std::cout << line << std::endl;
                //std::cout << line.substr(34,line.length()-34) << std::endl;
                //std::cout << i << std::endl;
				xticsName[i] = line.substr(34,line.length()-34);
                //std::cout << xticsName[i] << std::endl;
			}
            
            if(line.substr(0,9).compare(" @ title ") == 0) {
				title = line.substr(9,line.length()-9);
                //std::cout << title << std::endl;
			}
            if(line.substr(0,8).compare("@ string") == 0) {
                std::stringstream s(line.substr(8,9));
				s >> EF;
                //std::cout << EF << std::endl;
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
    outfile << "set terminal epslatex color newstyle size 9cm, 10.5cm standalone" << std::endl;
    std::string texfile = argv[1];
    //std::cout << texfile.replace(texfile.find("."),1,"_") << std::endl;
    texfile = texfile.replace(texfile.find("."),1,"_");
    outfile << "set output \"" << texfile.replace(texfile.find("."),1,"_") <<".tex\"" << std::endl << std::endl;
    
    outfile << "set xtics (";
    for (unsigned int i = 0; i < xticsName.size(); i++) {
        
        if (xticsName[i].find("xG") < xticsName[i].length()) {
            xticsName[i].replace(xticsName[i].find("\\xG"),3,"$\\\\Gamma$");
        }
        outfile << xticsName[i] << " " << xticsPos[i];
        if (i < xticsName.size()-1) {
            outfile << ",";
        } 
    }
    
    outfile << ")" << std::endl;
    outfile << "set mytics " << xticsName.size() << std::endl;
    outfile << "set xlabel \"" << xlabel << "\"" << std::endl;
    outfile << "set ylabel \"" << ylabel << "\"" << std::endl;
    outfile << "set grid xtics" << std::endl;
    outfile << "set label \"$\\\\mathsf{E_F}$\" at " << EF+0.15 << ",0 right" << std::endl;
    outfile << "set style line 1 lt 1 lw 3" << std::endl;
    outfile << "set title " << title << std::endl << std::endl;
    
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

    outfile << "set yrange [-6:5]" << std::endl;
    outfile << "set size ratio sqrt(2)" << std::endl;
    outfile << "plot 0 notitle ls 1 lc rgb \"black\", '" << argv[1] << "' using 1:2 with lines ls 7 notitle" << std::endl;


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

