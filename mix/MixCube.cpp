
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
	CubeManger * maxcude = 0;
	CubeManger * mincude = 0;
	if (minv == (*_cube).bytes()) {
		maxcude = &_cm;
		mincude = _cube;
	}else if (minv == _cm.bytes()) {
		maxcude = _cube;
		mincude = &_cm;
	}
	size_t i = 0;
	for (; i < (*mincude).count(); i++) {
		Cube * cu = _cm[i];
		Cube * cp = (*_cube)[i];
		Cube * ct = temp[i];
		ct->count = cp->count;
		for (size_t step = 0; step < cp->count; step+=1) {
			char chu = (short)*(cu->data + step);
			char chp = (short)*(cp->data + step);
#ifdef _MIX_LINE_ARG
			/*叠加后求均值*/
			*(ct->data + step) =(chu + chp)/2;
#else ifdef _MIX_NEWLC_KVG
			if( (chu < 0)&&(chp < 0) ){
				*(ct->data + step) = byte((chu + chp) -(chu*chp / -(pow(2,8 - 1) - 1)));
			}else {
				*(ct->data + step) = byte((chu + chp) - (chu*chp / (pow(2, 8 - 1) - 1)));
			}
#endif
		}
	}
	for (; i < (*maxcude).count(); i++) {
		Cube * mcu = (*maxcude)[i];
		Cube * ct  = temp[i];
		memcpy(ct->data, mcu->data, mcu->count);
		ct->count = mcu->count;
	}

	_cube = new CubeManger(temp);
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

