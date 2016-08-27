
#include "MixCube.h"
#include "CubeManger.h"

#include <algorithm>
#include <iostream>

#ifndef  NULL
#define NULL 0
#endif // ! NULL


MixCube::MixCube() :_cube(0) {
}

bool MixCube::MixSelf(CubeManger & _cm) {
	if (_cube == NULL) {
		return false;
	}
	if (_cube->bytes() < _cm.bytes()) {
		return false;
	}
	return ( this->Mix(*(this->_cube), _cm) == this->_cube->bytes() );
}

size_t MixCube::Mix(CubeManger&left, CubeManger & right) {
	if (right.bytes() <= 0) {
		return 0;
	}
	if ( left.bytes() < right.bytes() ) {
		return -1;
	}
	for (size_t i = 0; i < right.count(); i++) {
		Cube *ct = left[i];
		Cube *cp = right[i];
		this->MixWithCube(*ct, *cp);
	}
	return left.bytes();
}
inline size_t MixCube::MixWithCube(Cube&ct, Cube&cp) {
	for (size_t i = 0; i < cp.count; i++) {
		char chu = (short)*(ct.data + i);
		char chp = (short)*(cp.data + i);
#ifdef _MIX_LINE_ARG
		/*叠加后求均值*/
		*(ct->data + step) = (chu + chp) / 2;
#else ifdef _MIX_NEWLC_KVG
		if ((chu < 0) && (chp < 0)) {
			*(ct.data + i) = byte((chu + chp) - (chu*chp / -(pow(2, 8 - 1) - 1)));
		}
		else {
			*(ct.data + i) = byte((chu + chp) - (chu*chp / (pow(2, 8 - 1) - 1)));
		}
#endif
	}
	return cp.count;
}

MixCube& MixCube::operator << (CubeManger & _cm) {
	if (_cube == NULL) {
		_cube = new CubeManger(_cm);
		_cube->copy(_cm);
		return *this;
	}
	size_t maxv = std::max((*_cube).bytes(), _cm.bytes());
	if( maxv > _cube->bytes() ){
		CubeManger * old = _cube;
		_cube = new CubeManger(maxv, _cm._sample);
		_cube->copy(*old);
		if (old != NULL) {
			delete old;
			old = NULL;
		}
	}
	if (this->MixSelf(_cm)) {
		return *this;
	}
	return *this;
}


MixCube& MixCube::operator >> (CubeManger & _cm) {
	_cm = CubeManger(*(this->_cube));
	return *this;
}

MixCube::~MixCube() {
	if (_cube != 0) {
		delete _cube;
	}
	_cube = NULL;
}

std::ostream& operator << (std::ostream & out, MixCube& cube) {
	if (cube._cube != NULL) {
		out << *(cube._cube);
	}
	return out;
}

std::istream& operator >> (std::istream & ino, MixCube& cube) {
	if (cube._cube != NULL) {
		ino >> *(cube._cube);
	}
	return ino;
}

