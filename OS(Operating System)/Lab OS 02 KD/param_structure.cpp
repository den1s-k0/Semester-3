#include "param_structure.h"

ParamStructure::ParamStructure(): size(0), min(0), max(0), average(0)
{
	Mas = NULL;
}

ParamStructure::~ParamStructure()
{
	if (Mas != NULL) {
		delete[] Mas;
	}
}

int ParamStructure::createMas() {
	cin >> this->size;
	if (size < 1)
		return ReturnParamCodes::ERROR_INVALID_LENGTH;
	this->Mas = new int[this->size];
	for (int i = 0; i < this->size; i++) {
		cin >> this->Mas[i];
	}
	return ReturnParamCodes::SUCCESS;
}
