/*
 * DOSCalculator.h
 *
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 *
 */


#ifndef DOSCALCULATOR_H
#define DOSCALCULATOR_H

#include <iostream>
#include <vector>
#include <complex>

#include "DOS.h"
#include "GreensFunction.h"

class DOSCalculator {

private:

protected:

public:
  DOSCalculator();
  ~DOSCalculator();

  void calculate(GreensFunction& gflocal, DOS& dos);
};

#endif
