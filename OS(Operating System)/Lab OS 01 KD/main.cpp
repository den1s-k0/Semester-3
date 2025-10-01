#include <conio.h>
#include "header.h"

int main()
{

	string BinName, BinAddress, ReportName, ReportAddress;
	int employeeNumber, hourly_rate;
	cout << "\nEnter bin-file name: ";
	cin >> BinName;
	BinName += ".bin";
	cout << "\nEnter number of employees: ";
	cin >> employeeNumber;

	BinAddress = "Creator.exe " + BinName + " " + to_string(employeeNumber);
	startProcess(BinAddress);
	ReadBinFile(BinName);

	cout << "\nEnter report-file name: ";
	cin >> ReportName;
	ReportName += ".txt";
	cout << "\nEnter hourly rate: ";
	cin >> hourly_rate;

	ReportAddress = "Reporter.exe " + BinName + " " + ReportName + " " + to_string(hourly_rate);
	startProcess(ReportAddress);
	ReadTxtFile(ReportName);

	return 0;
}