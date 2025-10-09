#include "average.h"

int calculateAverage(int* mas, int size) {
	int sum = 0, time = 12;
	if (size == 0 || mas == NULL) 
		return 0;
	for (int i = 0; i < size; i++) {
		sum += mas[i];
		Sleep(time);
	}
	return sum / size;
}