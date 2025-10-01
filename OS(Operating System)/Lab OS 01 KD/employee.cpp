#include "header.h"

employee::employee() : num(0), hours(0.0) {
	strcpy(name, "");
}
employee::employee(int n, const char* nm, double h) : num(n), hours(h) {
	strncpy(name, nm, sizeof(name) - 1);
	if (strlen(nm) > 9) {
		name[sizeof(name) - 2] = '*';
	}
	name[sizeof(name) - 1] = '\0';
}

ostream& operator <<(ostream& out, employee& a) {
	out << fixed << setprecision(2);
	return out << "ID: " << a.num << "\t Name: " << a.name << "\t Number of hours: " << a.hours << endl;
}

istream& operator >>(istream& in, employee& a) {
	cout << "\nEnter ID: ";
	in >> a.num;

	cout << "\nEnter employee name: ";
	string s;
	in >> s;
	strncpy(a.name, s.c_str(), sizeof(a.name) - 1);
	if (s.size() > 9) {
		a.name[sizeof(a.name) - 2] = '*';
	}
	a.name[sizeof(a.name) - 1] = '\0';

	cout << "\nEnter number of hours: ";
	in >> a.hours;

	return in;
}