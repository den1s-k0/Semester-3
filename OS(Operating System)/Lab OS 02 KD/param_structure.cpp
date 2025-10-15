#include "param_structure.h"

ParamStructure::ParamStructure(): size(0), min(0), max(0), average(0)
{
	Mas = NULL;
}

ParamStructure::ParamStructure(int s): size(s), min(0), max(0), average(0)
{
	if (size < 1)
		size = 0;
	Mas = new int[size];
}

ParamStructure::ParamStructure(int s, int mi, int ma, int av): size(s), min(mi), max(ma), average(av)
{
	if (size < 1) 
		size = 0;
	Mas = new int[size];
}

ParamStructure::~ParamStructure()
{
	if (Mas != NULL) {
		delete[] Mas;
	}
}

int ParamStructure::createMas() {
	cout << "Enter array size: ";
	cin >> this->size;
	if (size < 1)
		return ReturnParamCodes::ERROR_INVALID_LENGTH;
	this->Mas = new int[this->size];
	cout << "Enter " << this->size << " array elements: ";
	for (int i = 0; i < this->size; i++) {
		cin >> this->Mas[i];
	}
	cout << endl;
	return ReturnParamCodes::SUCCESS;
}

int ParamStructure::ArrayChange() {
	if (Mas == NULL)
		return ReturnParamCodes::ERROR_NULL_PONTER;
	if (size < 1)
		return ReturnParamCodes::ERROR_INVALID_LENGTH;

	for (int i = 0; i < this->size; i++) {
		if (this->Mas[i] == min || this->Mas[i] == max)
			Mas[i] = average;
		cout << Mas[i] << " ";
	}
	cout << endl;
	return ReturnParamCodes::SUCCESS;
}
