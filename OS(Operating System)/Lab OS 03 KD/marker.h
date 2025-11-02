#pragma once

#include <iostream>
#include "thread_data.h"

using namespace std;

namespace MARKER_TIME {
	const int TIME_TO_SLEEP = 5;
}

DWORD WINAPI MarkerThread(LPVOID parametr);