#include "sender.h"


using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Usage: Sender.exe <filename> <readyEventName> <queueCapacity>\n";
        return SENDER_RETURN_CODES::ARGC_ERROR;
    }

    string file_name = argv[1];
    string event_name = argv[2];
    int queue_capacity = atoi(argv[3]);

    HANDLE hReadyEvent = OpenEventA(EVENT_MODIFY_STATE, FALSE, event_name.c_str());
    if (!hReadyEvent) {
        cerr << "Failed to open ready event\n";
        return SENDER_RETURN_CODES::EVENT_ERROR;
    }

    HANDLE hMutex, hEmpty, hFull;
    if (!open_sync_objects(file_name, hMutex, hEmpty, hFull)) {
        cerr << "Failed to open synchronization objects\n";
        CloseHandle(hReadyEvent);
        return SENDER_RETURN_CODES::SYNC_OBJECT_ERROR;
    }

    SetEvent(hReadyEvent);

    CircularQueue queue(file_name, queue_capacity);
    bool active = true;

    while (active) {
        cout << "\n1. Send message\n"
             << "2. Exit\n";
        int choice = cinInt(SENDER_CHOICE_CODES::SEND_CHOICE, SENDER_CHOICE_CODES::EXIT_CHOICE, "Enter choice: ");

        if (choice == SENDER_CHOICE_CODES::SEND_CHOICE) {
            WaitForSingleObject(hEmpty, INFINITE);
            WaitForSingleObject(hMutex, INFINITE);

            string message = cinString(SENDER_SIZES_CODES::MIN_STRING_SIZE, SENDER_SIZES_CODES::MAX_MESSAGE_SIZE,
                "Enter message (max " + to_string(SENDER_SIZES_CODES::MAX_MESSAGE_SIZE) + " chars): ");

            if (queue.write_message(message)) {
                cout << "Message sent\n";
            }
            else {
                cout << "Failed to send message\n";
            }

            ReleaseMutex(hMutex);
            ReleaseSemaphore(hFull, 1, nullptr);

        }
        else if (choice == SENDER_CHOICE_CODES::EXIT_CHOICE) {
            active = false;
        }
    }

    CloseHandle(hReadyEvent);
    CloseHandle(hMutex);
    CloseHandle(hEmpty);
    CloseHandle(hFull);

    cout << "Sender finished\n";
    return SENDER_RETURN_CODES::SUCCESS;
}