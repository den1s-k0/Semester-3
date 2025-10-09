#include "test_average.h"

TEST(AverageTest, HandlesPositiveNumbers) {
    int* numbers = new int[10];
    for (int i = 0; i < 10; i++) {
        numbers[i] = i + 1;
    }
    EXPECT_EQ(calculateAverage(numbers, 10), 5);
    delete[] numbers; 
}

TEST(AverageTest, HandlesNegativeNumbers) {
    int* numbers = new int[4];
    numbers[0] = -5;
    numbers[1] = -3;
    numbers[2] = -1;
    numbers[3] = -7;
    EXPECT_EQ(calculateAverage(numbers, 4), -4);
    delete[] numbers;
}

TEST(AverageTest, HandlesPositiveNegativeNumbers) {
    int* numbers = new int[6];
    numbers[0] = 10;
    numbers[1] = -2;
    numbers[2] = 8;
    numbers[3] = -4;
    numbers[4] = 6;
    numbers[5] = -6;
    EXPECT_EQ(calculateAverage(numbers, 6), 2);
    delete[] numbers;
}

TEST(AverageTest, HandlesBigNumbers) {
    int* numbers = new int[5];
    numbers[0] = 10000;
    numbers[1] = 20000;
    numbers[2] = 0;
    numbers[3] = 40000;
    numbers[4] = 50000;
    EXPECT_EQ(calculateAverage(numbers, 5), 24000);
    delete[] numbers;
}

TEST(AverageTest, HandlesRandomNumbers) {
    int* numbers = new int[11];
    numbers[0] = 6900;
    numbers[1] = -670;
    numbers[2] = 5252;
    numbers[3] = 42;
    numbers[4] = -3;
    numbers[5] = 14;
    numbers[6] = -8800;
    numbers[7] = 94;
    numbers[8] = 49;
    numbers[9] = 974;
    numbers[10] = 250;
    EXPECT_EQ(calculateAverage(numbers, 11), 372);
    delete[] numbers;
}

TEST(AverageTest, HandlesEmptyArray) {
    int* numbers = new int[0];
    EXPECT_EQ(calculateAverage(numbers, 0), 0);
    delete[] numbers;
}

TEST(AverageTest, HandlesSingleElement) {
    int* numbers = new int[1];
    numbers[0] = 42;
    EXPECT_EQ(calculateAverage(numbers, 1), 42);
    delete[] numbers;
}
