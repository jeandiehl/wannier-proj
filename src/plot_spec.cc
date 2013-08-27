/*
 * plot_spec.cc
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
    std::string title;
	int Nsf = 0;
	
	//int i = 0;
	if (infile.is_open()) {
		while (infile.good()) {
            getline (infile,line);
			if(line.substr(0,8).compare("# kpath ") == 0) {
				xticsName.push_back(line.substr(8,10));
				//std::cout << line.substr(8,10) << std::endl;
			}
			if(line.substr(0,12).compare("# kpathIndex") == 0) {
				std::stringstream s(line.substr(12,line.length()-12));
				int temp;
				s >> temp;
				xticsPos.push_back(temp);
				//std::cout << temp << std::endl;
				
			}
			if(line.substr(0,9).compare("# Num SF ") == 0) {
				std::stringstream s(line.substr(9,line.length()-9));
				
				s >> Nsf;
				
				//std::cout << Nsf << std::endl;
				
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
    //texfile = texfile.replace(texfile.find("."),1,"_");
    outfile << "set output \"" << texfile.replace(texfile.find("."),1,"_") <<".tex\"" << std::endl << std::endl;
    
    
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

	outfile << "set xlabel \"k-path\"" << std::endl;
	outfile << "set ylabel \"energy / eV\"" << std::endl;
	outfile << "set title \"LaFeAsO\"" << std::endl;
	outfile << "set xtics (";
    for (unsigned int i = 0; i < xticsName.size(); i++) {
        
        if (xticsName[i].find("GAMMA") < xticsName[i].length()) {
            xticsName[i].replace(xticsName[i].find("GAMMA"),5,"$\\\\Gamma$");
        }
        outfile << "\"" << xticsName[i] << "\" " << xticsPos[i];
        if (i < xticsName.size()-1) {
            outfile << ",";
        } 
    }
    outfile << ")" << std::endl;
	//outfile << "set xtics ("$\\Gamma$" 0,"X            " 89,"M            " 177,"$\\Gamma$" 300)
	outfile << "set mytics 4" << std::endl;
	outfile << "set grid xtics" << std::endl << std::endl;

	outfile << "set palette rgb 23,28,3" << std::endl;
	outfile << "set palette negative" << std::endl;
	//outfile << "set palette model HSV" << std::endl;
	//outfile << "set palette rgb 3,2,2" << std::endl;
	
	//outfile << "set palette defined ( 0 \"#ffffff\", 1 \"#ee4035\", 2 \"#3cb74f\", 3 \"#b04c6e\", 4 \"#aece3c\", 5 \"#6a51a2\" )" << std::endl;
	outfile << "set view map" << std::endl;
	//outfile << "unset colorbox" << std::endl << std::endl;

	outfile << "set multiplot" << std::endl << std::endl;

	outfile << "set yrange[-5:7]" << std::endl;
	outfile << "set origin 0.0,0.0" << std::endl;
	outfile << "set size 1.0,1.0" << std::endl << std::endl;

	outfile << "splot '" << argv[1] << "' using 1:2:( ";
	for(int i = 0; i < Nsf; i++) {
		if(i < Nsf-1) {
			outfile << "$" << i+3 << " + ";
		}  else {
			outfile << "$" << i+3;
		}
		
	}
	outfile << " ) with image notitle" << std::endl << std::endl;

	outfile << "set yrange[-5:7]" << std::endl;
	outfile << "set origin 0.11,0.153" << std::endl;
	outfile << "set size 0.79,0.695" << std::endl;
	outfile << "unset border" << std::endl;
	outfile << "unset xtics" << std::endl;
	outfile << "unset ytics" << std::endl;
	outfile << "unset xlabel" << std::endl;
	outfile << "unset ylabel" << std::endl;
	outfile << "unset title" << std::endl << std::endl;

	std::string bandsfile = argv[1];
	if (bandsfile.find("specproj") < bandsfile.length()) {
            bandsfile = bandsfile.replace(bandsfile.find("specproj"),8,"bands.agr");
        }
	outfile << "plot '"<< bandsfile <<"' using 1:2 with lines notitle lc rgb \"black\"" << std::endl;
	outfile << "plot 0 notitle lc rgb \"black\"" << std::endl << std::endl;

	outfile << "plot -3 notitle ls 1" << std::endl;
	outfile << "plot 5 notitle ls 1" << std::endl;
	
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

