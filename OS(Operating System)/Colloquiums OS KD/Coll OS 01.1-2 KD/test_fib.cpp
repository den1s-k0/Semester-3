#include "test_fib.h"

INSTANTIATE_TEST_SUITE_P(
    VariousFinInputs,
    FibControlTest,
    ::testing::Values(
        make_tuple(1, vector<long long>{0, 1, 1}),
        make_tuple(2, vector<long long>{0, 1, 1, 2}),
        make_tuple(3, vector<long long>{0, 1, 1, 2, 3}),
        make_tuple(4, vector<long long>{0, 1, 1, 2, 3, 5}),
        make_tuple(5, vector<long long>{0, 1, 1, 2, 3, 5, 8})
    )
);

TEST_P(FibControlTest, FinConstrCorrectSize) {
    int expected_size = get<0>(GetParam());
    vector <long long> expected_fib_arr = get<1>(GetParam());

    fib test_fib(expected_size);

    EXPECT_EQ(test_fib.GetSize(), expected_size + 1);
    for (int i = 0; i < test_fib.GetSize(); i++) {
        EXPECT_EQ(test_fib[i], expected_fib_arr[i]);
    }
}

TEST(FibTest, FinDefaultConstrSize) {

    fib test_fib;

    EXPECT_EQ(test_fib.GetSize(), 1);
    EXPECT_EQ(test_fib[0], 0);
}

TEST(FibTest, FinConstrZeroSize) {

    fib test_fib(0);

    EXPECT_EQ(test_fib.GetSize(), 1);
    EXPECT_EQ(test_fib[0], 0);
}

TEST(FibTest, FinConstrNegativeSize) {

    fib test_fib(-10);

    EXPECT_EQ(test_fib.GetSize(), 1);
    EXPECT_EQ(test_fib[0], 0);
}

TEST(FibTest, FinConstrBigSize) {
    fib test_fib(92);

    EXPECT_EQ(test_fib.GetSize(), 93);
    EXPECT_EQ(test_fib[92], 7540113804746346429);
}

TEST(FibTest, FinConstrMaxSize) {
    fib test_fib(10000000);

    EXPECT_EQ(test_fib.GetSize(), 686);
}