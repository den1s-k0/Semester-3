#include "file_manager.h"

bool createEmployeeFile(const string& fileName, int employeeCount) {
    ofstream file(fileName, ios::binary);
    if (!file) {
        cerr << "Cannot create file" << endl;
        return false;
    }

    Employee* employees = new Employee[employeeCount];

    for (int i = 0; i < employeeCount; i++) {
        cout << "Employee " << i + 1 << ":" << endl;
        cin >> employees[i];
    }

    file.write(reinterpret_cast<char*>(employees), employeeCount * sizeof(Employee));
    file.close();

    delete[] employees;
    return true;
}

void displayEmployeeFile(const string& fileName, int employeeCount) {
    ifstream file(fileName, ios::binary);
    if (!file) {
        cerr << "Cannot open file" << endl;
        return;
    }

    Employee emp;
    for (int i = 0; i < employeeCount; i++) {
        file.read(reinterpret_cast<char*>(&emp), sizeof(Employee));
        cout << "Record " << i + 1 << ":" << endl;
        cout << emp << endl;
    }

    file.close();
}

int inputIntInRange(int min, int max, const string& message) {
    int value;
    cout << message;
    cin >> value;

    while (cin.fail() || value < min || value > max) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Enter value between " << min << " and " << max << ": ";
        cin >> value;
    }

    return value;
}