#include "client.h"
#include <cstring>

bool isPipeConnected(HANDLE hPipe) {
    DWORD bytesAvailable = 0;
    if (!PeekNamedPipe(hPipe, NULL, 0, NULL, &bytesAvailable, NULL)) {
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: Client.exe <pipeName> <employeeCount>" << endl;
        return 1;
    }

    string pipeName = argv[1];
    int employeeCount = atoi(argv[2]);

    HANDLE hPipe = connectToNamedPipe(pipeName);
    if (!hPipe) {
        return 1;
    }

    while (true) {
        if (!isPipeConnected(hPipe)) {
            cout << "Server disconnected. Exiting..." << endl;
            break;
        }

        cout << endl << "1. Modify record" << endl;
        cout << "2. Read record" << endl;
        cout << "3. Exit" << endl;

        int choice = inputIntInRange(
            ClientConstants::MODIFY_CHOICE,
            ClientConstants::EXIT_CHOICE,
            "Enter choice: "
        );

        if (choice == ClientConstants::EXIT_CHOICE) {
            int operation = OperationType::END_OPERATION;
            DWORD bytesWritten;
            if (!WriteFile(hPipe, &operation, sizeof(operation), &bytesWritten, NULL)) {
                cout << "Server disconnected during exit" << endl;
            }
            break;
        }

        int recordIndex = inputIntInRange(
            1,
            employeeCount,
            "Enter record number (1-" + to_string(employeeCount) + "): "
        );

        DWORD bytesWritten, bytesRead;

        if (choice == ClientConstants::READ_CHOICE) {
            int operation = OperationType::READ_OPERATION;
            if (!WriteFile(hPipe, &operation, sizeof(operation), &bytesWritten, NULL)) {
                cout << "Server disconnected" << endl;
                break;
            }

            if (!WriteFile(hPipe, &recordIndex, sizeof(recordIndex), &bytesWritten, NULL)) {
                cout << "Server disconnected" << endl;
                break;
            }

            Employee emp;
            if (!ReadFile(hPipe, &emp, sizeof(emp), &bytesRead, NULL)) {
                cout << "Server disconnected while reading response" << endl;
                break;
            }

            cout << endl << "Record contents:" << endl;
            cout << emp;
        }
        else if (choice == ClientConstants::MODIFY_CHOICE) {
            int operation = OperationType::READ_OPERATION;
            if (!WriteFile(hPipe, &operation, sizeof(operation), &bytesWritten, NULL)) {
                cout << "Server disconnected" << endl;
                break;
            }

            if (!WriteFile(hPipe, &recordIndex, sizeof(recordIndex), &bytesWritten, NULL)) {
                cout << "Server disconnected" << endl;
                break;
            }

            Employee emp;
            if (!ReadFile(hPipe, &emp, sizeof(emp), &bytesRead, NULL)) {
                cout << "Server disconnected while reading current record" << endl;
                break;
            }

            cout << endl << "Current record:" << endl;
            cout << emp;

            cout << endl << "Enter new values (enter - to keep old value):" << endl;

            cout << "ID [" << emp.id << "]: ";
            string input;
            cin >> input;
            if (input != "-") emp.id = stoi(input);

            cout << "Name [" << emp.name << "]: ";
            cin >> input;
            if (input != "-") strcpy_s(emp.name, input.c_str());

            cout << "Hours [" << emp.hours << "]: ";
            cin >> input;
            if (input != "-") emp.hours = stod(input);

            operation = OperationType::WRITE_OPERATION;
            if (!WriteFile(hPipe, &operation, sizeof(operation), &bytesWritten, NULL)) {
                cout << "Server disconnected" << endl;
                break;
            }

            if (!WriteFile(hPipe, &recordIndex, sizeof(recordIndex), &bytesWritten, NULL)) {
                cout << "Server disconnected" << endl;
                break;
            }

            if (!WriteFile(hPipe, &emp, sizeof(emp), &bytesWritten, NULL)) {
                cout << "Server disconnected" << endl;
                break;
            }

            bool success;
            if (!ReadFile(hPipe, &success, sizeof(success), &bytesRead, NULL)) {
                cout << "Server disconnected while waiting for confirmation" << endl;
                break;
            }

            if (success) {
                cout << "Record updated successfully" << endl;
            }
        }
    }

    closeNamedPipe(hPipe);
    cout << "Client finished" << endl;

    return 0;
}