#include "employee.h"

Employee::Employee() : id(0), hours(0.0) {
    memset(name, 0, sizeof(name));
}

Employee::Employee(int empId, const string& empName, double empHours)
    : id(empId), hours(empHours) {
    memset(name, 0, sizeof(name));
    if (!empName.empty()) {
        size_t copySize = min(empName.size(), static_cast<size_t>(9));
        strncpy_s(name, empName.c_str(), copySize);
    }
}

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