#include "header.h"
#include <iomanip>

int main(int argc, char* argv[]) {
	ifstream in(argv[1], ios::binary);
	ofstream out(argv[2]);
	if(!in.is_open()){
		cout << "Error\nBinFile isn't open";
		return 0;
	}
	if(!out.is_open()){
		cout << "Error\nTextFile isn't create";
		return 0;
	}
	employee tipok;
	int i = 1;
	double salary;
	int hourly_rate = stoi(argv[3]);
	out << setw(5)
		<< setw(5) << "ID" << " | "
		<< setw(10) << "Name" << " | "
		<< setw(5) << "Hours" << " | "
		<< setw(6) <<  "Salary";
	while (in.read(reinterpret_cast<char*>(&tipok), sizeof(employee))) {
		salary = hourly_rate * tipok.hours;
		out << setw(5) << to_string(i) + "."
			<< setw(5) << tipok.num << " | "
			<< setw(10) << tipok.name << " | "
			<< setw(5) << tipok.hours << " | "
			<< setw(6) << fixed << setprecision(2) << salary;
		i++;
	}
	in.close();
	out.close();
	return 0;
}
