// mix.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <time.h>
#include <fstream>
#include <iostream>
using namespace std;

#include "MixCube.h"

#include <sys/timeb.h>
__inline long long getSystemTime() {
	struct timeb t;
	ftime(&t);
	return 1000 * t.time + t.millitm;
}

size_t filesize(ifstream & iif) {
	streampos b   = iif.tellg();
	iif.seekg(0, ios_base::end);
	streampos fno = iif.tellg();
	iif.seekg(0, ios_base::beg);
	return static_cast<size_t>(fno - b);
}

int main() {

	long long t1 = getSystemTime();
	char b[44] = { 0 };
	char bc[44] = { 0 };


	MixCube mc;
	{
		ifstream ifo;
		ifo.open("d:/1.wav", std::ios_base::binary | ios_base::in);
		size_t to = filesize(ifo) - 44;
		CubeManger cm(to);
		ifo.read(bc,44);
		ifo >> cm;
		ifo.close();

		ifstream ifo2;
		ifo2.open("d:/2.wav", std::ios_base::binary | ios_base::in);
		to = filesize(ifo2) - 44;
		CubeManger cm2(to);
		ifo2.read(b,44);
		ifo2 >> cm2;
		ifo2.close();

		ifstream ifo21;
		ifo21.open("d:/21.wav", std::ios_base::binary | ios_base::in);
		to = filesize(ifo21) - 44;
		CubeManger cm21(to);
		ifo21.read(b, 44);
		ifo21 >> cm21;
		ifo21.close();
		mc <<cm  << cm2 << cm21;

	}
	ofstream of;
	of.open("d:/cube.txt.wav", std::ios_base::binary);
	of.write(bc, 44);
	of << mc;
	of.close();
	//
	long long t2 = getSystemTime();
	cout << t2 - t1 << endl;
	return 0;
}
