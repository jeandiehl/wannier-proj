/*
 * OverlapCalculator.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#include "OverlapCalculator.h"

OverlapCalculator::OverlapCalculator() {
	
}
OverlapCalculator::~OverlapCalculator() {}

void OverlapCalculator::calculate(Projector& P, Overlap& O) {
	unsigned int Nkpoints = P.getMaxKpoints();
	O.initialize(Nkpoints);
	for(unsigned int ikpoints = 0; ikpoints < Nkpoints; ikpoints++) {
		O.set(ikpoints, P.get(ikpoints).adjoint()*P.get(ikpoints) ) ;
	}
}
