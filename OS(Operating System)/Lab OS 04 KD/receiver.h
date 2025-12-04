#pragma once

#include <iostream>
#include <vector>
#include "circular_queue.h"
#include "process_manager.h"

using namespace std;

namespace RECEIVER_RETURN_CODES {
	const int SUCCESS = 0;
	const int FILE_ERROR = 1;
	const int EVENT_ERROR = 2;
	const int PROCESS_ERROR = 3;
	const int WAIT_ERROR = 4;
}

namespace RECEIVER_SIZES_CODES {
	const int MAX_FILE_NAME = 100;
	const int MIN_FILE_NAME = 1;

	const int MAX_QUEUE_CAPACITY = 10000;
	const int MIN_QUEUE_CAPACITY = 1;

	const int MAX_SENDER_COUNT = 1000;
	const int MIN_SENDER_COUNT = 1;
}

namespace RECEIVER_CHOICE_CODES {
	const int READ_CHOICE = 1;
	const int EXIT_CHOICE = 2;
}