#pragma once

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <cstring>

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

bool startProcess(string address);

bool readBinFile(string NAME);

bool readTextFile(string NAME);