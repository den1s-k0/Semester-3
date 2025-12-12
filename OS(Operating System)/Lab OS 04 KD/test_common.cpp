#include "test_common.h"

TEST(CommonFunctionsTest, CinString_ValidInput) {
    stringstream input("Hello\n");
    stringstream output;

    streambuf* orig_cin = cin.rdbuf();
    streambuf* orig_cout = cout.rdbuf();

    cin.rdbuf(input.rdbuf());
    cout.rdbuf(output.rdbuf());

    string result = cinString(1, 10, "Enter text: ");

    cin.rdbuf(orig_cin);
    cout.rdbuf(orig_cout);

    EXPECT_EQ("Hello", result);
}

TEST(CommonFunctionsTest, CinString_InputTooShort) {
    stringstream input("\nWorld\n");
    stringstream output;

    streambuf* orig_cin = cin.rdbuf();
    streambuf* orig_cout = cout.rdbuf();

    cin.rdbuf(input.rdbuf());
    cout.rdbuf(output.rdbuf());

    string result = cinString(2, 10, "Enter text: ");

    cin.rdbuf(orig_cin);
    cout.rdbuf(orig_cout);

    EXPECT_EQ("World", result);
}

TEST(CommonFunctionsTest, CinString_InputTooLong) {
    stringstream input("ThisIsAVeryLongStringThatWillBeTruncated\n");
    stringstream output;

    streambuf* orig_cin = cin.rdbuf();
    streambuf* orig_cout = cout.rdbuf();

    cin.rdbuf(input.rdbuf());
    cout.rdbuf(output.rdbuf());

    string result = cinString(1, 10, "Enter text: ");

    cin.rdbuf(orig_cin);
    cout.rdbuf(orig_cout);

    EXPECT_EQ(10, result.length());
    EXPECT_EQ("ThisIsAVer", result.substr(0, 10));
}

TEST(CommonFunctionsTest, CinInt_ValidInput) {
    stringstream input("5\n");
    stringstream output;

    streambuf* orig_cin = cin.rdbuf();
    streambuf* orig_cout = cout.rdbuf();

    cin.rdbuf(input.rdbuf());
    cout.rdbuf(output.rdbuf());

    int result = cinInt(1, 10, "Enter number: ");

    cin.rdbuf(orig_cin);
    cout.rdbuf(orig_cout);

    EXPECT_EQ(5, result);
}

TEST(CommonFunctionsTest, CinInt_InputOutOfRange) {
    stringstream input("15\n5\n");
    stringstream output;

    streambuf* orig_cin = cin.rdbuf();
    streambuf* orig_cout = cout.rdbuf();

    cin.rdbuf(input.rdbuf());
    cout.rdbuf(output.rdbuf());

    int result = cinInt(1, 10, "Enter number: ");

    cin.rdbuf(orig_cin);
    cout.rdbuf(orig_cout);

    EXPECT_EQ(5, result);
}

TEST(CommonFunctionsTest, CinInt_NonNumericInput) {
    stringstream input("abc\n5\n");
    stringstream output;

    streambuf* orig_cin = cin.rdbuf();
    streambuf* orig_cout = cout.rdbuf();

    cin.rdbuf(input.rdbuf());
    cout.rdbuf(output.rdbuf());

    int result = cinInt(1, 10, "Enter number: ");

    cin.rdbuf(orig_cin);
    cout.rdbuf(orig_cout);

    EXPECT_EQ(5, result);
}

TEST(CommonFunctionsTest, WaitWithMessage_ImmediateSuccess) {
    HANDLE testEvent = CreateEvent(nullptr, FALSE, TRUE, nullptr);
    ASSERT_TRUE(testEvent != nullptr);

    stringstream output;
    streambuf* orig_cout = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    bool result = waitWithMessage(testEvent, "Waiting...");

    cout.rdbuf(orig_cout);
    CloseHandle(testEvent);

    EXPECT_TRUE(result);
    EXPECT_EQ("", output.str());
}

TEST(CommonFunctionsTest, WaitWithMessage_TimeoutAndSuccess) {
    HANDLE testEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    ASSERT_TRUE(testEvent != nullptr);

    stringstream output;
    streambuf* orig_cout = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    thread signalThread([testEvent]() {
        this_thread::sleep_for(chrono::milliseconds(150));
        SetEvent(testEvent);
        });

    bool result = waitWithMessage(testEvent, "Waiting for event...");

    signalThread.join();

    cout.rdbuf(orig_cout);
    CloseHandle(testEvent);

    EXPECT_TRUE(result);
    EXPECT_NE(string::npos, output.str().find("Waiting for event..."));
}