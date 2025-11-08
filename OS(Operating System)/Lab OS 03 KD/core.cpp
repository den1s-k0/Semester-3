#include "core.h"

CRITICAL_SECTION console_cs;
CRITICAL_SECTION array_cs;

int cinIntLessEqualN(int max, string str) {
	int n;
	cout << str;
	cin >> n;
	while (cin.fail() || n > max || n < 0) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Wrong input\nEnter number from 0 to " << max << ": ";
		cin >> n;
	}
	return n;
}

void printArray(int* array, int array_count) {
	cout << "\nArray: \n";
	for (int i = 0; i < array_count; i++) {
		cout << array[i] << " ";
	}
	cout << endl << endl;
}

void createArrayOfThreads(ThreadData* threads_data, HANDLE* threads_handles, int threads_count, int* array, int array_size, HANDLE start_event) {

	for (int i = 0; i < threads_count; i++) {

		HANDLE pause_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		HANDLE continue_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		HANDLE break_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);


		threads_data[i].thread_id = i + 1;
		threads_data[i].array = array;
		threads_data[i].array_size = array_size;
		threads_data[i].start_event = start_event;
		threads_data[i].pause_event = pause_event;
		threads_data[i].continue_event = continue_event;
		threads_data[i].break_event = break_event;


		HANDLE hThread = CreateThread(nullptr, 0, MarkerThread, &threads_data[i],	0, nullptr);

		threads_handles[i] = hThread;
	}
}

void WaitAllPausedEvents(ThreadData* threads_data, int threads_count, int active_threads) {
	HANDLE* pause_events = new HANDLE[active_threads];
	for (int i = 0, j = 0; i < threads_count && j < active_threads; i++) {
		if (!threads_data[i].is_break) {
			pause_events[j++] = threads_data[i].pause_event;
		}
	}

	WaitForMultipleObjects(active_threads, pause_events, TRUE, INFINITE);
	delete[] pause_events;
}

void breakThread(ThreadData* threads_data, HANDLE* threads_handles, int& active_threads, int thread_index) {
	if (!threads_data[thread_index].is_break) {
		SetEvent(threads_data[thread_index].break_event);

		WaitForSingleObject(threads_handles[thread_index], INFINITE);
		threads_data[thread_index].is_break = true;
		active_threads--;

		CloseHandle(threads_data[thread_index].pause_event);
		CloseHandle(threads_data[thread_index].continue_event);
		CloseHandle(threads_data[thread_index].break_event);
		CloseHandle(threads_handles[thread_index]);
	}
}

void continueThreads(ThreadData* threads_data, HANDLE* threads_handles, int threads_count) {
	for (int i = 0; i < threads_count; i++) {
		if (!threads_data[i].is_break) {
			SetEvent(threads_data[i].continue_event);
		}
	}
}

