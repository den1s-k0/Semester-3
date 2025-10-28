#pragma once

#include <iostream>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include "main.h"


using namespace std;

namespace ReturnCoreCodes {
	const int SUCCES = 0;
}

int cinIntLessEqualN(int max, string str);

void createArrayOfZeros(int* array, int size);

void createArrayOfThreads(ThreadData* threads_data, HANDLE* threads_handles, int threads_count, int* array, int array_size, HANDLE start_event);