#pragma once

#include <iostream>
#include <windows.h>

using namespace std;

namespace ReturnAverageCodes {

	const int SUCCESS = 0;

	const int ERROR_NULL_PONTER = 1;

	const int ERROR_INVALID_LENGTH = 2;

}

int calculateAverage(int* mas, int size, int& result);