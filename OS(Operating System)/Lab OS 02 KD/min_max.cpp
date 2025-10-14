#include "min_max.h"

int findMin(int* mas, int size, int& result) {
	if (mas == NULL)
		return ReturnMinMaxCodes::ERROR_NULL_PONTER;
	if (size < 1)
		return ReturnMinMaxCodes::ERROR_INVALID_LENGTH;
	int time = 7;
	result = mas[0];
	for (int i = 1; i < size; i++) {
		if (result > mas[i]) result = mas[i];
		Sleep(time);
	}
	return ReturnMinMaxCodes::SUCCESS;
}

int findMax(int* mas, int size, int& result) {
	if (mas == NULL)
		return ReturnMinMaxCodes::ERROR_NULL_PONTER;
	if (size < 1)
		return ReturnMinMaxCodes::ERROR_INVALID_LENGTH;
	int time = 7;
	result = mas[0];
	for (int i = 1; i < size; i++) {
		if (result < mas[i]) result = mas[i];
		Sleep(time);
	}
	return ReturnMinMaxCodes::SUCCESS;
}