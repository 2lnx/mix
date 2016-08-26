#pragma once


#include "CubeManger.h"

#include <iostream>

class MixCube {
private:
	CubeManger *_cube;

public:
	MixCube();

	MixCube& operator << (CubeManger & _cm);
	~MixCube();
	friend std::ostream&  operator << (std::ostream & out, MixCube& cube);
	friend std::istream& operator >> (std::istream & ino, MixCube& cube);
};

