#include "test_marker.h"

TEST(MarkerTest, MarkerCodes_Values) {
    EXPECT_EQ(MARKER_CODES::SUCCES, 0);
    EXPECT_EQ(MARKER_CODES::WAIT_FAIL, -1);
    EXPECT_EQ(MARKER_CODES::TIME_TO_SLEEP, 5);
}

TEST(MarkerTest, ThreadData_Initialization) {
    int array[5] = { 0 };
    HANDLE start = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    HANDLE pause = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    HANDLE cont = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    HANDLE brk = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    ThreadData data(1, array, 5, start, pause, cont, brk);

    EXPECT_EQ(data.thread_id, 1);
    EXPECT_EQ(data.array, array);
    EXPECT_EQ(data.array_size, 5);
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