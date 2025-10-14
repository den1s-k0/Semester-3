#include "test_min_max.h"

TEST(MinTest, HandlesPositiveNumbers) {
    int* numbers = new int[10];
    int result;
    for (int i = 0; i < 10; i++) {
        numbers[i] = i + 1;
    }
    EXPECT_EQ(findMin(numbers, 10, result), ReturnMinMaxCodes::SUCCESS);
    EXPECT_EQ(result, 1);
    delete[] numbers;
}

TEST(MinTest, HandlesNegativeNumbers) {
    int* numbers = new int[4];
    int result;
    numbers[0] = -5;
    numbers[1] = -3;
    numbers[2] = -1;
    numbers[3] = -7;
    EXPECT_EQ(findMin(numbers, 4, result), ReturnMinMaxCodes::SUCCESS);
    EXPECT_EQ(result, -7);
    delete[] numbers;
}

TEST(MinTest, HandlesPositiveNegativeNumbers) {
    int* numbers = new int[6];
    int result;
    numbers[0] = 10;
    numbers[1] = -2;
    numbers[2] = 8;
    numbers[3] = -4;
    numbers[4] = 6;
    numbers[5] = -6;
    EXPECT_EQ(findMin(numbers, 6, result), ReturnMinMaxCodes::SUCCESS);
    EXPECT_EQ(result, -6);
    delete[] numbers;
}

TEST(MinTest, HandlesBigNumbers) {
    int* numbers = new int[5];
    int result;
    numbers[0] = 10000;
    numbers[1] = 20000;
    numbers[2] = 0;
    numbers[3] = 40000;
    numbers[4] = 50000;
    EXPECT_EQ(findMin(numbers, 5, result), ReturnMinMaxCodes::SUCCESS);
    EXPECT_EQ(result, 0);
    delete[] numbers;
}

TEST(MinTest, HandlesRandomNumbers) {
    int* numbers = new int[11];
    int result;
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
    EXPECT_EQ(findMin(numbers, 11, result), ReturnMinMaxCodes::SUCCESS);
    EXPECT_EQ(result, -8800);
    delete[] numbers;
}

TEST(MinTest, NULLPointer) {
    int* numbers = NULL;
    int result;
    EXPECT_EQ(findMin(numbers, 0, result), ReturnMinMaxCodes::ERROR_NULL_PONTER);
    delete[] numbers;
}

TEST(MinTest, ZeroLenghtArray) {
    int* numbers = new int[0];
    int result;
    EXPECT_EQ(findMin(numbers, 0, result), ReturnMinMaxCodes::ERROR_INVALID_LENGTH);
    delete[] numbers;
}

TEST(MinTest, InvalidLenghtArray) {
    int* numbers = new int[0];
    int result;
    EXPECT_EQ(findMin(numbers, -50, result), ReturnMinMaxCodes::ERROR_INVALID_LENGTH);
    delete[] numbers;
}

TEST(MinTest, HandlesSingleElement) {
    int* numbers = new int[1];
    int result;
    numbers[0] = 42;
    EXPECT_EQ(findMin(numbers, 1, result), ReturnMinMaxCodes::SUCCESS);
    EXPECT_EQ(result, 42);
    delete[] numbers;
}

TEST(MaxTest, HandlesPositiveNumbers) {
    int* numbers = new int[10];
    int result;
    for (int i = 0; i < 10; i++) {
        numbers[i] = i + 1;
    }
    EXPECT_EQ(findMax(numbers, 10, result), ReturnMinMaxCodes::SUCCESS);
    EXPECT_EQ(result, 10);
    delete[] numbers;
}

TEST(MaxTest, HandlesNegativeNumbers) {
    int* numbers = new int[4];
    int result;
    numbers[0] = -5;
    numbers[1] = -3;
    numbers[2] = -1;
    numbers[3] = -7;
    EXPECT_EQ(findMax(numbers, 4, result), ReturnMinMaxCodes::SUCCESS);
    EXPECT_EQ(result, -1);
    delete[] numbers;
}

TEST(MaxTest, HandlesPositiveNegativeNumbers) {
    int* numbers = new int[6];
    int result;
    numbers[0] = 10;
    numbers[1] = -2;
    numbers[2] = 8;
    numbers[3] = -4;
    numbers[4] = 6;
    numbers[5] = -6;
    EXPECT_EQ(findMax(numbers, 6, result), ReturnMinMaxCodes::SUCCESS);
    EXPECT_EQ(result, 10);
    delete[] numbers;
}

TEST(MaxTest, HandlesBigNumbers) {
    int* numbers = new int[5];
    int result;
    numbers[0] = 10000;
    numbers[1] = 20000;
    numbers[2] = 0;
    numbers[3] = 40000;
    numbers[4] = 50000;
    EXPECT_EQ(findMax(numbers, 5, result), ReturnMinMaxCodes::SUCCESS);
    EXPECT_EQ(result, 50000);
    delete[] numbers;
}

TEST(MaxTest, HandlesRandomNumbers) {
    int* numbers = new int[11];
    int result;
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
    EXPECT_EQ(findMax(numbers, 11, result), ReturnMinMaxCodes::SUCCESS);
    EXPECT_EQ(result, 6900);
    delete[] numbers;
}

TEST(MaxTest, NULLPointer) {
    int* numbers = NULL;
    int result;
    EXPECT_EQ(findMax(numbers, 0, result), ReturnMinMaxCodes::ERROR_NULL_PONTER);
    delete[] numbers;
}

TEST(MaxTest, ZeroLenghtArray) {
    int* numbers = new int[0];
    int result;
    EXPECT_EQ(findMax(numbers, 0, result), ReturnMinMaxCodes::ERROR_INVALID_LENGTH);
    delete[] numbers;
}

TEST(MaxTest, InvalidLenghtArray) {
    int* numbers = new int[0];
    int result;
    EXPECT_EQ(findMax(numbers, -50, result), ReturnMinMaxCodes::ERROR_INVALID_LENGTH);
    delete[] numbers;
}

TEST(MaxTest, HandlesSingleElement) {
    int* numbers = new int[1];
    int result;
    numbers[0] = 42;
    EXPECT_EQ(findMax(numbers, 1, result), ReturnMinMaxCodes::SUCCESS);
    EXPECT_EQ(result, 42);
    delete[] numbers;
}