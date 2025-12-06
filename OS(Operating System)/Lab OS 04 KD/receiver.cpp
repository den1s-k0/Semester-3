#include "receiver.h"

int main() {
    string file_name = cinString(1, 100, "Enter file name: ");

    int queue_capacity = cinInt(RECEIVER_SIZES_CODES::MIN_QUEUE_CAPACITY, RECEIVER_SIZES_CODES::MAX_QUEUE_CAPACITY, "Enter queue capacity: ");

    CircularQueue queue(file_name, queue_capacity);
    if (!queue.initialize()) {
        cerr << "Cannot create file\n";
        return RECEIVER_RETURN_CODES::FILE_ERROR;
    }

    int sender_count = cinInt(RECEIVER_SIZES_CODES::MIN_SENDER_COUNT, RECEIVER_SIZES_CODES::MAX_SENDER_COUNT, "Enter number of sender processes: ");

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
            return RECEIVER_RETURN_CODES::EVENT_ERROR;
        }

        string event_name = file_name + "_rdy_" + to_string(i + 1);
        string command = "Sender.exe \"" + file_name + "\" \"" + event_name + "\" \"" +
            to_string(queue_capacity) + "\"";

        if (!start_sender_process(command, processes[i])) {
            cerr << "Cannot create process " << i + 1 << "\n";
            return RECEIVER_RETURN_CODES::PROCESS_ERROR;
        }
    }

    if (WaitForMultipleObjects(sender_count, ready_events, TRUE, INFINITE) == WAIT_FAILED) {
        cerr << "WaitForMultipleObjects failed\n";
        return RECEIVER_RETURN_CODES::WAIT_ERROR;
    }

    bool running = true;

    while (running) {
        cout << "\n1. Read message\n"
            << "2. Exit\n";

        int choice = cinInt(RECEIVER_CHOICE_CODES::READ_CHOICE, RECEIVER_CHOICE_CODES::EXIT_CHOICE, "Enter choice: ");

        if (choice == RECEIVER_CHOICE_CODES::READ_CHOICE) {
            waitWithMessage(hFull, "Queue is empty. Waiting for messages...");

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
        else if (choice == RECEIVER_CHOICE_CODES::EXIT_CHOICE) {
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
    return RECEIVER_RETURN_CODES::SUCCESS;
}