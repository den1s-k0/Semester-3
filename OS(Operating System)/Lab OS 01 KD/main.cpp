#include "main.h"

int main()
{

	string BinName, BinInputs, BinPath, ReportName, ReportInputs, ReportPath;
	int employeeNumber, hourly_rate;
	cout << "\nEnter bin-file name: ";
	cin >> BinName;
	BinPath = "C:\\PathToBinFile\\" + BinName + ".bin";
	cout << "\nEnter number of employees: ";
	cin >> employeeNumber;

	BinInputs = "Creator.exe \"" + BinPath + "\" " + to_string(employeeNumber);
	startProcess(BinInputs);
	ReadBinFile(BinPath);

	cout << "\nEnter report-file name: ";
	cin >> ReportName;
	ReportPath = "C:\\PathToTxtFile\\\\" + ReportName + ".txt";
	cout << "\nEnter hourly rate: ";
	cin >> hourly_rate;

	ReportInputs = "Reporter.exe \"" + BinPath + "\" \"" + ReportPath + "\" " + to_string(hourly_rate);
	startProcess(ReportInputs);
	ReadTxtFile(ReportPath);

	return 0;
}
