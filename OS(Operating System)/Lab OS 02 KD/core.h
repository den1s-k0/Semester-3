#pragma once

#include "min_max.h"
#include "average.h"
#include "param_structure.h"

namespace ReturnCoreCodes {

	const int SUCCESS = 0;

	const int ERROR_MIN_SEARCH = 1;

	const int ERROR_MAX_SEARCH = 2;

	const int ERROR_AVERAGE_SEARCH = 3;

}

DWORD WINAPI MinMaxThread(LPVOID parametr);

DWORD WINAPI AverageThread(LPVOID parametr);