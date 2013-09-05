/*
 * WannierFunctionCalculator.cc
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#include "WannierFunctionCalculator.h"

WannierFunctionCalculator::WannierFunctionCalculator() {}
WannierFunctionCalculator::~WannierFunctionCalculator() {}

void WannierFunctionCalculator::calculate(double vol, std::vector<Eigen::Vector3d>& kpoints, std::vector<std::vector<Eigen::Vector3d> >& atomPositions, Projector& proj, WaveFunction& psi, WaveFunction& wannier) {
    
    Eigen::MatrixXcd wann;
    unsigned int Nkpoints = kpoints.size();
    wann.resize(proj.getMaxCombinedIndex(),psi.getNspaceTotal());
    wann.setZero();
    std::complex<double> im = std::complex<double> (0.0, 1.0);
    
    //std::cout << Nkpoints << std::endl;
    std::vector<std::vector<int> > combIndex = proj.getCombinedIndex();
    std::vector<std::vector<int> > energyIndex = proj.getEnergyIndex();
    
    wannier.initialize(psi.getNspace(), proj.getCombinedIndex());
    
    for (unsigned int ikpoints = 0; ikpoints < Nkpoints; ikpoints++) {
        Eigen::MatrixXcd P = proj.get(ikpoints).transpose();

        Eigen::MatrixXcd bloch = psi.get(ikpoints).block(energyIndex[ikpoints][0], 0, energyIndex[ikpoints].size(), psi.get(ikpoints).cols());
        //std::cout << bloch << std::endl;
        //std::cout << bloch.rows() << " " << bloch.cols() << std::endl;
        Eigen::MatrixXcd temp;
        temp.setZero();
        temp = P*bloch;
        //std::cout << temp.rows() << std::endl;
        //std::cout << temp << std::endl << std::endl;
        for (int i = 0; i < temp.rows(); i++) {
            std::complex<double> ikR = 2*M_PI*im*kpoints[ikpoints].transpose()*atomPositions[combIndex[i][0]][combIndex[i][1]];
            Eigen::VectorXcd tmpRow = temp.row(i);
            //std::cout << combIndex[i][0] << " " << combIndex[i][1] << std::endl;
            //std::cout << atomPositions[combIndex[i][0]][combIndex[i][1]].transpose() << std::endl;
            //std::cout << exp(ikR) << std::endl;
            temp.row(i) = vol/pow(2*M_PI,3.0)*exp(ikR)*tmpRow;
        }
        wannier.set(ikpoints, temp);
        //std::cout << temp << std::endl;
    }
    
}
