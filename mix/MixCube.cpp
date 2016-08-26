
#include "MixCube.h"
#include "CubeManger.h"

#include <algorithm>
#include <iostream>

#ifndef  NULL
#define NULL 0
#endif // ! NULL


MixCube::MixCube() :_cube(0) {
}

MixCube& MixCube::operator << (CubeManger & _cm) {
	if (_cube == NULL) {
		_cube = new CubeManger(_cm);
		_cube->copy(_cm);
		return *this;
	}
	size_t maxv = std::max((*_cube).bytes(), _cm.bytes());
	size_t minv = std::min((*_cube).bytes(), _cm.bytes());
	CubeManger temp(maxv, _cm._sample);
	size_t i = 0;
	if (minv == (*_cube).bytes()) {
		for (; i < (*_cube).count(); i++) {
			Cube * cu = _cm[i];
			Cube * cp = (*_cube)[i];
			Cube * ct = temp[i];
			//memcpy(ct->data, cp->data, cp->count);
			ct->count = cp->count;
			for (size_t step = 0; step < cp->count; step++) {
				char chu = *(cu->data + step);
				char chp = *(cp->data + step);
				*(ct->data + step) = (chu + chp) / 2;
			}
		}
		for (; i < _cm.count(); i++) {
			Cube * cu = _cm[i];
			Cube * ct = temp[i];
			memcpy(ct->data, cu->data, cu->count);
			ct->count = cu->count;
		}
	}else if (minv == _cm.bytes()) {
		for (; i < _cm.count(); i++) {
			Cube * cu = _cm[i];
			Cube * cp = (*_cube)[i];
			Cube * ct = temp[i];
			//memcpy(ct->data, cp->data, cp->count);
			ct->count = cp->count;
			for (size_t step = 0; step < cu->count; step++) {
				char chu = *(cu->data + step);
				char chp = *(cp->data + step);
				*(ct->data + step) = (chu + chp) / 2;
			}
		}
		for (; i < (*_cube).count(); i++) {
			Cube * cp = (*_cube)[i];
			Cube * ct = temp[i];
			memcpy(ct->data, cp->data, cp->count);
			ct->count = cp->count;
		}
	}
	_cube = new CubeManger(temp);
	return *this;
}
MixCube::~MixCube() {
	if (_cube != 0) {
		delete _cube;
	}
	_cube = NULL;
}
std::ostream& operator << (std::ostream & out, MixCube& cube) {
	out << *(cube._cube);
	return out;
}

std::istream& operator >> (std::istream & ino, MixCube& cube) {
	ino >> *(cube._cube);
	return ino;
}

