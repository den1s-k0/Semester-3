#include "average.h"

int calculateAverage(int* mas, int size, int& result) {
	if (mas == NULL)
		return ReturnAverageCodes::ERROR_NULL_PONTER;
	if (size < 1)
		return ReturnAverageCodes::ERROR_INVALID_LENGTH;
	int time = 12;
	result = mas[0];
	for (int i = 1; i < size; i++) {
		result += mas[i];
		Sleep(time);
	}
	result /= size;
	return ReturnAverageCodes::SUCCESS;
}