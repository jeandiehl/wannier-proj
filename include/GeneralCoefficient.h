/*
 * GeneralCoefficient.h
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#ifndef GENERALCOEFFICIENT_H
#define GENERALCOEFFICIENT_H

#include <vector>

/// class GeneralCoefficient - 
template <class T>
class GeneralCoefficient {
  // Attributes
private:
  int Nkpoints;
  int Njatom;
  // kpoint, jatom, atom, energy, l, m
  std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<T > > > > > > CoeffValue;
  // Operations
public:
  GeneralCoefficient ();
  ~GeneralCoefficient ();

  void setCoefficient(int k, int j, int a, int e, int l, int m, T value);
  T getCoefficient(int k, int j, int a, int e, int l, int m);
};
template <class T> 
GeneralCoefficient<T>::GeneralCoefficient() : Nkpoints(0), Njatom(0) {}

template <class T> 
GeneralCoefficient<T>::~GeneralCoefficient() {}

template <class T> 
void GeneralCoefficient<T>::setCoefficient(int k, int j, int a, int e, int l, int m, T value) {
	// check if multidimensional vector has to be resized
	int Natom = CoeffValue[k][j].size();
	int Nenergy = CoeffValue[k][j][a].size();
	int Nl = CoeffValue[k][j][a][e].size();
	int Nm = CoeffValue[k][j][a][e][l].size();

	if(k >= Nkpoints) {
		Nkpoints = k+1;
		CoeffValue.resize(k+1);
	}
	if(j >= Njatom) {
		Njatom = j+1;
		CoeffValue[k].resize(j+1);
	}
	if(a >= Natom) {
		CoeffValue[k][j].resize(a+1);
	}
	if(e >= Nenergy) {
		CoeffValue[k][j][a].resize(e+1);
	}
	if(l >= Nl) {
		CoeffValue[k][j][a][e].resize(l+1);
	}
	if(m >= Nm) {
		CoeffValue[k][j][a][e][l].resize(m+1);
	}

	CoeffValue[k][j][a][e][l][m] = value;
}

template<class T> 
T GeneralCoefficient<T>::getCoefficient(int k, int j, int a, int e, int l, int m) {
	int Natom = CoeffValue[k][j].size();
	int Nenergy = CoeffValue[k][j][a].size();
	int Nl = CoeffValue[k][j][a][e].size();
	int Nm = CoeffValue[k][j][a][e][l].size();
	
	if(k < Nkpoints) {
		if(j < Njatom) {
			if(a < Natom) {
				if(e < Nenergy) {
					if(l < Nl) {
						if(m < Nm) {
							return CoeffValue[k][j][a][e][l][m];
						}
					}
				}
			}
		}
	}
}


#endif


