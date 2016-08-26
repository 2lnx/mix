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

