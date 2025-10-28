#include "core.h"

int cinIntLessEqualN(int max, string str) {
	int n;
	cout << str;
	cin >> n;
	while (cin.fail() || n > max || n < 0) {
		cin.clear();
		cin.ignore();
		cout << "Wrong input\nEnter number from 0 to " << max << ": ";
		cin >> n;
	}
	return n;
}

void createArrayOfZeros(int* array, int size) {
	if (array) {
		delete[] array;
	}
	array = new int[size];
	for (int i = 0; i < size; i++) {
		array[i] = 0;
	}
}

void createArrayOfThreads(ThreadData* threads_data, HANDLE* threads_handles, int threads_count, int* array, int array_size, HANDLE start_event) {
	if (threads_data) {
		delete[] threads_data;
	}
	if (threads_handles) {
		delete[] threads_handles;
	}
	threads_data = new ThreadData[threads_count];
	threads_handles = new HANDLE[threads_count];

	for (int i = 0; i < threads_count; i++) {

		HANDLE pause_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		HANDLE control_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);

		threads_data[i].thread_id = i + 1;
		threads_data[i].array = array;
		threads_data[i].array_size = array_size;
		threads_data[i].start_event = start_event;
		threads_data[i].pause_event = pause_event;
		threads_data[i].control_event = control_event;

		HANDLE hThread = CreateThread(nullptr, 0, MarkerThread, &threads_data[i],	0, nullptr);

		threads_handles[i] = hThread;
	}

}

