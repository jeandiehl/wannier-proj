#include "FileGeneral.h"

/// class FileInproj - 
class FileInproj : public FileGeneral {
  // Operations
public:
  FileInproj ();
  ~FileInproj ();
  void read (double& Emin, double& Emax, double& dE, vector<vector<vector<int > > >& selectedOrbitals);
};

