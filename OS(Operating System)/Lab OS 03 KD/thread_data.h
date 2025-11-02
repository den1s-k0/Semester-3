#pragma once

#include <windows.h>

using namespace std;

struct ThreadData {
    int thread_id;
    int* array;
    int array_size;

    HANDLE start_event;
    HANDLE pause_event;
    HANDLE control_event;

    int marked_count;
    int failed_index;

    ThreadData();

    ThreadData(int id, int* arr, int size, HANDLE start, HANDLE pause, HANDLE control);
};