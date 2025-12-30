#include "test_employee.h"

TEST(EmployeeTest, DefaultConstructor) {
    Employee emp;
    EXPECT_EQ(emp.id, 0);
    EXPECT_STREQ(emp.name, "");
    EXPECT_DOUBLE_EQ(emp.hours, 0.0);
}

TEST(EmployeeTest, ParamConstructor) {
    Employee emp(123, "John", 40.5);
    EXPECT_EQ(emp.id, 123);
    EXPECT_STREQ(emp.name, "John");
    EXPECT_DOUBLE_EQ(emp.hours, 40.5);
}

TEST(EmployeeTest, StreamOutput) {
    Employee emp = { 123, "John", 40.5 };

    stringstream ss;
    ss << emp;

    string output = ss.str();
    EXPECT_NE(output.find("ID: 123"), string::npos);
    EXPECT_NE(output.find("Name: John"), string::npos);
    EXPECT_NE(output.find("Hours: 40.5"), string::npos);
}

TEST(EmployeeTest, StreamInput) {
    Employee emp;
    stringstream input("456\nJane\n37.5\n");
    stringstream output;

    auto oldCinBuf = cin.rdbuf();
    cin.rdbuf(input.rdbuf());

    auto oldCoutBuf = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    cin >> emp;

    cin.rdbuf(oldCinBuf);
    cout.rdbuf(oldCoutBuf);

    EXPECT_EQ(emp.id, 456);
    EXPECT_STREQ(emp.name, "Jane");
    EXPECT_DOUBLE_EQ(emp.hours, 37.5);
}

TEST(EmployeeTest, ReadWriteToFile) {
    const string testFileName = "test_employee.dat";
    Employee emp1 = { 1, "Alice", 35.0 };
    Employee emp2;

    fstream file(testFileName, ios::out | ios::binary);
    ASSERT_TRUE(file.is_open());

    file.write(reinterpret_cast<char*>(&emp1), sizeof(Employee));
    file.close();

    file.open(testFileName, ios::in | ios::binary);
    ASSERT_TRUE(file.is_open());

    file.read(reinterpret_cast<char*>(&emp2), sizeof(Employee));
    file.close();

    EXPECT_EQ(emp2.id, emp1.id);
    EXPECT_STREQ(emp2.name, emp1.name);
    EXPECT_DOUBLE_EQ(emp2.hours, emp1.hours);

    remove(testFileName.c_str());
}

TEST(EmployeeTest, ReadEmployeeFromFile) {
    const string testFileName = "test_read.dat";

    Employee employees[2] = {
        {1, "Bob", 40.0},
        {2, "Carol", 30.5}
    };

    ofstream outFile(testFileName, ios::binary);
    outFile.write(reinterpret_cast<char*>(employees), 2 * sizeof(Employee));
    outFile.close();

    fstream file(testFileName, ios::in | ios::binary);
    ASSERT_TRUE(file.is_open());

    Employee emp;
    EXPECT_TRUE(readEmployeeFromFile(file, 0, emp));
    EXPECT_EQ(emp.id, 1);
    EXPECT_STREQ(emp.name, "Bob");

    EXPECT_TRUE(readEmployeeFromFile(file, 1, emp));
    EXPECT_EQ(emp.id, 2);
    EXPECT_STREQ(emp.name, "Carol");

    EXPECT_FALSE(readEmployeeFromFile(file, 2, emp));

    file.close();

    remove(testFileName.c_str());
}

TEST(EmployeeTest, WriteEmployeeToFile) {
    const string testFileName = "test_write.dat";

    Employee employees[2] = {};
    ofstream outFile(testFileName, ios::binary);
    outFile.write(reinterpret_cast<char*>(employees), 2 * sizeof(Employee));
    outFile.close();

    fstream file(testFileName, ios::in | ios::out | ios::binary);
    ASSERT_TRUE(file.is_open());

    Employee emp1 = { 1, "David", 45.0 };
    Employee emp2 = { 2, "Eve", 32.5 };

    EXPECT_TRUE(writeEmployeeToFile(file, 0, emp1));
    EXPECT_TRUE(writeEmployeeToFile(file, 1, emp2));

    file.close();

    ifstream inFile(testFileName, ios::binary);
    Employee readEmps[2];
    inFile.read(reinterpret_cast<char*>(readEmps), 2 * sizeof(Employee));
    inFile.close();

    EXPECT_EQ(readEmps[0].id, 1);
    EXPECT_STREQ(readEmps[0].name, "David");
    EXPECT_DOUBLE_EQ(readEmps[0].hours, 45.0);

    EXPECT_EQ(readEmps[1].id, 2);
    EXPECT_STREQ(readEmps[1].name, "Eve");
    EXPECT_DOUBLE_EQ(readEmps[1].hours, 32.5);

    remove(testFileName.c_str());
}

TEST(EmployeeTest, SizeOfEmployee) {
    Employee emp;
    EXPECT_GE(sizeof(emp), sizeof(int) + 10 * sizeof(char) + sizeof(double));
}