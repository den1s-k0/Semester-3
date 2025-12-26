#pragma once

#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

HANDLE createNamedPipe(const string& pipeName);
bool connectClientToPipe(HANDLE hPipe);
HANDLE connectToNamedPipe(const string& pipeName);
bool closeNamedPipe(HANDLE hPipe);