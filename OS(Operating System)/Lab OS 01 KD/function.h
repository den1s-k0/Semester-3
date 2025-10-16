#pragma once

#include <conio.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <cstring>

#include "employee.h"

bool startProcess(string address);

bool startProcessCMD(string commandLine);

bool ReadBinFile(string NAME);

bool ReadTxtFile(string NAME);