#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>

using namespace std;

struct employee {
	int num; // ID
	char name[10]; // employee name
	double hours; // number of hours

	employee();
	employee(int n, const char* nm, double h);
	~employee() {};
};
ostream& operator <<(ostream& out, employee& a);
istream& operator >>(istream& in, employee& a);