#include "core.h"

bool IsNumber(string str)
{
	regex numb("\\d+");
	if (regex_match(str, numb))
		return ReturnIsNumberCodes::Yes_it_is_Number;
	return ReturnIsNumberCodes::No_it_isnt_Number;
}

bool IsPalend(string str)
{
	if (str.length() == 0)
		return ReturnIsPalendCodes::No_it_isnt_Palend;
	for (int i = 0; i < str.length() / 2; i++) {
		if (str[i] != str[str.length() - 1 - i])
			return ReturnIsPalendCodes::No_it_isnt_Palend;
	}
	return ReturnIsPalendCodes::Yes_it_is_Palend;
}

int PalendNumberVerif() {
	string input;
	cout << "Enter Number: ";
	cin >> input;

	if (IsNumber(input)) {
		if (IsPalend(input)) {
			cout << "Number is palendrome\n";
			return ReturnPalendNumberVerifCodes::Yes_it_is_Palend;
		}
		cout << "Number isn't palendrome\n";
		return ReturnPalendNumberVerifCodes::No_it_isnt_Palend;
	}
	cout << "Entered data is wrong\n";
	return ReturnPalendNumberVerifCodes::Wrong_Number;
}

int TestPalendNumberVerif(string input) {
	if (IsNumber(input)) {
		if (IsPalend(input)) {
			cout << "Number is palendrome\n";
			return ReturnPalendNumberVerifCodes::Yes_it_is_Palend;
		}
		cout << "Number isn't palendrome\n";
		return ReturnPalendNumberVerifCodes::No_it_isnt_Palend;
	}
	cout << "Entered data is wrong\n";
	return ReturnPalendNumberVerifCodes::Wrong_Number;
}