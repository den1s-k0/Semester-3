#pragma once

#include <iostream>
#include "thread_data.h"

using namespace std;

namespace MARKER_CODES {
	const int TIME_TO_SLEEP = 5;

	const int SUCCES = 0;

	const int WAIT_FAIL = -1;
}

DWORD WINAPI MarkerThread(LPVOID parametr);
