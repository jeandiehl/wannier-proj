#include "FileGeneral.h"

/// class FileAlmblm - 
class FileAlmblm : public FileGeneral {
  // Operations
public:
  FileAlmblm ();
  ~FileAlmblm ();
  void read (GeneralCoefficient<complex<double> >& Alm, GeneralCoefficient<Vector3cd>& Clm, GeneralCoefficient<Vector3cd>& O);
};

