#include "test_function.h"

void WriteTxtFile(string TextFileName, employee testemp) {
    ofstream out(TextFileName);
    if (out.is_open()) {
        out << testemp;
    }
    out.close();
}

INSTANTIATE_TEST_SUITE_P(
    VariousBinInputs,
    FunctionBinContolTest,
    ::testing::Values(
        make_tuple(1, "Denis", 10.5),
        make_tuple(2, "Anna", 0.0),
        make_tuple(3, "Max", 99.9),
        make_tuple(4, "-", 5.0),
        make_tuple(5, "LongName", 12.3)
    )
);

TEST_P(FunctionBinContolTest, ReadBinFileTest_CorrectFile) {
    int expected_num = get<0>(GetParam());
    const char* expected_name = get<1>(GetParam());
    double expected_hours = get<2>(GetParam());

    const string BinFileName = "testBinFile.bin";
    WriteBinFile(BinFileName, employee(expected_num, expected_name, expected_hours));

    testing::internal::CaptureStdout();
    ReadBinFile(BinFileName);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("ID: " + to_string(expected_num)) != string::npos);
    EXPECT_TRUE(output.find("\t Name: " + string(expected_name)) != string::npos);
    ostringstream oss;
    oss << fixed << setprecision(2) << expected_hours;
    EXPECT_TRUE(output.find("\t Number of hours: " + oss.str()) != string::npos);

    filesystem::remove(BinFileName);
}


TEST(FunctionBinTest, ReadBinFileTest_NotExistingFile) {
    const string BinFileName = "non_existing_testBinFile.bin";

    testing::internal::CaptureStderr();
    ReadBinFile(BinFileName);
    string output = testing::internal::GetCapturedStderr();

    EXPECT_TRUE(output.find("Error\nBinFile isn't open") != string::npos);
}


TEST(FunctionBinTest, ReadBinFileTest_EmptyFile) {
    const string BinFileName = "empty_testBinFile.bin";

    ofstream out(BinFileName, ios::binary);
    out.close();

    testing::internal::CaptureStdout();
    ReadBinFile(BinFileName);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("ID:") == string::npos);

    filesystem::remove(BinFileName);
}

INSTANTIATE_TEST_SUITE_P(
    VariousTxtInputs,
    FunctionTxtControlTest,
    ::testing::Values(
        make_tuple(1, "Denis", 10.5),
        make_tuple(2, "Anna", 0.0),
        make_tuple(3, "Max", 99.9),
        make_tuple(4, "-", 5.0),
        make_tuple(5, "LongName", 12.3)
    )
);

TEST_P(FunctionTxtControlTest, ReadTextFileTest_CorrectFile) {
    int expected_num = get<0>(GetParam());
    const char* expected_name = get<1>(GetParam());
    double expected_hours = get<2>(GetParam());

    const string TxtFileName = "testTxtFile.txt";
    WriteTxtFile(TxtFileName, employee(expected_num, expected_name, expected_hours));

    testing::internal::CaptureStdout();
    ReadTxtFile(TxtFileName);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("ID: " + to_string(expected_num)) != string::npos);
    EXPECT_TRUE(output.find("\t Name: " + string(expected_name)) != string::npos);
    ostringstream oss;
    oss << fixed << setprecision(2) << expected_hours;
    EXPECT_TRUE(output.find("\t Number of hours: " + oss.str()) != string::npos);

    filesystem::remove(TxtFileName);
}


TEST(FunctionTxtTest, ReadTxtFileTest_NotExistingFile) {
    const string TxtFileName = "non_existing_testTxtFile.txt";

    testing::internal::CaptureStderr();
    ReadTxtFile(TxtFileName);
    string output = testing::internal::GetCapturedStderr();

    EXPECT_TRUE(output.find("Error\nTextFile isn't open") != string::npos);
}


TEST(FunctionTxtTest, ReadTxtFileTest_EmptyFile) {
    const string TxtFileName = "empty_testTxtFile.txt";

    ofstream out(TxtFileName);
    out.close();

    testing::internal::CaptureStdout();
    ReadTxtFile(TxtFileName);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("ID:") == string::npos);

    filesystem::remove(TxtFileName);
}