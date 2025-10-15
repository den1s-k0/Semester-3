#include "main.h"

int main() {
	ParamStructure obj;
	if (!(obj.createMas() == ReturnParamCodes::SUCCESS))
		return ReturnMainCodes::ERROR_CREATING_ARRAY;
	
	DWORD IDMinMax, IDAverage;
	HANDLE hMinMax = CreateThread(NULL, 0, MinMaxThread, &obj, 0, &IDMinMax);
	HANDLE hAverage = CreateThread(NULL, 0, AverageThread, &obj, 0, &IDAverage);
	if (!hMinMax)
		return ReturnMainCodes::ERROR_CREATING_THREAD_MINMAX;
	if (!hAverage)
		return ReturnMainCodes::ERROR_CREATING_THREAD_AVERAGE;

	WaitForSingleObject(hMinMax, INFINITE);
	WaitForSingleObject(hAverage, INFINITE);

	obj.ArrayChange();

	CloseHandle(hMinMax);
	CloseHandle(hAverage);


	return ReturnMainCodes::SUCCESS;
}