#include "test_circular_queue.h"

TEST_F(CircularQueueTest, Constructor_InitializesCorrectly) {
    const char* filename = "test1.bin";
    CircularQueue queue(filename, 10);

    EXPECT_TRUE(queue.initialize());

    remove(filename);
}

TEST_F(CircularQueueTest, WriteAndRead_SingleMessage) {
    const char* filename = "test2.bin";
    CircularQueue queue(filename, 5);
    ASSERT_TRUE(queue.initialize());

    EXPECT_TRUE(queue.write_message("Hello"));

    string result;
    EXPECT_TRUE(queue.read_message(result));
    EXPECT_EQ("Hello", result);

    remove(filename);
}

TEST_F(CircularQueueTest, IsEmpty_InitialState) {
    const char* filename = "test3.bin";
    CircularQueue queue(filename, 5);
    ASSERT_TRUE(queue.initialize());

    EXPECT_TRUE(queue.is_empty());

    remove(filename);
}

TEST_F(CircularQueueTest, IsEmpty_AfterWriteAndRead) {
    const char* filename = "test4.bin";
    CircularQueue queue(filename, 3);
    ASSERT_TRUE(queue.initialize());

    EXPECT_TRUE(queue.write_message("Test"));

    string msg;
    EXPECT_TRUE(queue.read_message(msg));

    EXPECT_TRUE(queue.is_empty());

    remove(filename);
}

TEST_F(CircularQueueTest, ReadFromEmptyQueue_Fails) {
    const char* filename = "test5.bin";
    CircularQueue queue(filename, 3);
    ASSERT_TRUE(queue.initialize());

    string msg;
    EXPECT_FALSE(queue.read_message(msg));

    remove(filename);
}

TEST_F(CircularQueueTest, WriteToFullQueue_Fails) {
    const char* filename = "test6.bin";
    CircularQueue queue(filename, 2);
    ASSERT_TRUE(queue.initialize());

    EXPECT_TRUE(queue.write_message("Msg1"));
    EXPECT_TRUE(queue.write_message("Msg2"));

    EXPECT_FALSE(queue.write_message("Msg3"));

    remove(filename);
}

TEST_F(CircularQueueTest, CircularBehavior) {
    const char* filename = "test7.bin";
    CircularQueue queue(filename, 3);
    ASSERT_TRUE(queue.initialize());

    EXPECT_TRUE(queue.write_message("A"));
    EXPECT_TRUE(queue.write_message("B"));
    EXPECT_TRUE(queue.write_message("C"));

    string msg;
    EXPECT_TRUE(queue.read_message(msg));
    EXPECT_EQ("A", msg);

    EXPECT_TRUE(queue.write_message("D"));

    EXPECT_TRUE(queue.read_message(msg));
    EXPECT_EQ("B", msg);

    EXPECT_TRUE(queue.read_message(msg));
    EXPECT_EQ("C", msg);

    EXPECT_TRUE(queue.read_message(msg));
    EXPECT_EQ("D", msg);

    remove(filename);
}