#include "thread_data.h"

ThreadData::ThreadData()
    : thread_id(-1), array(nullptr), array_size(0),
    start_event(nullptr), pause_event(nullptr), control_event(nullptr),
    marked_count(0), failed_index(-1) {
}

ThreadData::ThreadData(int id, int* arr, int size, HANDLE start, HANDLE pause, HANDLE control)
    : thread_id(id), array(arr), array_size(size),
    start_event(start), pause_event(pause), control_event(control),
    marked_count(0), failed_index(-1) {
}