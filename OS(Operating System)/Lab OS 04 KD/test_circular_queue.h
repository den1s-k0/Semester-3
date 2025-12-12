#pragma once

#include <gtest/gtest.h>
#include <cstdio>
#include "circular_queue.h"

using namespace std;

class CircularQueueTest : public ::testing::Test {
protected:
    void TearDown() override {
        const char* files[] = {
            "test1.bin", "test2.bin", "test3.bin",
            "test4.bin", "test5.bin", "test6.bin",
            "test7.bin"
        };

        for (const char* filename : files) {
            remove(filename);
        }
    }
};