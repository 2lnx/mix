
#include "CubeManger.h"


#include <iostream>

CubeManger::CubeManger(size_t total, size_t sample) :_cube(0), _bytes(total), _sample(sample), _count(0) {
	if (total == 0) {
		return;
	}
	int cut = total / sample;
	int cup = total % sample;
	if (cup > 0) {
		cut += 1;
	}else {
		cup = sample;
	}
	_count = cut;
	_cube = new Cube[cut];

	size_t i = 0;
	for (; i < _count - 1; i++) {
		Cube * cu = (*this)[i];
		cu->data = new byte[sample];
		memset(cu->data, 0, sample);
		cu->count = sample;
	}

	Cube * cu = (*this)[i];
	cu->data = new byte[sample];
	memset(cu->data, 0, sample);
	cu->count = cup;
}

Cube* CubeManger::operator[](size_t i) {
	if ((i < 0) || (i >= _count)) {
		return 0;
	}
	return (_cube + i);
}

size_t CubeManger::bytes() const {
	if (_bytes < 0) {
		return 0;
	}
	return _bytes;
}

size_t CubeManger::count() const {
	if (_count < 0) {
		return 0;
	}
	return _count;
}
CubeManger::CubeManger(CubeManger& _cm) :CubeManger(_cm._bytes, _cm._sample) {
	copy(_cm);
}

CubeManger::~CubeManger() {
	if ((_cube == NULL) || (_count != 0)) {
		_count = 0;
		_cube = 0;
		return;
	}
	for (size_t i = 0; i < _count; i++) {
		Cube * cu = (*this)[i];
		if ((cu != 0) && (cu->data != 0)) {
			delete[] cu->data;
			cu->data = 0;
			cu->count = 0;
		}
	}
	delete[] _cube;
	_count = 0;
	_cube = 0;
}

void CubeManger::operator = (CubeManger & _cm) {
	this->_bytes = _cm._bytes;
	this->_count = _cm._count;
	this->_sample = _cm._sample;
	copy(_cm);
}
//bool CubeManger::extent(size_t total=0) {
//	CubeManger temp(this->bytes() + total,this->_sample);
//	copy(temp)
//}


void CubeManger::copy(CubeManger& _cm) {
	for (size_t i = 0; i < _cm.count(); i++) {
		Cube* cu = _cm[i];
		Cube* cp = (*this)[i];
		memcpy(cp->data, cu->data, cu->count);
		cp->count = cu->count;
	}
}

std::ostream& operator << (std::ostream & out, CubeManger& cube) {
	for (size_t i = 0; i < cube.count(); i++) {
		Cube * cp = cube[i];
#ifdef _DEBUG
		if (cp == NULL) {
			std::cout << "cp NULL" << std::endl;
		}
		if (cp->data == NULL) {
			std::cout << "data NULL" << std::endl;
		}
		if (cp->count == NULL) {
			std::cout << "count 0" << std::endl;
		}
#endif
		out.write((char*)(cp->data), cp->count);
	}
	return out;
}

std::istream& operator >> (std::istream & ino, CubeManger& cube) {
	for (size_t i = 0; i < cube.count(); i++) {
		Cube * cp = cube[i];
		ino.read((char*)(cp->data), cp->count);
	}
	return ino;
}
