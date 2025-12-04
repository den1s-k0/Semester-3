#pragma once
#include <string>
#include <fstream>
#include <algorithm>
#include <cstring>
#include "common.h"

using namespace std;

namespace QUEUE_SIZES_CODES {
    const int MAX_MESSAGE_SIZE = 20;

    const int HEADER_SIZE = sizeof(int) * 2;
}

class CircularQueue {
    string file_path;
    int queue_capacity;

public:
    CircularQueue(const string& path, int capacity);

    bool initialize();
    bool read_message(string& result);
    bool write_message(const string& message);

private:
    bool read_raw_message(int index, string& result);
    bool write_raw_message(int index, const string& message);
    bool read_head(int& head);
    int read_tail();
    bool write_head(int head);
    bool write_tail(int tail);
};