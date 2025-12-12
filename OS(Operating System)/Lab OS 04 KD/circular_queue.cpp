#include "circular_queue.h"

CircularQueue::CircularQueue(const string& path, int capacity)
    : file_path(path), queue_capacity(capacity) {
}

bool CircularQueue::initialize() {
    int head = 0;
    int tail = 0;
    int count = 0;

    ofstream file(file_path, ios::binary);
    if (!file) return false;

    int total_size = queue_capacity * QUEUE_SIZES_CODES::MAX_MESSAGE_SIZE;
    file.seekp(total_size + QUEUE_SIZES_CODES::HEADER_SIZE - 1);
    char zero = '\0';
    file.write(&zero, 1);

    file.seekp(0);
    file.write(reinterpret_cast<char*>(&head), sizeof(head));
    file.write(reinterpret_cast<char*>(&tail), sizeof(tail));
    file.write(reinterpret_cast<char*>(&count), sizeof(count));
    file.close();

    return true;
}

bool CircularQueue::read_message(string& result) {
    int head, count;

    if (!read_head(head) || !read_count(count)) {
        return false;
    }

    if (count <= 0) {
        return false;
    }

    if (!read_raw_message(head, result)) {
        return false;
    }

    head = (head + 1) % queue_capacity;
    count--;

    return write_head(head) && write_count(count);
}

bool CircularQueue::write_message(const string& message) {
    int tail, count;

    if (!read_tail(tail) || !read_count(count)) {
        return false;
    }

    if (count >= queue_capacity) {
        return false;
    }

    if (!write_raw_message(tail, message)) {
        return false;
    }

    tail = (tail + 1) % queue_capacity;
    count++;

    return write_tail(tail) && write_count(count);
}

bool CircularQueue::is_empty() {
    int count;
    return read_count(count) && (count == 0);
}

bool CircularQueue::is_full() {
    int count;
    return read_count(count) && (count >= queue_capacity);
}

int CircularQueue::get_count() {
    int count;
    return read_count(count) ? count : -1;
}

bool CircularQueue::read_raw_message(int index, string& result) {
    char buffer[QUEUE_SIZES_CODES::MAX_MESSAGE_SIZE + 1] = { 0 };
    fstream file(file_path, ios::in | ios::binary);

    if (!file) return false;

    file.seekg(QUEUE_SIZES_CODES::HEADER_SIZE + index * QUEUE_SIZES_CODES::MAX_MESSAGE_SIZE, ios::beg);
    file.read(buffer, QUEUE_SIZES_CODES::MAX_MESSAGE_SIZE);
    file.close();

    buffer[QUEUE_SIZES_CODES::MAX_MESSAGE_SIZE] = '\0';
    result = buffer;

    size_t null_pos = result.find('\0');
    if (null_pos != string::npos) {
        result.erase(null_pos);
    }

    return true;
}

bool CircularQueue::write_raw_message(int index, const string& message) {
    char buffer[QUEUE_SIZES_CODES::MAX_MESSAGE_SIZE] = { 0 };
    fstream file(file_path, ios::in | ios::out | ios::binary);

    if (!file) return false;

    size_t copy_size = min(message.size(), static_cast<size_t>(QUEUE_SIZES_CODES::MAX_MESSAGE_SIZE));
    memcpy(buffer, message.c_str(), copy_size);

    file.seekp(QUEUE_SIZES_CODES::HEADER_SIZE + index * QUEUE_SIZES_CODES::MAX_MESSAGE_SIZE, ios::beg);
    file.write(buffer, QUEUE_SIZES_CODES::MAX_MESSAGE_SIZE);
    file.close();

    return true;
}

bool CircularQueue::read_head(int& head) {
    fstream file(file_path, ios::in | ios::binary);
    if (!file) return false;
    file.seekg(0, ios::beg);
    bool success = static_cast<bool>(file.read(reinterpret_cast<char*>(&head), sizeof(head)));
    file.close();
    return success;
}

bool CircularQueue::read_tail(int& tail) {
    fstream file(file_path, ios::in | ios::binary);
    if (!file) return false;
    file.seekg(sizeof(int), ios::beg);
    bool success = static_cast<bool>(file.read(reinterpret_cast<char*>(&tail), sizeof(tail)));
    file.close();
    return success;
}

bool CircularQueue::read_count(int& count) {
    fstream file(file_path, ios::in | ios::binary);
    if (!file) return false;
    file.seekg(sizeof(int) * 2, ios::beg);
    bool success = static_cast<bool>(file.read(reinterpret_cast<char*>(&count), sizeof(count)));
    file.close();
    return success;
}

bool CircularQueue::write_head(int head) {
    fstream file(file_path, ios::in | ios::out | ios::binary);
    if (!file) return false;
    file.seekp(0, ios::beg);
    bool success = static_cast<bool>(file.write(reinterpret_cast<char*>(&head), sizeof(head)));
    file.close();
    return success;
}

bool CircularQueue::write_tail(int tail) {
    fstream file(file_path, ios::in | ios::out | ios::binary);
    if (!file) return false;
    file.seekp(sizeof(int), ios::beg);
    bool success = static_cast<bool>(file.write(reinterpret_cast<char*>(&tail), sizeof(tail)));
    file.close();
    return success;
}

bool CircularQueue::write_count(int count) {
    fstream file(file_path, ios::in | ios::out | ios::binary);
    if (!file) return false;
    file.seekp(sizeof(int) * 2, ios::beg);
    bool success = static_cast<bool>(file.write(reinterpret_cast<char*>(&count), sizeof(count)));
    file.close();
    return success;
}