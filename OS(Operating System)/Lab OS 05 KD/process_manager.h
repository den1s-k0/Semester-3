#pragma once

#include <iostream>
#include <windows.h>
#include <string>
#include "record_lock.h"
#include "shared_constants.h"
#include "pipe_manager.h"
#include "employee.h"

using namespace std;

struct ProcessInfo {
    PROCESS_INFORMATION pi;
    bool launchClientProcess(const string& pipeName, int employeeCount);
    void closeProcess();
};

bool startClientThread(const string& pipeName, int employeeCount, RecordLock* locks, const string& fileName);
DWORD WINAPI clientHandler(LPVOID param);