#include "test_file_manager.h"

TEST(FileManagerTest, InputIntInRange_ValidInput) {
    stringstream input("5\n");
    stringstream output;

    auto oldCinBuf = cin.rdbuf();
    cin.rdbuf(input.rdbuf());

    auto oldCoutBuf = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    int result = inputIntInRange(1, 10, "Enter number: ");

    cin.rdbuf(oldCinBuf);
    cout.rdbuf(oldCoutBuf);

    EXPECT_EQ(result, 5);
}

TEST(FileManagerTest, InputIntInRange_OutOfRangeRetry) {
    stringstream input("15\n5\n");
    stringstream output;

    auto oldCinBuf = cin.rdbuf();
    cin.rdbuf(input.rdbuf());

    auto oldCoutBuf = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    int result = inputIntInRange(1, 10, "Enter number: ");

    cin.rdbuf(oldCinBuf);
    cout.rdbuf(oldCoutBuf);

    EXPECT_EQ(result, 5);
    EXPECT_NE(output.str().find("Invalid input"), string::npos);
}

TEST(FileManagerTest, InputIntInRange_NonNumericRetry) {
    stringstream input("abc\n5\n");
    stringstream output;

    auto oldCinBuf = cin.rdbuf();
    cin.rdbuf(input.rdbuf());

    auto oldCoutBuf = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    int result = inputIntInRange(1, 10, "Enter number: ");

    cin.rdbuf(oldCinBuf);
    cout.rdbuf(oldCoutBuf);

    EXPECT_EQ(result, 5);
    EXPECT_NE(output.str().find("Invalid input"), string::npos);
}

TEST(FileManagerTest, CreateEmployeeFile_Success) {
    const string testFileName = "test_create.dat";
    stringstream input("1\nTest\n40.5\n");

    auto oldCinBuf = cin.rdbuf();
    cin.rdbuf(input.rdbuf());

    bool result = createEmployeeFile(testFileName, 1);

    cin.rdbuf(oldCinBuf);

    EXPECT_TRUE(result);

    ifstream file(testFileName, ios::binary);
    EXPECT_TRUE(file.is_open());
    file.close();

    remove(testFileName.c_str());
}

TEST(FileManagerTest, CreateEmployeeFile_MultipleEmployees) {
    const string testFileName = "test_multiple.dat";
    stringstream input("1\nAlice\n35.0\n2\nBob\n40.0\n");

    auto oldCinBuf = cin.rdbuf();
    cin.rdbuf(input.rdbuf());

    bool result = createEmployeeFile(testFileName, 2);

    cin.rdbuf(oldCinBuf);

    EXPECT_TRUE(result);

    ifstream file(testFileName, ios::binary);
    EXPECT_TRUE(file.is_open());

    Employee employees[2];
    file.read(reinterpret_cast<char*>(employees), 2 * sizeof(Employee));
    file.close();

    EXPECT_EQ(employees[0].id, 1);
    EXPECT_STREQ(employees[0].name, "Alice");
    EXPECT_DOUBLE_EQ(employees[0].hours, 35.0);

    EXPECT_EQ(employees[1].id, 2);
    EXPECT_STREQ(employees[1].name, "Bob");
    EXPECT_DOUBLE_EQ(employees[1].hours, 40.0);

    remove(testFileName.c_str());
}

TEST(FileManagerTest, DisplayEmployeeFile_Success) {
    const string testFileName = "test_display.dat";
    stringstream output;

    Employee employees[2] = {
        {1, "Charlie", 42.5},
        {2, "Diana", 38.0}
    };

    ofstream outFile(testFileName, ios::binary);
    outFile.write(reinterpret_cast<char*>(employees), 2 * sizeof(Employee));
    outFile.close();

    auto oldCoutBuf = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    displayEmployeeFile(testFileName, 2);

    cout.rdbuf(oldCoutBuf);

    string result = output.str();
    EXPECT_NE(result.find("Record 1:"), string::npos);
    EXPECT_NE(result.find("ID: 1"), string::npos);
    EXPECT_NE(result.find("Name: Charlie"), string::npos);
    EXPECT_NE(result.find("Record 2:"), string::npos);
    EXPECT_NE(result.find("ID: 2"), string::npos);
    EXPECT_NE(result.find("Name: Diana"), string::npos);

    remove(testFileName.c_str());
}

TEST(FileManagerTest, DisplayEmployeeFile_NonExistent) {
    stringstream output;
    stringstream errorOutput;

    auto oldCoutBuf = cout.rdbuf();
    auto oldCerrBuf = cerr.rdbuf();
    cout.rdbuf(output.rdbuf());
    cerr.rdbuf(errorOutput.rdbuf());

    displayEmployeeFile("nonexistent.dat", 1);

    cout.rdbuf(oldCoutBuf);
    cerr.rdbuf(oldCerrBuf);

    EXPECT_NE(errorOutput.str().find("Cannot open file"), string::npos);
}