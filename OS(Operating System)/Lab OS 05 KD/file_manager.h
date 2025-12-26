#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "employee.h"

using namespace std;

bool createEmployeeFile(const string& fileName, int employeeCount);
void displayEmployeeFile(const string& fileName, int employeeCount);
int inputIntInRange(int min, int max, const string& message);