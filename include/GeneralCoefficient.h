/*
 * GeneralCoefficient.h
 * 
 * Copyright 2013 Jean Diehl <jdiehl@itp.uni-frankfurt.de>
 * 
 */

#ifndef GENERALCOEFFICIENT_H
#define GENERALCOEFFICIENT_H

#include <vector>
#include <Eigen/Core>

/// class GeneralCoefficient - 
template <class T>
class GeneralCoefficient {
  // Attributes
private:
  int Nkpoints;
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
GeneralCoefficient<T>::GeneralCoefficient() : Nkpoints(1) {
	CoeffValue.resize(1);
	CoeffValue[0].resize(1);
	CoeffValue[0][0].resize(1);
	CoeffValue[0][0][0].resize(1);
	CoeffValue[0][0][0][0].resize(1);
	CoeffValue[0][0][0][0][0].resize(1);
}

template <class T> 
GeneralCoefficient<T>::~GeneralCoefficient() {}

template <class T> 
void GeneralCoefficient<T>::setCoefficient(int k, int j, int a, int e, int l, int m, T value) {
	// check if multidimensional vector has to be resized

	if(k >= Nkpoints) {
		Nkpoints = k+1;
		CoeffValue.resize(k+1);
		CoeffValue[k].resize(1);
	}
	int Njatom = CoeffValue[k].size();
	if(j >= Njatom) {
		Njatom = j+1;
		CoeffValue[k].resize(j+1);
		CoeffValue[k][j].resize(1);
		
	}
	int Natom = CoeffValue[k][j].size();
	if(a >= Natom) {
		CoeffValue[k][j].resize(a+1);
		CoeffValue[k][j][a].resize(1);
	}
	int Nenergy = CoeffValue[k][j][a].size();
	if(e >= Nenergy) {
		CoeffValue[k][j][a].resize(e+1);
		CoeffValue[k][j][a][e].resize(1);
	}
			
	int Nl = CoeffValue[k][j][a][e].size();
	if(l >= Nl) {
		CoeffValue[k][j][a][e].resize(l+1);
		CoeffValue[k][j][a][e][l].resize(1);
	}
	int Nm = CoeffValue[k][j][a][e][l].size();
	if(m+l >= Nm) {
		CoeffValue[k][j][a][e][l].resize(m+l+1);
	}
	CoeffValue[k][j][a][e][l][m] = value;
}

template<class T> 
T GeneralCoefficient<T>::getCoefficient(int k, int j, int a, int e, int l, int m) {
	
	if(k < Nkpoints) {
		int Njatom = CoeffValue[k].size();
		if(j < Njatom) {
			int Natom = CoeffValue[k][j].size();
			if(a < Natom) {
				int Nenergy = CoeffValue[k][j][a].size();
				if(e < Nenergy) {
					int Nl = CoeffValue[k][j][a][e].size();
					if(l < Nl) {
						int Nm = CoeffValue[k][j][a][e][l].size();
						if(m < Nm) {
							return CoeffValue[k][j][a][e][l][m];
						} else {
							return T();
						}
					} else {
						return T();
					}
				} else {
					return T();
				}
			} else {
				return T();
			}
		} else {
			return T();
		}
	} else {
		return T();
	}
}

// VectorXcd specialization

template <>
class GeneralCoefficient<Eigen::VectorXcd> {
  // Attributes
private:
  int Nkpoints;
  // kpoint, jatom, atom, energy, l, m
  std::vector<std::vector<std::vector<std::vector<std::vector<std::vector<Eigen::VectorXcd > > > > > > CoeffValue;
  // Operations
public:
  GeneralCoefficient();
  ~GeneralCoefficient();

  void setCoefficient(int k, int j, int a, int e, int l, int m, Eigen::VectorXcd value);
  Eigen::VectorXcd getCoefficient(int k, int j, int a, int e, int l, int m);
};

inline
GeneralCoefficient<Eigen::VectorXcd>::GeneralCoefficient() : Nkpoints(1) {

	CoeffValue.resize(1);
	CoeffValue[0].resize(1);
	CoeffValue[0][0].resize(1);
	CoeffValue[0][0][0].resize(1);
	CoeffValue[0][0][0][0].resize(1);
	CoeffValue[0][0][0][0][0].resize(1);
	
}

inline
GeneralCoefficient<Eigen::VectorXcd>::~GeneralCoefficient() {}

inline
void GeneralCoefficient<Eigen::VectorXcd>::setCoefficient(int k, int j, int a, int e, int l, int m, Eigen::VectorXcd value) {
	// check if multidimensional vector has to be resized

	if(k >= Nkpoints) {
		Nkpoints = k+1;
		CoeffValue.resize(k+1);
		CoeffValue[k].resize(1);
	}
	int Njatom = CoeffValue[k].size();
	if(j >= Njatom) {
		Njatom = j+1;
		CoeffValue[k].resize(j+1);
		CoeffValue[k][j].resize(1);
		
	}
	int Natom = CoeffValue[k][j].size();
	if(a >= Natom) {
		CoeffValue[k][j].resize(a+1);
		CoeffValue[k][j][a].resize(1);
	}
	int Nenergy = CoeffValue[k][j][a].size();
	if(e >= Nenergy) {
		CoeffValue[k][j][a].resize(e+1);
		CoeffValue[k][j][a][e].resize(1);
	}
			
	int Nl = CoeffValue[k][j][a][e].size();
	if(l >= Nl) {
		CoeffValue[k][j][a][e].resize(l+1);
		CoeffValue[k][j][a][e][l].resize(1);
	}
	int Nm = CoeffValue[k][j][a][e][l].size();
	if(m+l >= Nm) {
		CoeffValue[k][j][a][e][l].resize(m+l+1);
	}
	CoeffValue[k][j][a][e][l][m] = value;
}

inline
Eigen::VectorXcd GeneralCoefficient<Eigen::VectorXcd>::getCoefficient(int k, int j, int a, int e, int l, int m) {
	Eigen::VectorXcd empty;
	empty.resize(3);
	empty.setZero();
	if(k < Nkpoints) {
		int Njatom = CoeffValue[k].size();
		if(j < Njatom) {
			int Natom = CoeffValue[k][j].size();
			if(a < Natom) {
				int Nenergy = CoeffValue[k][j][a].size();
				if(e < Nenergy) {
					int Nl = CoeffValue[k][j][a][e].size();
					if(l < Nl) {
						int Nm = CoeffValue[k][j][a][e][l].size();
						if(m < Nm) {
							return CoeffValue[k][j][a][e][l][m];
						} else {
							return empty;
						}
					} else {
						return empty;
					}
				} else {
					return empty;
				}
			} else {
				return empty;
			}
		} else {
			return empty;
		}
	} else {
		return empty;
	}
}

#endif


