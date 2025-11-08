#pragma once

#include <iostream>
#include <windows.h>
#include "thread_data.h"

using namespace std;

namespace MARKER_CODES {
	const int TIME_TO_SLEEP = 5;

	const int SUCCES = 0;

	const int WAIT_FAIL = -1;
}

extern CRITICAL_SECTION console_cs;
extern CRITICAL_SECTION array_cs;


DWORD WINAPI MarkerThread(LPVOID parametr);
