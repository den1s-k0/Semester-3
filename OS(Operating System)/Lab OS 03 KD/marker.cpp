#include "marker.h"

DWORD WINAPI MarkerThread(LPVOID parametr) {

	ThreadData* param = static_cast<ThreadData*>(parametr);

	WaitForSingleObject(param->start_event, INFINITE);

	srand(param->thread_id);

	while (true) {
		int num = rand() % param->array_size;
		if (param->array[num] == 0) {
			Sleep(MARKER_CODES::TIME_TO_SLEEP);
			param->array[num] = param->thread_id;
			param->marked_count++;
			Sleep(MARKER_CODES::TIME_TO_SLEEP);
		}
		else {
			cout << "\nThread ID: " << param->thread_id
				<< "\nNumber of marked elements: " << param->marked_count
				<< "\nIndex of an element that cannot be marked: " << num;

			SetEvent(param->pause_event);

            HANDLE array_events[2] = {param->continue_event, param->break_event};

            DWORD wait_result = WaitForMultipleObjects(2, array_events, FALSE, INFINITE);

            if (wait_result == WAIT_OBJECT_0) {
                ResetEvent(param->continue_event);
                ResetEvent(param->pause_event);
                continue;
            }
            else if (wait_result == WAIT_OBJECT_0 + 1) {
                for (int i = 0; i < param->array_size; i++) {
                    if (param->array[i] == param->thread_id) {
                        param->array[i] = 0;
                    }
                }
                break;
            }
            else if (wait_result == WAIT_FAILED) {
                cerr << "Marker " << param->thread_id << " WaitForMultipleObjects failed\n";
				return MARKER_CODES::WAIT_FAIL;
            }
		}
	}

	return MARKER_CODES::SUCCES;
}