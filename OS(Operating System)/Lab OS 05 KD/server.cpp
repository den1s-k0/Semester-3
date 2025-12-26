#include "server.h"

int main() {
    cout << "Enter file name: ";
    string fileName;
    getline(cin, fileName);

    int employeeCount = inputIntInRange(
        ServerConstants::MIN_EMPLOYEES,
        ServerConstants::MAX_EMPLOYEES,
        "Enter number of employees: "
    );

    if (!createEmployeeFile(fileName, employeeCount)) {
        return 1;
    }

    cout << "File contents:" << endl;
    displayEmployeeFile(fileName, employeeCount);

    int clientCount = inputIntInRange(
        ServerConstants::MIN_CLIENTS,
        ServerConstants::MAX_CLIENTS,
        "Enter number of client processes: "
    );

    RecordLock* locks = new RecordLock[employeeCount];
    initLocks(locks, employeeCount);

    for (int i = 0; i < clientCount; i++) {
        string pipeName = "\\\\.\\pipe\\EmployeePipe" + to_string(i);
        if (!startClientThread(pipeName, employeeCount, locks, fileName)) {
            cerr << "Failed to start client " << i + 1 << endl;
        }
    }

    cout << "Press Enter to stop server...\n";
    cin.ignore();
    cin.get();

    cleanupLocks(locks, employeeCount);
    delete[] locks;

    cout << "Final file contents:" << endl;
    displayEmployeeFile(fileName, employeeCount);

    return 0;
}