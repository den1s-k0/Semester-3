#include "employee.h"

ostream& operator<<(ostream& out, Employee& emp) {
    out << "ID: " << emp.id << endl;
    out << "Name: " << emp.name << endl;
    out << "Hours: " << emp.hours << endl;
    return out;
}

istream& operator>>(istream& in, Employee& emp) {
    cout << "Enter employee ID: ";
    in >> emp.id;
    cout << "Enter name (max 9 chars): ";
    in >> emp.name;
    cout << "Enter hours worked: ";
    in >> emp.hours;
    return in;
}

bool readEmployeeFromFile(fstream& file, int index, Employee& emp) {
    if (!file) return false;

    file.seekg(index * sizeof(Employee), ios::beg);
    file.read(reinterpret_cast<char*>(&emp), sizeof(Employee));

    return !file.fail();
}

bool writeEmployeeToFile(fstream& file, int index, Employee& emp) {
    if (!file) return false;

    file.seekp(index * sizeof(Employee), ios::beg);
    file.write(reinterpret_cast<char*>(&emp), sizeof(Employee));

    return !file.fail();
}