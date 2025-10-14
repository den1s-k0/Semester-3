#pragma once

#include <iostream>
#include <windows.h>

namespace ReturnMinMaxCodes {

	const int SUCCESS = 0;

	const int ERROR_NULL_PONTER = 1;

	const int ERROR_INVALID_LENGTH = 2;

}

using namespace std;

int findMin(int* mas, int size, int& result);

int findMax(int* mas, int size, int &result);