#include "test_core.h"

TEST_F(CoreTest, PrintArray_EmptyArray) {
    int arr[5] = { 0, 0, 0, 0, 0 };
    EXPECT_NO_THROW(printArray(arr, 5));
}

TEST_F(CoreTest, WaitAllPausedEvents_Simple) {
    ThreadData threads[2];
    HANDLE events[2];

    for (int i = 0; i < 2; i++) {
        events[i] = CreateEvent(nullptr, FALSE, TRUE, nullptr);
        threads[i].pause_event = events[i];
        threads[i].is_break = false;
    }

    WaitAllPausedEvents(threads, 2, 2);

    for (int i = 0; i < 2; i++) {
        CloseHandle(events[i]);
    }
}

TEST_F(CoreTest, continueThreads_Simple) {
    ThreadData threads[2];
    HANDLE threadHandles[2] = { nullptr, nullptr };
    HANDLE events[2];

    for (int i = 0; i < 2; i++) {
        events[i] = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        threads[i].continue_event = events[i];
        threads[i].is_break = false;
    }

    continueThreads(threads, threadHandles, 2);

    for (int i = 0; i < 2; i++) {
        DWORD result = WaitForSingleObject(events[i], 0);
        EXPECT_EQ(result, WAIT_OBJECT_0);
        CloseHandle(events[i]);
    }
}

TEST_F(CoreTest, breakThread_WithNullHandle) {
    ThreadData threadData;
    threadData.is_break = false;

    threadData.pause_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    threadData.continue_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    threadData.break_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    HANDLE hThread = nullptr;
    int active_threads = 1;

    breakThread(&threadData, &hThread, active_threads, 0);

    EXPECT_EQ(active_threads, 0);
    EXPECT_TRUE(threadData.is_break);

    CloseHandle(threadData.pause_event);
    CloseHandle(threadData.continue_event);
    CloseHandle(threadData.break_event);
}

TEST_F(CoreTest, ArrayOperations) {
    const int SIZE = 10;
    int* array = new int[SIZE]();

    EXPECT_NE(array, nullptr);

    EXPECT_NO_THROW(printArray(array, SIZE));

    delete[] array;
}