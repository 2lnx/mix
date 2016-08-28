#pragma once


#include "CubeManger.h"

#include <iostream>

/**
* _MIX_LINE_ARGʹ�����Ե��Ӻ����ֵ�����㷨
* �ŵ� �� �ǲ�������������������С
* ȱ�� �� ��˥�����㣬Ӱ����Ƶ����
*/
#ifdef _MIX_LINE_ARG
#undef _MIX_LINE_ARG
#endif // _MIX_LINE_ARG

/**����newlc��ʹ�ùؼ������㷨*/
#ifndef _MIX_NEWLC_KVG
#define _MIX_NEWLC_KVG
#endif //!_MIX_NEWLC_KVG

/** ���ö��̼ܹ߳��������� */
#ifndef _USING_MUTIL_MIX_
#define _USING_MUTIL_MIX_
#endif // !_USING_MUTIL_MIX_

#ifndef _MAX_MUTIL_COUNT_
#define _MAX_MUTIL_COUNT_ 24
#endif

class MixCube {
private:
	CubeManger *_cube;

public:
	MixCube();
	~MixCube();

private:
	/**
	* ������cube����mix
	*/
	bool MixSelf(CubeManger & _cm);


public:
	static size_t MutilMix(CubeManger &left, CubeManger &right);
	static size_t Mix(CubeManger&left,CubeManger & right);
	static inline size_t MixWithCube(Cube&ct, Cube&cp);
	/**
	* ������
	*/
	MixCube& operator << (CubeManger & _cm);
	/**
	* �����Ƶ���
	*/
	MixCube& operator >> (CubeManger & _cm);

	friend std::ostream& operator << (std::ostream & out, MixCube& cube);
	friend std::istream& operator >> (std::istream & ino, MixCube& cube);
};

