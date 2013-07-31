#include "FileGeneral.h"

/// class FileSymm - 
class FileSymm : public FileGeneral {
  // Operations
public:
  FileSymm ();
  ~FileSymm ();
  void read (vector<MatrixXcd>& S);
};

