#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include "header.h"


int main(int argc, char* argv[]) {
	ofstream out(argv[1], ios::binary);
	if (!out.is_open()) {
		cout << "Error\nFile isn't open";
	}
	else {
		employee tipok;
		for (int i = 0; i < stoi(argv[2]); i++) {
			cin >> tipok;
			out << tipok;
		}
	}
	out.close();
}