#include "ThreadData.h"

ThreadData::ThreadData()
    : thread_id(-1), array(NULL), array_size(0),
    start_event(NULL), pause_event(NULL), control_event(NULL),
    marked_count(0), failed_index(-1) {
}

ThreadData::ThreadData(int id, int* arr, int size, HANDLE start, HANDLE pause, HANDLE control) 
    : thread_id(id), array(arr), array_size(size),
    start_event(start), pause_event(pause), control_event(control),
    marked_count(0), failed_index(-1) {}

ThreadData::~ThreadData()
{
    if (array) {
        delete[] array;
    }
}
