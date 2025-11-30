#include "circular_queue.h"
#include <algorithm>
#include <cstring>

CircularQueue::CircularQueue(const string& path, int capacity)
    : file_path(path), queue_capacity(capacity) {
}

bool CircularQueue::initialize() {
    int head = 0;
    int tail = 0;

    ofstream file(file_path, ios::binary);
    if (!file) return false;

    int total_size = queue_capacity * MAX_MESSAGE_SIZE;
    file.seekp(total_size + HEADER_SIZE - 1);
    char zero = '\0';
    file.write(&zero, 1);

    file.seekp(0);
    file.write(reinterpret_cast<char*>(&head), sizeof(head));
    file.write(reinterpret_cast<char*>(&tail), sizeof(tail));
    file.close();

    return true;
}

bool CircularQueue::read_message(string& result) {
    int head;
    if (!read_head(head)) return false;

    if (!read_raw_message(head, result)) return false;

    head = (head + 1) % queue_capacity;
    return write_head(head);
}

bool CircularQueue::write_message(const string& message) {
    int tail = read_tail();
    if (!write_raw_message(tail, message)) return false;

    tail = (tail + 1) % queue_capacity;
    return write_tail(tail);
}

bool CircularQueue::read_raw_message(int index, string& result) {
    char buffer[MAX_MESSAGE_SIZE + 1] = { 0 };
    fstream file(file_path, ios::in | ios::out | ios::binary);

    if (!file) return false;

    file.seekg(HEADER_SIZE + index * MAX_MESSAGE_SIZE, ios::beg);
    file.read(buffer, MAX_MESSAGE_SIZE);
    file.close();

    buffer[MAX_MESSAGE_SIZE] = '\0';
    result = buffer;

    size_t null_pos = result.find('\0');
    if (null_pos != string::npos) {
        result.erase(null_pos);
    }

    return true;
}

bool CircularQueue::write_raw_message(int index, const string& message) {
    char buffer[MAX_MESSAGE_SIZE] = { 0 };
    fstream file(file_path, ios::in | ios::out | ios::binary);

    if (!file) return false;

    size_t copy_size = min(message.size(), static_cast<size_t>(MAX_MESSAGE_SIZE));
    memcpy(buffer, message.c_str(), copy_size);

    file.seekp(HEADER_SIZE + index * MAX_MESSAGE_SIZE, ios::beg);
    file.write(buffer, MAX_MESSAGE_SIZE);
    file.close();

    return true;
}

bool CircularQueue::read_head(int& head) {
    fstream file(file_path, ios::in | ios::out | ios::binary);

    if (!file) return false;

    file.seekg(0, ios::beg);
    file.read(reinterpret_cast<char*>(&head), sizeof(head));
    file.close();

    return true;
}

int CircularQueue::read_tail() {
    int tail;
    fstream file(file_path, ios::in | ios::out | ios::binary);

    file.seekg(sizeof(int), ios::beg);
    file.read(reinterpret_cast<char*>(&tail), sizeof(tail));
    file.close();

    return tail;
}

bool CircularQueue::write_head(int head) {
    fstream file(file_path, ios::in | ios::out | ios::binary);

    if (!file) return false;

    file.seekp(0, ios::beg);
    file.write(reinterpret_cast<char*>(&head), sizeof(head));
    file.close();

    return true;
}

bool CircularQueue::write_tail(int tail) {
    fstream file(file_path, ios::in | ios::out | ios::binary);

    if (!file) return false;

    file.seekp(sizeof(int), ios::beg);
    file.write(reinterpret_cast<char*>(&tail), sizeof(tail));
    file.close();

    return true;
}