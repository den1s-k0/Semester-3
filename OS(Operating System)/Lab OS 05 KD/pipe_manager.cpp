#include "pipe_manager.h"

HANDLE createNamedPipe(const string& pipeName) {
    HANDLE hPipe = CreateNamedPipe(
        pipeName.c_str(),
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        0,
        0,
        0,
        NULL
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        cerr << "Failed to create named pipe" << endl;
        return NULL;
    }

    return hPipe;
}

bool connectClientToPipe(HANDLE hPipe) {
    return ConnectNamedPipe(hPipe, NULL);
}

HANDLE connectToNamedPipe(const string& pipeName) {
    HANDLE hPipe = CreateFile(
        pipeName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        cerr << "Failed to connect to pipe" << endl;
        return NULL;
    }

    return hPipe;
}

bool closeNamedPipe(HANDLE hPipe) {
    return CloseHandle(hPipe);
}