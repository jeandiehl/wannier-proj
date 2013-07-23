/*
 * run_proj.cc
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */
 
#include "FileAlmblm.h"

int main(int argc, char **argv) {
	
	// get current working directory
	char cwd[256];
	getcwd(cwd, sizeof(cwd));
	string path = string(cwd);
    
    unsigned pos = path.find_last_of("/");
	string w2kProjectName = path.substr(pos + 1, path.length() - (pos + 1) );

    FileAlmblm fileABC(w2kProjectName);

	return 0;
}

