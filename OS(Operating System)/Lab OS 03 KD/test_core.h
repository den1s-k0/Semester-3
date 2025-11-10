#pragma once

#include <gtest/gtest.h>
#include <windows.h>
#include "core.h"

using namespace std;

class CoreTest : public ::testing::Test {
protected:
    void SetUp() override {
        InitializeCriticalSection(&console_cs);
        InitializeCriticalSection(&array_cs);
    }

    void TearDown() override {
        DeleteCriticalSection(&console_cs);
        DeleteCriticalSection(&array_cs);
    }
};