#include "process_manager.h"


using namespace std;

bool create_sync_objects(const string& file_name, int queue_capacity,
    HANDLE& hMutex, HANDLE& hEmpty, HANDLE& hFull) {
    string mutex_name = file_name + "_mtx";
    string empty_name = file_name + "_emp";
    string full_name = file_name + "_ful";

    hMutex = CreateMutexA(nullptr, FALSE, mutex_name.c_str());
    if (!hMutex) {
        cerr << "CreateMutex failed\n";
        return false;
    }

    hEmpty = CreateSemaphoreA(nullptr, queue_capacity, queue_capacity, empty_name.c_str());
    if (!hEmpty) {
        cerr << "CreateSemaphore(empty) failed\n";
        CloseHandle(hMutex);
        return false;
    }

    hFull = CreateSemaphoreA(nullptr, 0, queue_capacity, full_name.c_str());
    if (!hFull) {
        cerr << "CreateSemaphore(full) failed\n";
        CloseHandle(hMutex);
        CloseHandle(hEmpty);
        return false;
    }

    return true;
}

bool open_sync_objects(const string& file_name,
    HANDLE& hMutex, HANDLE& hEmpty, HANDLE& hFull) {
    string mutex_name = file_name + "_mtx";
    string empty_name = file_name + "_emp";
    string full_name = file_name + "_ful";

    hMutex = OpenMutexA(SYNCHRONIZE, FALSE, mutex_name.c_str());
    hEmpty = OpenSemaphoreA(SYNCHRONIZE | SEMAPHORE_MODIFY_STATE, FALSE, empty_name.c_str());
    hFull = OpenSemaphoreA(SYNCHRONIZE | SEMAPHORE_MODIFY_STATE, FALSE, full_name.c_str());

    if (!hMutex || !hEmpty || !hFull) {
        return false;
    }

    return true;
}

HANDLE create_ready_event(const string& base_name, int index) {
    string event_name = base_name + "_rdy_" + to_string(index + 1);
    return CreateEventA(nullptr, FALSE, FALSE, event_name.c_str());
}

bool start_sender_process(const string& command, PROCESS_INFORMATION& pi) {
    vector<char> cmd_buf(command.begin(), command.end());
    cmd_buf.push_back('\0');

    STARTUPINFOA si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (CreateProcessA(nullptr, cmd_buf.data(), nullptr, nullptr,
        FALSE, CREATE_NEW_CONSOLE, nullptr, nullptr, &si, &pi)) {
        return true;
    }
    return false;
}