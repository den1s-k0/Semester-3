#include "process_manager.h"

bool ProcessInfo::launchClientProcess(const string& pipeName, int employeeCount) {
    string command = "Client.exe \"" + pipeName + "\" " + to_string(employeeCount);

    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(
        NULL,
        const_cast<char*>(command.c_str()),
        NULL,
        NULL,
        FALSE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &si,
        &pi
    )) {
        cerr << "Failed to start client process" << endl;
        return false;
    }

    return true;
}

void ProcessInfo::closeProcess() {
    WaitForSingleObject(pi.hProcess, 1000);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

bool startClientThread(const string& pipeName, int employeeCount, RecordLock* locks, const string& fileName) {
    ThreadParams* params = new ThreadParams{ pipeName, employeeCount, locks, fileName };

    HANDLE hThread = CreateThread(
        NULL,
        0,
        clientHandler,
        params,
        0,
        NULL
    );

    if (hThread == NULL) {
        delete params;
        return false;
    }

    CloseHandle(hThread);
    return true;
}

DWORD WINAPI clientHandler(LPVOID param) {
    ThreadParams* params = static_cast<ThreadParams*>(param);

    HANDLE hPipe = createNamedPipe(params->pipeName);
    if (!hPipe) {
        delete params;
        return 1;
    }

    ProcessInfo process;
    if (!process.launchClientProcess(params->pipeName, params->employeeCount)) {
        closeNamedPipe(hPipe);
        delete params;
        return 1;
    }

    if (!connectClientToPipe(hPipe)) {
        process.closeProcess();
        closeNamedPipe(hPipe);
        delete params;
        return 1;
    }

    cout << "Client connected" << endl;

    while (true) {
        int operation;
        DWORD bytesRead;

        if (!ReadFile(hPipe, &operation, sizeof(operation), &bytesRead, NULL)) {
            break;
        }

        if (operation == OperationType::END_OPERATION) {
            break;
        }

        int recordIndex;
        ReadFile(hPipe, &recordIndex, sizeof(recordIndex), &bytesRead, NULL);

        if (recordIndex < 1 || recordIndex > params->employeeCount) {
            break;
        }

        if (operation == OperationType::READ_OPERATION) {
            enterReadLock(params->locks[recordIndex - 1]);

            fstream file(params->fileName, ios::in | ios::binary);
            Employee emp;
            if (readEmployeeFromFile(file, recordIndex - 1, emp)) {
                WriteFile(hPipe, &emp, sizeof(emp), &bytesRead, NULL);
            }
            file.close();

            exitReadLock(params->locks[recordIndex - 1]);
        }
        else if (operation == OperationType::WRITE_OPERATION) {
            enterWriteLock(params->locks[recordIndex - 1]);

            Employee emp;
            ReadFile(hPipe, &emp, sizeof(emp), &bytesRead, NULL);

            fstream file(params->fileName, ios::in | ios::out | ios::binary);
            if (writeEmployeeToFile(file, recordIndex - 1, emp)) {
                bool success = true;
                WriteFile(hPipe, &success, sizeof(success), &bytesRead, NULL);
            }
            file.close();

            exitWriteLock(params->locks[recordIndex - 1]);
        }
    }

    process.closeProcess();
    closeNamedPipe(hPipe);
    delete params;

    return 0;
}