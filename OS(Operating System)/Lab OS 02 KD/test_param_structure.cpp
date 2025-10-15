#include "test_param_structure.h"

TEST(ParamConstructorTest, DefaultConstructor) {
    ParamStructure struc;
    EXPECT_EQ(struc.size, 0);
    EXPECT_EQ(struc.min, 0);
    EXPECT_EQ(struc.max, 0);
    EXPECT_EQ(struc.average, 0);
    EXPECT_TRUE(struc.Mas == NULL);
}

TEST(ParamConstructorTest, ZeroSizeParametrConstructor) {
    ParamStructure struc(0);
    EXPECT_EQ(struc.size, 0);
    EXPECT_EQ(struc.min, 0);
    EXPECT_EQ(struc.max, 0);
    EXPECT_EQ(struc.average, 0);
    EXPECT_TRUE(struc.Mas != NULL);
}

TEST(ParamConstructorTest, SizeParametrConstructor) {
    ParamStructure struc(10);
    EXPECT_EQ(struc.size, 10);
    EXPECT_EQ(struc.min, 0);
    EXPECT_EQ(struc.max, 0);
    EXPECT_EQ(struc.average, 0);
    EXPECT_TRUE(struc.Mas != NULL);
}

TEST(ParamConstructorTest, ZeroParametrConstructor) {
    ParamStructure struc(0, 0, 0, 0);
    EXPECT_EQ(struc.size, 0);
    EXPECT_EQ(struc.min, 0);
    EXPECT_EQ(struc.max, 0);
    EXPECT_EQ(struc.average, 0);
    EXPECT_TRUE(struc.Mas != NULL);
}

TEST(ParamConstructorTest, ParametrConstructor) {
    ParamStructure struc(10, 7000, -479, -8999);
    EXPECT_EQ(struc.size, 10);
    EXPECT_EQ(struc.min, 7000);
    EXPECT_EQ(struc.max, -479);
    EXPECT_EQ(struc.average, -8999);
    EXPECT_TRUE(struc.Mas != NULL);
}

TEST(ParamArrayChangeTest, HandlesPositiveNumbers) {
    ParamStructure struc(10, 1, 10, 5);
    for (int i = 0; i < 10; i++) {
        struc.Mas[i] = i + 1;
    }
    EXPECT_EQ(struc.ArrayChange(), ReturnParamCodes::SUCCESS);
    EXPECT_EQ(struc.Mas[0], 5);
    EXPECT_EQ(struc.Mas[1], 2);
    EXPECT_EQ(struc.Mas[2], 3);
    EXPECT_EQ(struc.Mas[3], 4);
    EXPECT_EQ(struc.Mas[4], 5);
    EXPECT_EQ(struc.Mas[5], 6);
    EXPECT_EQ(struc.Mas[6], 7);
    EXPECT_EQ(struc.Mas[7], 8);
    EXPECT_EQ(struc.Mas[8], 9);
    EXPECT_EQ(struc.Mas[9], 5);
}

TEST(ParamArrayChangeTest, HandlesNegativeNumbers) {
    ParamStructure struc(4, -7, -1, -4);
    struc.Mas[0] = -5;
    struc.Mas[1] = -3;
    struc.Mas[2] = -1;
    struc.Mas[3] = -7;
    EXPECT_EQ(struc.ArrayChange(), ReturnParamCodes::SUCCESS);
    EXPECT_EQ(struc.Mas[0], -5);
    EXPECT_EQ(struc.Mas[1], -3);
    EXPECT_EQ(struc.Mas[2], -4);
    EXPECT_EQ(struc.Mas[3], -4);
}

TEST(ParamArrayChangeTest, HandlesPositiveNegativeNumbers) {
    ParamStructure struc(6, -6, 10, 2);
    struc.Mas[0] = 10;
    struc.Mas[1] = -2;
    struc.Mas[2] = 8;
    struc.Mas[3] = -4;
    struc.Mas[4] = 6;
    struc.Mas[5] = -6;
    EXPECT_EQ(struc.ArrayChange(), ReturnParamCodes::SUCCESS);
    EXPECT_EQ(struc.Mas[0], 2);
    EXPECT_EQ(struc.Mas[1], -2);
    EXPECT_EQ(struc.Mas[2], 8);
    EXPECT_EQ(struc.Mas[3], -4);
    EXPECT_EQ(struc.Mas[4], 6);
    EXPECT_EQ(struc.Mas[5], 2);
}

TEST(ParamArrayChangeTest, HandlesBigNumbers) {
    ParamStructure struc(5, 0, 50000, 24000);
    struc.Mas[0] = 10000;
    struc.Mas[1] = 20000;
    struc.Mas[2] = 0;
    struc.Mas[3] = 40000;
    struc.Mas[4] = 50000;
    EXPECT_EQ(struc.ArrayChange(), ReturnParamCodes::SUCCESS);
    EXPECT_EQ(struc.Mas[0], 10000);
    EXPECT_EQ(struc.Mas[1], 20000);
    EXPECT_EQ(struc.Mas[2], 24000);
    EXPECT_EQ(struc.Mas[3], 40000);
    EXPECT_EQ(struc.Mas[4], 24000);
}

TEST(ParamArrayChangeTest, HandlesRandomNumbers) {
    ParamStructure struc(11, -8800, 6900, 372);
    struc.Mas[0] = 6900;
    struc.Mas[1] = -670;
    struc.Mas[2] = 5252;
    struc.Mas[3] = 42;
    struc.Mas[4] = -3;
    struc.Mas[5] = 14;
    struc.Mas[6] = -8800;
    struc.Mas[7] = 94;
    struc.Mas[8] = 49;
    struc.Mas[9] = 974;
    struc.Mas[10] = 250;
    EXPECT_EQ(struc.ArrayChange(), ReturnParamCodes::SUCCESS);
}

TEST(ParamArrayChangeTest, NULLPointer) {
    ParamStructure struc;
    EXPECT_EQ(struc.ArrayChange(), ReturnParamCodes::ERROR_NULL_PONTER);
    EXPECT_TRUE(struc.Mas == NULL);
}

TEST(ParamArrayChangeTest, ZeroLenghtArray) {
    ParamStructure struc(0);
    EXPECT_EQ(struc.ArrayChange(), ReturnParamCodes::ERROR_INVALID_LENGTH);
    EXPECT_TRUE(struc.Mas != NULL);
}

TEST(ParamArrayChangeTest, InvalidLenghtArray) {
    ParamStructure struc(-5);
    EXPECT_EQ(struc.ArrayChange(), ReturnParamCodes::ERROR_INVALID_LENGTH);
    EXPECT_TRUE(struc.Mas != NULL);
}

TEST(ParamArrayChangeTest, HandlesSingleElement) {
    ParamStructure struc(1, 42, 42, 42);
    struc.Mas[0] = 42;
    EXPECT_EQ(struc.ArrayChange(), ReturnParamCodes::SUCCESS);
    EXPECT_EQ(struc.Mas[0], 42);
}
