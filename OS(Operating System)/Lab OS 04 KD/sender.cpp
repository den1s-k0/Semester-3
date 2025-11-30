#include "sender.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    return sender_main(argc, argv);
}

int sender_main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Usage: Sender.exe <filename> <readyEventName> <queueCapacity>\n";
        return 1;
    }

    string file_name = argv[1];
    string event_name = argv[2];
    int queue_capacity = atoi(argv[3]);

    HANDLE hReadyEvent = OpenEventA(EVENT_MODIFY_STATE, FALSE, event_name.c_str());
    if (!hReadyEvent) {
        cerr << "Failed to open ready event\n";
        return 1;
    }

    HANDLE hMutex, hEmpty, hFull;
    if (!open_sync_objects(file_name, hMutex, hEmpty, hFull)) {
        cerr << "Failed to open synchronization objects\n";
        CloseHandle(hReadyEvent);
        return 1;
    }

    SetEvent(hReadyEvent);

    CircularQueue queue(file_name, queue_capacity);
    bool active = true;

    while (active) {
        cout << "\n1. Send message\n";
        cout << "2. Exit\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;
        cin.ignore(1000, '\n');

        if (choice == 1) {
            WaitForSingleObject(hEmpty, INFINITE);
            WaitForSingleObject(hMutex, INFINITE);

            cout << "Enter message (max " << MAX_MESSAGE_SIZE << " chars): ";
            string message;
            getline(cin, message);

            if (message.size() > MAX_MESSAGE_SIZE) {
                message = message.substr(0, MAX_MESSAGE_SIZE);
            }

            if (queue.write_message(message)) {
                cout << "Message sent\n";
            }
            else {
                cout << "Failed to send message\n";
            }

            ReleaseMutex(hMutex);
            ReleaseSemaphore(hFull, 1, nullptr);

        }
        else if (choice == 2) {
            active = false;
        }
    }

    CloseHandle(hReadyEvent);
    CloseHandle(hMutex);
    CloseHandle(hEmpty);
    CloseHandle(hFull);

    cout << "Sender finished\n";
    return 0;
}