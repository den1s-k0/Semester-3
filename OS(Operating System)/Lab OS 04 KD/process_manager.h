#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>

using namespace std;

bool create_sync_objects(const string& file_name, int queue_capacity,
    HANDLE& hMutex, HANDLE& hEmpty, HANDLE& hFull);
bool open_sync_objects(const string& file_name,
    HANDLE& hMutex, HANDLE& hEmpty, HANDLE& hFull);
HANDLE create_ready_event(const string& base_name, int index);
bool start_sender_process(const string& command, PROCESS_INFORMATION& pi);