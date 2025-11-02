#include "marker.h"

DWORD WINAPI MarkerThread(LPVOID parametr) {

	ThreadData* param = static_cast<ThreadData*>(parametr);

	WaitForSingleObject(param->start_event, INFINITE);

	srand(param->thread_id);

	while (true) {
		int num = rand() % param->array_size;
		if (param->array[num] == 0) {
			Sleep(MARKER_TIME::TIME_TO_SLEEP);
			param->array[num] = param->thread_id;
			param->marked_count++;
			Sleep(MARKER_TIME::TIME_TO_SLEEP);
		}
		else {
			cout << "\nThread ID: " << param->thread_id
				<< "\nNumber of marked elements: " << param->marked_count
				<< "\nIndex of an element that cannot be marked: " << num;

			SetEvent(param->pause_event);

			WaitForSingleObject(param->control_event, INFINITE);
		}
	}

	return 1;
}