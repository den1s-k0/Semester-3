#include "min_max.h"

int findMin(int* mas, int size) {
	if (size == 0 || mas == NULL)
		return 0;
	int min = mas[0], time = 7;
	for (int i = 1; i < size; i++) {
		if (min > mas[i]) min = mas[i];
		Sleep(time);
	}
	return min;
}

int findMax(int* mas, int size) {
	if (size == 0 || mas == NULL)
		return 0;
	int max = mas[0], time = 7;
	for (int i = 1; i < size; i++) {
		if (max < mas[i]) max = mas[i];
		Sleep(time);
	}
	return max;
}