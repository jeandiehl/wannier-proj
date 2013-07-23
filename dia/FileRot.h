#include "FileGeneral.h"

/// class FileRot - 
class FileRot : public FileGeneral {
  // Operations
public:
  FileRot ();
  ~FileRot ();
  void read (vector<MatrixXcd>& R);
};

