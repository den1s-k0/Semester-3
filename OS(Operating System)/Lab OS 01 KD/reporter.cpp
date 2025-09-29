#include "header.h"
#include <iomanip>

int main(int argc, char* argv[]) {
	ifstream in(argv[1], ios::binary);
	ofstream out(argv[2]);
	if(!in.is_open()){
		cout << "Error\nBinFile isn't open";
		return 1;
	}
	if(!out.is_open()){
		cout << "Error\nTextFile isn't create";
		return 2;
	}
	employee tipok;
	int i = 1;
	double salary;
	int hourly_rate = stoi(argv[3]);
	out << setw(8) << right << "| "
		<< setw(10) << "ID" << " | "
		<< setw(10) << "Name" << " | "
		<< setw(10) << "Hours" << " | "
		<< setw(10) << "Salary" << endl
		<< string(57, '-') << endl;
	while (in.read(reinterpret_cast<char*>(&tipok), sizeof(employee))) {
		salary = hourly_rate * tipok.hours;
		out << setw(5) << to_string(i) + "." << " | "
			<< setw(10) << tipok.num << " | "
			<< setw(10) << tipok.name << " | "
			<< setw(10) << fixed << setprecision(2) << tipok.hours << " | "
			<< setw(10) << fixed << setprecision(2) << salary
			<< endl;
		i++;
	}
	in.close();
	out.close();
	return 0;
}