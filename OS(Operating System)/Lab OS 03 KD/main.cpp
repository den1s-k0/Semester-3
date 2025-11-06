#include "main.h"

int main()
{
	int array_size = cinIntLessEqualN(MAX_SIZES_OF_ARRAYS::MAX_SIZE_OF_ARRAY, "Enter array size: ");
	int* array = new int[array_size]();

	int threads_count = cinIntLessEqualN(MAX_SIZES_OF_ARRAYS::MAX_COUNT_OF_THREADS, "Enter count of threads: ");

	HANDLE start_event = CreateEvent(NULL, TRUE, FALSE, NULL);
	ThreadData* threads_data = new ThreadData[threads_count];;
	HANDLE* threads_handles = new HANDLE[threads_count];

	createArrayOfThreads(threads_data, threads_handles, threads_count, array, array_size, start_event);

	delete[] array;
	delete[] threads_data;
	delete[] threads_handles;
	CloseHandle(start_event);

	return 0;
}
