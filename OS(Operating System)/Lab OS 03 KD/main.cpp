#include "main.h"

int main()
{
	int array_size = cinIntLessEqualN(MAX_SIZES_OF_ARRAYS::MAX_SIZE_OF_ARRAY, "Enter array size: ");
	int* array;
	createArrayOfZeros(array, array_size);

	int threads_count = cinIntLessEqualN(MAX_SIZES_OF_ARRAYS::MAX_COUNT_OF_THREADS, "Enter count of threads: ");

	HANDLE start_event = CreateEvent(NULL, TRUE, FALSE, NULL);

	ThreadData* threads_data;
	HANDLE* threads_handles;


	return 0;
}
