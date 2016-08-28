
#include "MixCube.h"
#include "CubeManger.h"

#include <algorithm>
#include <iostream>

#ifndef  NULL
#define NULL 0
#endif // ! NULL

#ifndef BOX_COUNT
#define BOX_COUNT 2
#endif // BOX_COUNT


/**
* 多线程传递载体类
**/
class CubeBox {
private:
	int _count;
	Cube* _cube[2];

public:
	CubeBox():_count(0){
		_cube[0] = 0;
		_cube[1] = 0;
	}

	CubeBox(int _c,Cube *_left,Cube*_right):_count(_c){
		if ( (_count == 0)||(_left == 0)|| (_right == 0) ){
			_cube[0] = 0;
			_cube[1] = 0;
			return;
		}
		_cube[0] = _left;
		_cube[1] = _right;
	}

	inline Cube* operator[](int i) {
		if (i < 0) {
			return NULL;
		}
		if (i >= 2) {
			return NULL;
		}
		if (_cube == 0) {
			return NULL;
		}
		return _cube[i];
	}

	int count() const {
		return _count;
	}
};

#include <Windows.h>

DWORD WINAPI MixXThread(LPVOID arg) {
	CubeBox * box = (CubeBox*)arg;
	if (box == NULL) {
		return 0;
	}
	for (int i = 0; i < box->count(); i++) {
		Cube* left  = (*box)[0];
		Cube* right = (*box)[1];
		MixCube::MixWithCube(*(left + i), *(right + i));
	}
	delete box;
	return 0;
}

MixCube::MixCube() :_cube(0) {

}

bool MixCube::MixSelf(CubeManger & _cm) {
	if (_cube == NULL) {
		return false;
	}
	if (_cube->bytes() < _cm.bytes()) {
		return false;
	}
#ifdef _USING_MUTIL_MIX_
	return (MixCube::MutilMix(*(this->_cube), _cm) == this->_cube->bytes() );
#else
	return (MixCube::Mix(*(this->_cube), _cm) == this->_cube->bytes());
#endif
}

/**
* 启用多线程处理混合cube
**/
size_t MixCube::MutilMix(CubeManger &left, CubeManger &right) {
	if (right.bytes() <= 0) {
		return 0;
	}
	if ( left.bytes() < right.bytes() ) {
		return -1;
	}

	// 数据最大分片数
	const int clips = _MAX_MUTIL_COUNT_;

	int cup = int(right.count() / clips);
	int mod = right.count() % clips;

	DWORD idThread[clips];
	HANDLE handle[clips];

	for (int i = 0; i < clips; i++) {
		int xco = cup + ( (i == (clips)) ? mod : 0);
		CubeBox * box = new CubeBox(xco,left[i * cup],right[i * cup]);
		handle[i] = ::CreateThread(NULL, 0, MixXThread, box, 0, &idThread[i]);
	}
	//DWORD hIndex = 0;
	//while (true) {
	//	hIndex = WaitForMultipleObjects(clips, handle, false, INFINITE) - WAIT_OBJECT_0;
	//	if (hIndex >= clips) {
	//		break;
	//	}
	//	CloseHandle(handle[hIndex]);
	//}
	WaitForMultipleObjects(clips, handle, true, INFINITE);
	for (int i = 0; i < clips; i++) {
		CloseHandle(handle[i]);
	}

	return right.bytes();
}


/**
* 使用顺序处理混合cube
**/
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
		MixCube::MixWithCube(*ct, *cp);
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
		}else {
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
	size_t maxv = max((*_cube).bytes(), _cm.bytes());
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

