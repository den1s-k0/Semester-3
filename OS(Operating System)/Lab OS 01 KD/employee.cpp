#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include <limits>

employee::employee() : num(0), hours(0.0) {
	strcpy(name, "");
}
employee::employee(int n, const char* nm, double h) : num(n), hours(h) {
    /*if(nm == nullptr) {
        name[0] = '-';
    }
    else {*/
        strncpy(name, nm, sizeof(name) - 1);
        if (strlen(nm) > 9) {
            name[sizeof(name) - 2] = '*';
        }
    //}
	name[sizeof(name) - 1] = '\0';
}

ostream& operator <<(ostream& out, employee& a) {
	out << fixed << setprecision(2);
	return out << "ID: " << a.num << "\t Name: " << a.name << "\t Number of hours: " << a.hours << endl;
}

istream& operator>>(istream& in, employee& a) {
    cout << "\nEnter ID: ";
    in >> a.num;
    //in.ignore(std::numeric_limits<std::streamsize>max(), '\n');

    cout << "\nEnter employee name: ";
    string s;
    in >> s;
    //getline(in, s);

    strncpy(a.name, s.c_str(), sizeof(a.name) - 1);
    a.name[sizeof(a.name) - 1] = '\0';

    if (s.size() >= sizeof(a.name)) {
        a.name[sizeof(a.name) - 2] = '*';
    }

    cout << "\nEnter number of hours: ";
    in >> a.hours;

    return in;
}
