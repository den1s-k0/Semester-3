#pragma once

#include <iostream>
#include <string>
#include <regex>

namespace ReturnIsNumberCodes {

	const bool Yes_it_is_Number = true;

	const bool No_it_isnt_Number = false;

}

namespace ReturnIsPalendCodes {

	const bool Yes_it_is_Palend = true;

	const bool No_it_isnt_Palend = false;

}

namespace ReturnPalendNumberVerifCodes {

	const int Yes_it_is_Palend = 0;

	const int No_it_isnt_Palend = 1;

	const int Wrong_Number = -1;
}

using namespace std;

bool IsNumber(string str);

bool IsPalend(string number);

int PalendNumberVerif();

int TestPalendNumberVerif(string input);