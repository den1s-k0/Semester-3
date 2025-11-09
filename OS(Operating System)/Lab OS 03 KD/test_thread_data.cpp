#include "test_thread_data.h"

TEST(ThreadDataTest, DefaultConstructor) {
    ThreadData data;

    EXPECT_EQ(data.thread_id, -1);
    EXPECT_EQ(data.array, nullptr);
    EXPECT_EQ(data.array_size, 0);
    EXPECT_FALSE(data.is_break);
    EXPECT_EQ(data.start_event, nullptr);
    EXPECT_EQ(data.pause_event, nullptr);
    EXPECT_EQ(data.continue_event, nullptr);
    EXPECT_EQ(data.break_event, nullptr);
    EXPECT_EQ(data.marked_count, 0);
}

TEST(ThreadDataTest, ParameterizedConstructor) {
    int array[10] = { 0 };
    HANDLE start = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    HANDLE pause = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    HANDLE cont = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    HANDLE brk = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    ThreadData data(5, array, 10, start, pause, cont, brk);

    EXPECT_EQ(data.thread_id, 5);
    EXPECT_EQ(data.array, array);
    EXPECT_EQ(data.array_size, 10);
    EXPECT_FALSE(data.is_break);
    EXPECT_EQ(data.start_event, start);
    EXPECT_EQ(data.pause_event, pause);
    EXPECT_EQ(data.continue_event, cont);
    EXPECT_EQ(data.break_event, brk);
    EXPECT_EQ(data.marked_count, 0);

    CloseHandle(start);
    CloseHandle(pause);
    CloseHandle(cont);
    CloseHandle(brk);
}