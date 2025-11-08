#include "thread_data.h"

ThreadData::ThreadData()
    : thread_id(-1), array(nullptr), array_size(0), is_break(false),
    start_event(nullptr), pause_event(nullptr), continue_event(nullptr), 
    break_event(nullptr), marked_count(0) {}

ThreadData::ThreadData(int id, int* arr, int size, HANDLE start, HANDLE pause, HANDLE hcontinue, HANDLE hbreak)
    : thread_id(id), array(arr), array_size(size), is_break(false),
    start_event(start), pause_event(pause), continue_event(hcontinue),
    break_event(hbreak), marked_count(0) {}
