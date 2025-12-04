#pragma once

#include <iostream>
#include <cstdlib>
#include "circular_queue.h"
#include "process_manager.h"

using namespace std;

namespace SENDER_RETURN_CODES{
	const int SUCCESS = 0;
	const int ARGC_ERROR = 1;
	const int EVENT_ERROR = 2;
	const int SYNC_OBJECT_ERROR = 3;
}

namespace SENDER_SIZES_CODES {
	const int MAX_STRING_SIZE = 20;
	const int MIN_STRING_SIZE = 0;

	const int MAX_MESSAGE_SIZE = 20;
}

namespace SENDER_CHOICE_CODES {
	const int SEND_CHOICE = 1;
	const int EXIT_CHOICE = 2;
}