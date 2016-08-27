#pragma once


#include "CubeManger.h"

#include <iostream>

/**
* _MIX_LINE_ARG使用线性叠加后求均值混音算法
* 优点 ： 是不会产生溢出并且噪音较小
* 缺点 ： 是衰减过点，影响音频质量
*/
#ifdef _MIX_LINE_ARG
#undef _MIX_LINE_ARG
#endif // _MIX_LINE_ARG

/**启用newlc中使用关键混音算法*/
#ifndef _MIX_NEWLC_KVG
#define _MIX_NEWLC_KVG
#endif //!_MIX_NEWLC_KVG

class MixCube {
private:
	CubeManger *_cube;

public:
	MixCube();
	~MixCube();

private:
	/**
	* 与内置cube进行mix
	*/
	bool MixSelf(CubeManger & _cm);


public:
	static size_t MutilMix(CubeManger &left, CubeManger &right);
	static size_t Mix(CubeManger&left,CubeManger & right);
	static inline size_t MixWithCube(Cube&ct, Cube&cp);
	/**
	* 混合入口
	*/
	MixCube& operator << (CubeManger & _cm);
	/**
	* 混合音频输出
	*/
	MixCube& operator >> (CubeManger & _cm);

	friend std::ostream& operator << (std::ostream & out, MixCube& cube);
	friend std::istream& operator >> (std::istream & ino, MixCube& cube);
};

