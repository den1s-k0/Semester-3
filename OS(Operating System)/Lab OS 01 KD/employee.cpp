#include "header.h"

ostream& operator <<(ostream& out, employee& a) {
	return out << "ID: " << a.num << "\t Name: " << a.name << "\t Number of hours: " << a.hours << endl;
}

istream& operator >>(istream& in, employee& a) {
	cout << "\nEnter ID: ";
	in >> a.num;
	cout << "\nEnter employee name: ";
	in >> a.name;
	cout << "\nEnter number of hours: ";
	in >> a.hours;

	return in;
}
