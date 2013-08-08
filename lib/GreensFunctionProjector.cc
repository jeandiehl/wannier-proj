/*
 * GreensFunctionProjector.cc
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#include "GreensFunctionProjector.h"

GreensFunctionProjector::GreensFunctionProjector() {}
GreensFunctionProjector::~GreensFunctionProjector() {}


void GreensFunctionProjector::calculate(GreensFunction& gf, GreensFunction& gfproj, Projector& proj) {
	unsigned int Nkpoints = proj.getMaxKpoints();
	Eigen::MatrixXcd PGP;
	Eigen::MatrixXcd P;
	Eigen::MatrixXcd G;
	Eigen::MatrixXcd PP;

	gfproj.initialize(gf.getEmin(), gf.getEmax(), gf.getDe(), gf.getEta(), gf.getEnergy(), proj.getCombinedIndex());
 
	std::vector<std::vector<int> > energyIndex = proj.getEnergyIndex();
	unsigned int Nomega = gf.getMaxNomega();
	unsigned int NcombIndex = proj.getMaxCombinedIndex();
	for(unsigned int i = 0; i < Nkpoints; i++) {
		P = proj.get(i);
		PP.resize(NcombIndex, Nomega);
		PP.setZero();
		for(unsigned int j = 0; j < Nomega; j++) {
			G = gf.get(i, j).block(energyIndex[i][0], energyIndex[i][0], energyIndex[i].size(), energyIndex[i].size());
			//std::cout << G << std::endl;
			//std::cout << G.rows() << " " << G.cols() << std::endl;
			PGP = P.adjoint()*G*P;
			//std::cout << std::fixed << std::setprecision(3) << PGP << std::endl;
			//std::cout << PGP.diagonal() << std::endl;
			PP.col(j) = PGP.diagonal();
		}
		//std::cout << PP << std::endl;
		gfproj.set(i, PP);
		//std::cout << gfproj.get(i) << std::endl;
	}
}
