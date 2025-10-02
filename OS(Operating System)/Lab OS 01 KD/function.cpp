#include "header.h"
#include <conio.h>

bool startProcess(string address) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	if (!CreateProcess(NULL, (LPSTR)address.c_str(), NULL, NULL, FALSE,
		0, NULL, NULL, &si, &pi))
	{
		_cputs("The new process is not created.\n");
		_cputs("Check a name of the process.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return 1;
	}
	_cputs("The new process is created.\n");
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	return 2;
}

bool startProcessCMD(string commandLine) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	char cmd[1024];
	strcpy(cmd, commandLine.c_str());

	if (!CreateProcess(NULL, cmd, NULL, NULL, FALSE,
		0, NULL, NULL, &si, &pi))
	{
		_cputs("The new process is not created.\n");
		_cputs("Check a name of the process.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return 1;
	}
	_cputs("The new process is created.\n");
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	return 2;
}

bool ReadBinFile(string NAME) {
	ifstream in(NAME, ios::binary);
	if (!in.is_open()) {
		cerr << "Error\nBinFile isn't open";
		return 1;
	}
	employee tipok;
	cout << endl;
	while (in.read(reinterpret_cast<char*>(&tipok), sizeof(employee))) {
		cout << tipok;
	}
	in.close();
	return 0;
}

bool ReadTxtFile(string NAME) {
	ifstream in(NAME);
	if (!in.is_open()) {
		cerr << "Error\nTextFile isn't open";
		return 1;
	}
	string line;
	cout << endl;
	while (getline(in, line)) {
		cout << line << endl;
	}
	in.close();
	return 0;
}