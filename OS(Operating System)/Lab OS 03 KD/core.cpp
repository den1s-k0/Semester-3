#include "core.h"

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

