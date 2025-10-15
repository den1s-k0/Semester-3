#include "core.h"

DWORD WINAPI MinMaxThread(LPVOID parametr)
{
	ParamStructure* param = static_cast<ParamStructure*>(parametr);
	if (!(findMin(param->Mas, param->size, param->min) == ReturnMinMaxCodes::SUCCESS))
		return ReturnCoreCodes::ERROR_MIN_SEARCH;
	if (!(findMax(param->Mas, param->size, param->max) == ReturnMinMaxCodes::SUCCESS))
		return 	ReturnCoreCodes::ERROR_MAX_SEARCH;

	cout << "Min = " << param->min << endl
		<< "Max = " << param->max << endl;

	return ReturnCoreCodes::SUCCESS;
}

DWORD WINAPI AverageThread(LPVOID parametr)
{
	ParamStructure* param = static_cast<ParamStructure*>(parametr);
	if (!(calculateAverage(param->Mas, param->size, param->average) == ReturnAverageCodes::SUCCESS))
		return ReturnCoreCodes::ERROR_AVERAGE_SEARCH;

	cout << "Average = " << param->average << endl;

	return ReturnCoreCodes::SUCCESS;
}