#pragma once

#include <iostream>

namespace ReturnParamCodes {

	const int SUCCESS = 0;

	const int ERROR_NULL_PONTER = 1;

	const int ERROR_INVALID_LENGTH = 2;

}

using namespace std;

struct ParamStructure
{
	int* Mas;
	int size;
	int min;
	int max;
	int average;

	ParamStructure();
	ParamStructure(int s);
	ParamStructure(int s, int mi, int ma, int av);
	~ParamStructure();

	int createMas();
	int ArrayChange();
};
