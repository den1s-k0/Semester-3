#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>

using namespace std;

int main()
{

	string BinName, BinAddress, ReportName, ReportAddress;
	int employeeNumber, hourly_rate;
	cout << "\nEnter bin-file name: ";
	cin >> BinName;
	cout << "\nEnter number of employees: ";
	cin >> employeeNumber;

	BinAddress = "Creator.exe " + BinName + ".bin " + to_string(employeeNumber);

	STARTUPINFO siCreator;
	PROCESS_INFORMATION piCreator;
	ZeroMemory(&siCreator, sizeof(STARTUPINFO));
	siCreator.cb = sizeof(STARTUPINFO);
	if (!CreateProcessA(NULL, (LPSTR)BinAddress.c_str(), NULL, NULL, FALSE,
		0, NULL, NULL, &siCreator, &piCreator))
	{
		_cputs("The new process is not created.\n");
		_cputs("Check a name of the process.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return 0;
	}
	_cputs("The new process is created.\n");
	WaitForSingleObject(piCreator.hProcess, INFINITE);
	CloseHandle(piCreator.hThread);
	CloseHandle(piCreator.hProcess);

	cout << "\nEnter report-file name: ";
	cin >> ReportName;
	cout << "\nEnter hourly rate: ";
	cin >> hourly_rate;

	ReportAddress = "Reporter.exe " + BinName + ".bin " + ReportName + ".txt " + to_string(hourly_rate);

	STARTUPINFO siReporter;
	PROCESS_INFORMATION piReporter;
	ZeroMemory(&siReporter, sizeof(STARTUPINFO));
	siReporter.cb = sizeof(STARTUPINFO);
	if (!CreateProcess(NULL, (LPSTR)ReportAddress.c_str(), NULL, NULL, FALSE,
		0, NULL, NULL, &siReporter, &piReporter))
	{
		_cputs("The new process is not created.\n");
		_cputs("Check a name of the process.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return 0;
	}
	_cputs("The new process is created.\n");
	WaitForSingleObject(piReporter.hProcess, INFINITE);
	CloseHandle(piReporter.hThread);
	CloseHandle(piReporter.hProcess);

	return 0;
}
