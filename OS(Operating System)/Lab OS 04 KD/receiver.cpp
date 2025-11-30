#include "receiver.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    return receiver_main();
}

int receiver_main() {
    cout << "Enter file name: ";
    string file_name;
    getline(cin, file_name);

    if (file_name.empty()) {
        cerr << "Empty file name\n";
        return 1;
    }

    cout << "Enter queue capacity: ";
    int queue_capacity;
    cin >> queue_capacity;

    CircularQueue queue(file_name, queue_capacity);
    if (!queue.initialize()) {
        cerr << "Cannot create file\n";
        return 1;
    }

    cin.ignore(1000, '\n');

    cout << "Enter number of sender processes: ";
    int sender_count;
    cin >> sender_count;

    HANDLE hMutex, hEmpty, hFull;
    if (!create_sync_objects(file_name, queue_capacity, hMutex, hEmpty, hFull)) {
        return 1;
    }

    HANDLE* ready_events = new HANDLE[sender_count];
    PROCESS_INFORMATION* processes = new PROCESS_INFORMATION[sender_count];

    for (int i = 0; i < sender_count; i++) {
        ready_events[i] = create_ready_event(file_name, i);
        if (!ready_events[i]) {
            cerr << "CreateEvent failed\n";
            return 1;
        }

        string event_name = file_name + "_rdy_" + to_string(i + 1);
        string command = "Sender.exe \"" + file_name + "\" \"" + event_name + "\" \"" +
            to_string(queue_capacity) + "\"";

        if (!start_sender_process(command, processes[i])) {
            cerr << "Cannot create process " << i + 1 << "\n";
            return 1;
        }
    }

    if (WaitForMultipleObjects(sender_count, ready_events, TRUE, INFINITE) == WAIT_FAILED) {
        cerr << "WaitForMultipleObjects failed\n";
        return 1;
    }

    bool running = true;
    while (running) {
        cout << "\n1. Read message\n";
        cout << "2. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            WaitForSingleObject(hFull, INFINITE);
            WaitForSingleObject(hMutex, INFINITE);

            string message;
            if (queue.read_message(message)) {
                cout << "Message: " << message << endl;
            }
            else {
                cout << "Failed to read message\n";
            }

            ReleaseMutex(hMutex);
            ReleaseSemaphore(hEmpty, 1, nullptr);
        }
        else if (choice == 2) {
            running = false;
        }
    }

    for (int i = 0; i < sender_count; i++) {
        WaitForSingleObject(processes[i].hProcess, 1000);
        CloseHandle(processes[i].hProcess);
        CloseHandle(processes[i].hThread);
        CloseHandle(ready_events[i]);
    }

    delete[] ready_events;
    delete[] processes;

    CloseHandle(hMutex);
    CloseHandle(hEmpty);
    CloseHandle(hFull);

    cout << "Receiver finished\n";
    return 0;
}