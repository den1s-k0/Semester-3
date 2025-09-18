#pragma once

#include <iostream>

using namespace std;

struct employee {
	int num; // ID
	char name[10]; // employee name
	double hours; // number of hours
};
ostream& operator <<(ostream& out, employee& a);
istream& operator >>(istream& in, employee& a);