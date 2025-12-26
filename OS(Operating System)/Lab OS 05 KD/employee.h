#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Employee {
    int id;
    char name[10];
    double hours;
};

ostream& operator<<(ostream& out, Employee& emp);
istream& operator>>(istream& in, Employee& emp);
bool readEmployeeFromFile(fstream& file, int index, Employee& emp);
bool writeEmployeeToFile(fstream& file, int index, Employee& emp);