#pragma once

#include <iostream>
#include <windows.h>

using namespace std;

struct ThreadData {
    int thread_id;
    int* array;
    int array_size;
    boolean is_break;

    HANDLE start_event;
    HANDLE pause_event;
    HANDLE break_event;
    HANDLE continue_event;


    int marked_count;

    ThreadData();

    ThreadData(int id, int* arr, int size, HANDLE start, HANDLE pause, HANDLE hcontinue, HANDLE hbreak);
};