#pragma once

#include <iostream>
#include "linked_list.h"

using namespace std;

namespace ReturnDataType {

	const int WRONG_INPUT = -1;

	const int INT = 1;

	const int LONGLONG = 2;

	const int STRING = 3;

	const int CHAR = 4;

	const int BOOL = 5;

}

int ChooseDataType();

int RunList();


