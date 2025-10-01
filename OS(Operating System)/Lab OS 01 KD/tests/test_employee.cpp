#include "test_header.h"

// Набор тестовых данных
INSTANTIATE_TEST_SUITE_P(
    VariousEmployeeInputs,
    EmployeeConstructorTest,
    ::testing::Values(
        make_tuple(1, "Denis", 10.5),
        make_tuple(2, "Anna", 0.0),
        make_tuple(3, "Max", 99.9),
        make_tuple(4, "", 5.0),
        make_tuple(5, "LongName", 12.3)
    )
);

TEST_P(EmployeeConstructorTest, InitializesCorrectly) {
    int expected_num = get<0>(GetParam());
    const char* expected_name = get<1>(GetParam());
    double expected_hours = get<2>(GetParam());

    employee e(expected_num, expected_name, expected_hours);

    EXPECT_EQ(e.num, expected_num);
    EXPECT_EQ(e.hours, expected_hours);
    EXPECT_STREQ(e.name, expected_name);
}

TEST(EmployeeTest, InitializesLongNameCorrectly) {
    employee e(1, "TooLongNameForMyFile", 5);
    EXPECT_EQ(e.num, 1);
    EXPECT_EQ(e.hours, 5);
    EXPECT_STREQ(e.name, "TooLongN*");
}

TEST(EmployeeTest, InitializesMaxNameCorrectly) {
    employee e(-1, "LongName9", -5);
    EXPECT_EQ(e.num, -1);
    EXPECT_EQ(e.hours, -5);
    EXPECT_STREQ(e.name, "LongName9");
}

TEST(EmployeeTest, DefaultConstructor) {
    employee e;
    EXPECT_EQ(e.num, 0);
    EXPECT_EQ(e.hours, 0.0);
    EXPECT_STREQ(e.name, "");
}