#pragma once

#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

string cinString(int min, int max, string message);

int cinInt(int min, int max, string message);

bool waitWithMessage(HANDLE handle, const string& wait_message);