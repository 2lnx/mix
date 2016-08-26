#pragma once

#include "Cube.h"
#include <iostream>

class MixCube;
class CubeManger {
public:
	CubeManger(CubeManger& _cm);
	CubeManger(size_t total = 0, size_t sample = 44100);

	void operator = (CubeManger & _cm);
	inline Cube* operator[](int i) {
		return (*this)[(size_t)i];
	}
	Cube* operator[](size_t i);

	size_t bytes() const;
	size_t count() const;

	//bool extent(size_t total=0);

	~CubeManger();

private:
	void copy(CubeManger& _cm);

public:
	friend std::ostream& operator << (std::ostream & out, CubeManger& cube);
	friend std::istream& operator >> (std::istream & ino, CubeManger& cube);

private:
	friend class MixCube;

private:
	Cube * _cube;
	size_t _count;
	size_t _bytes;
	size_t _sample;
};
