#pragma once

#include <iostream>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include "thread_data.h"
#include "marker.h"

using namespace std;

namespace ReturnCoreCodes {
	const int SUCCES = 0;
}

extern CRITICAL_SECTION console_cs;
extern CRITICAL_SECTION array_cs;

int cinIntLessEqualN(int max, string str);

void printArray(int* array, int array_count);

void createArrayOfThreads(ThreadData* threads_data, HANDLE* threads_handles, int threads_count, int* array, int array_size, HANDLE start_event);

void WaitAllPausedEvents(ThreadData* threads_data, int threads_count, int active_threads);

void breakThread(ThreadData* threads_data, HANDLE* threads_handles, int& active_threads, int thread_index);

void continueThreads(ThreadData* threads_data, HANDLE* threads_handles, int threads_count);
