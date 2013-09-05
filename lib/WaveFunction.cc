/*
 * WaveFunction.cc
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#include "WaveFunction.h"

WaveFunction::WaveFunction() {}
WaveFunction::~WaveFunction() {}

void WaveFunction::initialize(Eigen::Vector3d NNspace, std::vector<std::vector<int> > combinedIndex) {
    initialize(NNspace);
    combIndex = combinedIndex;
}

void WaveFunction::initialize(WaveFunction& wf) {
    initialize(wf.getNspace());
}

void WaveFunction::initialize(Eigen::Vector3d NNspace) {
    Nspace = NNspace;
    NspaceTotal = 1;
    for (int i = 0; i < 3; i++) {
        NspaceTotal *= Nspace(i);
    }
    WF.resize(1);
}

void WaveFunction::set(int ikpoints, Eigen::MatrixXcd w) {
    if (WF.size() <= ikpoints) {
        WF.resize(ikpoints+1);
    }
    WF[ikpoints] = w;
}

Eigen::MatrixXcd WaveFunction::get(int ikpoints) { return WF[ikpoints]; }

int WaveFunction::getNspaceTotal() { return NspaceTotal; }

Eigen::Vector3d WaveFunction::getNspace() { return Nspace; }

int WaveFunction::getMaxNkpoints() { return WF.size(); }

Eigen::MatrixXcd WaveFunction::get(int ikpoints, int inspace) {
	return WF[ikpoints].col(inspace).asDiagonal();
}

std::vector<std::vector<int> > WaveFunction::getCombinedIndex() {
	return combIndex;
}

std::ostream& operator<<(std::ostream& Stream, WaveFunction& W) {

	int Natoms = 0;
	for(unsigned int i = 0; i < W.atomPositions.size(); i++) {
		for(unsigned int j = 0; j < W.atomPositions[i].size(); j++) {
			Natoms++;
		}
	}

	
	int NcombinedIndex = W.combIndex.size();
	Stream << "CRYSTAL" << std::endl;
	Stream << "PRIMVEC" << std::endl;
	Stream << std::fixed << std::setprecision(10) << W.unitCell << std::endl;
	Stream << "CONVVEC" << std::endl;
	Stream << std::fixed << std::setprecision(10) << W.unitCell << std::endl;
	Stream << "PRIMCOORD" << std::endl;
	Stream << std::fixed << std::setprecision(0) << std::setw(12) << Natoms << std::setw(12) << "1" << std::endl;
	for(unsigned int i = 0; i < W.atomPositions.size(); i++) {
		for(unsigned int j = 0; j < W.atomPositions[i].size(); j++) {
			Stream << W.atomNames[i] << "    " << std::setprecision(10) << (W.unitCell*W.atomPositions[i][j]).transpose() << std::endl;
		}
	}
	for(int i = 0; i < NcombinedIndex; i++) {
		Stream << "BEGIN_BLOCK_DATAGRID_3D" << std::endl;
		Stream << "3D_field_" << i << std::endl;
		Stream << "BEGIN_DATAGRID_3D_UNKNOWN" << std::endl;
		for(int j = 0; j < W.Nspace.size(); j++) {
			Stream << std::setw(5) << std::fixed << std::setprecision(0) << W.Nspace(j);
		}
		Stream << std::endl;
		Stream << std::fixed << std::setprecision(10) << W.selectedCell[0].transpose() << std::endl;
		Eigen::MatrixXd temp;
		temp.resize(3,3);
		temp.setZero();
		temp.col(0) = W.selectedCell[1];
		temp.col(1) = W.selectedCell[2];
		temp.col(2) = W.selectedCell[3];
		
		Stream << std::fixed << std::setprecision(10) << W.unitCell*temp << std::endl;
		
		int lineindex = 0;

		for(int iz = 0; iz < W.Nspace(2); iz++) {
			for(int iy = 0; iy < W.Nspace(1); iy++) {
				for(int ix = 0; ix < W.Nspace(0); ix++) {
					Stream << std::setw(10) << std::scientific  << std::setprecision(6) << abs(W.WF[0](i,ix*W.Nspace(2)*W.Nspace(1) + iy*W.Nspace(2) + iz)) << " ";
					if(lineindex < 5) {
						lineindex++;
					}  else {
						lineindex = 0;
						Stream << std::endl;
					}
				}
			}
		}

		Stream << std::endl;
		Stream << "END_DATAGRID_3D" << std::endl;
		Stream << "END_BLOCK_DATAGRID_3D" << std::endl << std::endl;
	}

    return Stream;
}

void WaveFunction::setStructure(Eigen::MatrixXd uunitCell, std::vector<std::string> aatomNames, std::vector<std::vector<Eigen::Vector3d> > aatomPositions, std::vector<Eigen::Vector3d > sselectedCell) {
	unitCell = uunitCell;
	atomPositions = aatomPositions;
	atomNames = aatomNames;
	selectedCell = sselectedCell;
}
