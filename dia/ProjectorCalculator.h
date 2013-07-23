#include "Projector.h"

/// class ProjectorCalculator - 
class ProjectorCalculator {
  // Operations
public:
  ProjectorCalculator (GeneralCoefficient<complex<double>>& const Alm, GeneralCoefficient<Vector3cd>& const Clm, GeneralCoefficient<Vector3cd>& const O);
  ~ProjectorCalculator ();
  void calculate (Projector Proj, Projector ProjTilde);
};

