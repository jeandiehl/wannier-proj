/*
 * DOSCalculator.cc
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#include "DOSCalculator.h"

DOSCalculator::DOSCalculator() {}
DOSCalculator::~DOSCalculator() {}

void DOSCalculator::calculate(GreensFunction& gflocal, DOS& dos) {
    dos.initialize(gflocal.getMaxNomega(), gflocal.getCombinedIndex().size(), gflocal.getEmin(), gflocal.getEmax(), gflocal.getDe(), gflocal.getCombinedIndex());
    //std::cout << -1.0/M_PI*gflocal.get(0).transpose().imag() << std::endl;
    
    dos.set(-1.0/M_PI*gflocal.get(0).transpose().imag());
}
