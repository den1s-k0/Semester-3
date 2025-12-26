#include "client.h"

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
            WriteFile(hPipe, &operation, sizeof(operation), &bytesWritten, NULL);
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
            WriteFile(hPipe, &operation, sizeof(operation), &bytesWritten, NULL);
            WriteFile(hPipe, &recordIndex, sizeof(recordIndex), &bytesWritten, NULL);

            Employee emp;
            ReadFile(hPipe, &emp, sizeof(emp), &bytesRead, NULL);

            cout << endl << "Record contents:" << endl;
            cout << emp;
        }
        else if (choice == ClientConstants::MODIFY_CHOICE) {
            int operation = OperationType::READ_OPERATION;
            WriteFile(hPipe, &operation, sizeof(operation), &bytesWritten, NULL);
            WriteFile(hPipe, &recordIndex, sizeof(recordIndex), &bytesWritten, NULL);

            Employee emp;
            ReadFile(hPipe, &emp, sizeof(emp), &bytesRead, NULL);

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
            WriteFile(hPipe, &operation, sizeof(operation), &bytesWritten, NULL);
            WriteFile(hPipe, &recordIndex, sizeof(recordIndex), &bytesWritten, NULL);
            WriteFile(hPipe, &emp, sizeof(emp), &bytesWritten, NULL);

            bool success;
            ReadFile(hPipe, &success, sizeof(success), &bytesRead, NULL);

            if (success) {
                cout << "Record updated successfully" << endl;
            }
        }
    }

    closeNamedPipe(hPipe);
    cout << "Client finished" << endl;

    return 0;
}

int clientMain(int argc, char* argv[]) {
    return main(argc, argv);
}