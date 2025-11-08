#include "main.h"

int main()
{
	InitializeCriticalSection(&console_cs);
	InitializeCriticalSection(&array_cs);
	int array_size = cinIntLessEqualN(MAX_SIZES_OF_ARRAYS::MAX_SIZE_OF_ARRAY, "Enter array size: ");
	int* array = new int[array_size]();

	int threads_count = cinIntLessEqualN(MAX_SIZES_OF_ARRAYS::MAX_COUNT_OF_THREADS, "Enter count of threads: ");
	int active_threads = threads_count;

	HANDLE start_event = CreateEvent(NULL, TRUE, FALSE, NULL);
	ThreadData* threads_data = new ThreadData[threads_count];;
	HANDLE* threads_handles = new HANDLE[threads_count];

	createArrayOfThreads(threads_data, threads_handles, threads_count, array, array_size, start_event);

	SetEvent(start_event);

	while (active_threads > 0) {

		WaitAllPausedEvents(threads_data, threads_count, active_threads);

		printArray(array, array_size);

		int ind;
		do {
			ind = cinIntLessEqualN(threads_count, "Enter ID of an element that will be complited: ");
			ind--;
		} while (threads_data[ind].is_break);

		breakThread(threads_data, threads_handles, active_threads, ind);

		printArray(array, array_size);

		continueThreads(threads_data, threads_handles, threads_count);
	}

	delete[] array;
	delete[] threads_data;
	delete[] threads_handles;
	CloseHandle(start_event);
	DeleteCriticalSection(&console_cs);
	DeleteCriticalSection(&array_cs);
	return 0;
}
