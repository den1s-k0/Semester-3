#include "test_core.h"

TEST(MinMaxThreadTest, HandlesPositiveNumbers) {
    ParamStructure struc(10);
    for (int i = 0; i < 10; i++) {
        struc.Mas[i] = i + 1;
    }

    HANDLE hMinMaxTest = CreateThread(NULL, 0, MinMaxThread, &struc, 0, NULL);
    ASSERT_TRUE(hMinMaxTest != NULL);

    WaitForSingleObject(hMinMaxTest, INFINITE);

    DWORD exitCode;
    BOOL result = GetExitCodeThread(hMinMaxTest, &exitCode);

    EXPECT_TRUE(result);
    EXPECT_EQ(exitCode, ReturnCoreCodes::SUCCESS);
    EXPECT_EQ(struc.min, 1);
    EXPECT_EQ(struc.max, 10);
    
    CloseHandle(hMinMaxTest);
}

TEST(MinMaxThreadTest, HandlesNegativeNumbers) {
    ParamStructure struc(4);
    struc.Mas[0] = -5;
    struc.Mas[1] = -3;
    struc.Mas[2] = -1;
    struc.Mas[3] = -7;

    HANDLE hMinMaxTest = CreateThread(NULL, 0, MinMaxThread, &struc, 0, NULL);
    ASSERT_TRUE(hMinMaxTest != NULL);

    WaitForSingleObject(hMinMaxTest, INFINITE);

    DWORD exitCode;
    BOOL result = GetExitCodeThread(hMinMaxTest, &exitCode);

    EXPECT_TRUE(result);
    EXPECT_EQ(exitCode, ReturnCoreCodes::SUCCESS);
    EXPECT_EQ(struc.min, -7);
    EXPECT_EQ(struc.max, -1);

    CloseHandle(hMinMaxTest);
}

TEST(MinMaxThreadTest, HandlesPositiveNegativeNumbers) {
    ParamStructure struc(6);
    struc.Mas[0] = 10;
    struc.Mas[1] = -2;
    struc.Mas[2] = 8;
    struc.Mas[3] = -4;
    struc.Mas[4] = 6;
    struc.Mas[5] = -6;

    HANDLE hMinMaxTest = CreateThread(NULL, 0, MinMaxThread, &struc, 0, NULL);
    ASSERT_TRUE(hMinMaxTest != NULL);

    WaitForSingleObject(hMinMaxTest, INFINITE);

    DWORD exitCode;
    BOOL result = GetExitCodeThread(hMinMaxTest, &exitCode);

    EXPECT_TRUE(result);
    EXPECT_EQ(exitCode, ReturnCoreCodes::SUCCESS);
    EXPECT_EQ(struc.min, -6);
    EXPECT_EQ(struc.max, 10);

    CloseHandle(hMinMaxTest);
}

TEST(MinMaxThreadTest, HandlesBigNumbers) {
    ParamStructure struc(5);
    struc.Mas[0] = 10000;
    struc.Mas[1] = 20000;
    struc.Mas[2] = 0;
    struc.Mas[3] = 40000;
    struc.Mas[4] = 50000;

    HANDLE hMinMaxTest = CreateThread(NULL, 0, MinMaxThread, &struc, 0, NULL);
    ASSERT_TRUE(hMinMaxTest != NULL);

    WaitForSingleObject(hMinMaxTest, INFINITE);

    DWORD exitCode;
    BOOL result = GetExitCodeThread(hMinMaxTest, &exitCode);

    EXPECT_TRUE(result);
    EXPECT_EQ(exitCode, ReturnCoreCodes::SUCCESS);
    EXPECT_EQ(struc.min, 0);
    EXPECT_EQ(struc.max, 50000);

    CloseHandle(hMinMaxTest);
}

TEST(MinMaxThreadTest, HandlesRandomNumbers) {
    ParamStructure struc(11);
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

    HANDLE hMinMaxTest = CreateThread(NULL, 0, MinMaxThread, &struc, 0, NULL);
    ASSERT_TRUE(hMinMaxTest != NULL);

    WaitForSingleObject(hMinMaxTest, INFINITE);

    DWORD exitCode;
    BOOL result = GetExitCodeThread(hMinMaxTest, &exitCode);

    EXPECT_TRUE(result);
    EXPECT_EQ(exitCode, ReturnCoreCodes::SUCCESS);
    EXPECT_EQ(struc.min, -8800);
    EXPECT_EQ(struc.max, 6900);

    CloseHandle(hMinMaxTest);
}

TEST(MinMaxThreadTest, NULLPointer) {
    ParamStructure struc;

    HANDLE hMinMaxTest = CreateThread(NULL, 0, MinMaxThread, &struc, 0, NULL);
    ASSERT_TRUE(hMinMaxTest != NULL);

    WaitForSingleObject(hMinMaxTest, INFINITE);

    DWORD exitCode;
    BOOL result = GetExitCodeThread(hMinMaxTest, &exitCode);

    EXPECT_TRUE(result);
    EXPECT_EQ(exitCode, ReturnCoreCodes::ERROR_MIN_SEARCH);
    EXPECT_EQ(struc.min, 0);
    EXPECT_EQ(struc.max, 0);

    CloseHandle(hMinMaxTest);
}

TEST(MinMaxThreadTest, ZeroLenghtArray) {
    ParamStructure struc(0);

    HANDLE hMinMaxTest = CreateThread(NULL, 0, MinMaxThread, &struc, 0, NULL);
    ASSERT_TRUE(hMinMaxTest != NULL);

    WaitForSingleObject(hMinMaxTest, INFINITE);

    DWORD exitCode;
    BOOL result = GetExitCodeThread(hMinMaxTest, &exitCode);

    EXPECT_TRUE(result);
    EXPECT_EQ(exitCode, ReturnCoreCodes::ERROR_MIN_SEARCH);
    EXPECT_EQ(struc.min, 0);
    EXPECT_EQ(struc.max, 0);

    CloseHandle(hMinMaxTest);
}

TEST(MinMaxThreadTest, InvalidLenghtArray) {
    ParamStructure struc(-5);

    HANDLE hMinMaxTest = CreateThread(NULL, 0, MinMaxThread, &struc, 0, NULL);
    ASSERT_TRUE(hMinMaxTest != NULL);

    WaitForSingleObject(hMinMaxTest, INFINITE);

    DWORD exitCode;
    BOOL result = GetExitCodeThread(hMinMaxTest, &exitCode);

    EXPECT_TRUE(result);
    EXPECT_EQ(exitCode, ReturnCoreCodes::ERROR_MIN_SEARCH);
    EXPECT_EQ(struc.min, 0);
    EXPECT_EQ(struc.max, 0);

    CloseHandle(hMinMaxTest);
}

TEST(MinMaxThreadTest, HandlesSingleElement) {
    ParamStructure struc(1);
    struc.Mas[0] = 42;
    HANDLE hMinMaxTest = CreateThread(NULL, 0, MinMaxThread, &struc, 0, NULL);
    ASSERT_TRUE(hMinMaxTest != NULL);

    WaitForSingleObject(hMinMaxTest, INFINITE);

    DWORD exitCode;
    BOOL result = GetExitCodeThread(hMinMaxTest, &exitCode);

    EXPECT_TRUE(result);
    EXPECT_EQ(exitCode, ReturnCoreCodes::SUCCESS);
    EXPECT_EQ(struc.min, 42);
    EXPECT_EQ(struc.max, 42);

    CloseHandle(hMinMaxTest);
}

TEST(AverageThreadTest, HandlesPositiveNumbers) {
    ParamStructure struc(10);
    for (int i = 0; i < 10; i++) {
        struc.Mas[i] = i + 1;
    }

    HANDLE hAverageTest = CreateThread(NULL, 0, AverageThread, &struc, 0, NULL);
    ASSERT_TRUE(hAverageTest != NULL);

    WaitForSingleObject(hAverageTest, INFINITE);

    DWORD exitCode;
    BOOL result = GetExitCodeThread(hAverageTest, &exitCode);

    EXPECT_TRUE(result);
    EXPECT_EQ(exitCode, ReturnCoreCodes::SUCCESS);
    EXPECT_EQ(struc.average, 5);

    CloseHandle(hAverageTest);
}

TEST(AverageThreadTest, HandlesNegativeNumbers) {
    ParamStructure struc(4);
    struc.Mas[0] = -5;
    struc.Mas[1] = -3;
    struc.Mas[2] = -1;
    struc.Mas[3] = -7;

    HANDLE hAverageTest = CreateThread(NULL, 0, AverageThread, &struc, 0, NULL);
    ASSERT_TRUE(hAverageTest != NULL);

    WaitForSingleObject(hAverageTest, INFINITE);

    DWORD exitCode;
    BOOL result = GetExitCodeThread(hAverageTest, &exitCode);

    EXPECT_TRUE(result);
    EXPECT_EQ(exitCode, ReturnCoreCodes::SUCCESS);
    EXPECT_EQ(struc.average, -4);


    CloseHandle(hAverageTest);
}

TEST(AverageThreadTest, HandlesPositiveNegativeNumbers) {
    ParamStructure struc(6);
    struc.Mas[0] = 10;
    struc.Mas[1] = -2;
    struc.Mas[2] = 8;
    struc.Mas[3] = -4;
    struc.Mas[4] = 6;
    struc.Mas[5] = -6;

    HANDLE hAverageTest = CreateThread(NULL, 0, AverageThread, &struc, 0, NULL);
    ASSERT_TRUE(hAverageTest != NULL);

    WaitForSingleObject(hAverageTest, INFINITE);

    DWORD exitCode;
    BOOL result = GetExitCodeThread(hAverageTest, &exitCode);

    EXPECT_TRUE(result);
    EXPECT_EQ(exitCode, ReturnCoreCodes::SUCCESS);
    EXPECT_EQ(struc.average, 2);

    CloseHandle(hAverageTest);
}

TEST(AverageThreadTest, HandlesBigNumbers) {
    ParamStructure struc(5);
    struc.Mas[0] = 10000;
    struc.Mas[1] = 20000;
    struc.Mas[2] = 0;
    struc.Mas[3] = 40000;
    struc.Mas[4] = 50000;

    HANDLE hAverageTest = CreateThread(NULL, 0, AverageThread, &struc, 0, NULL);
    ASSERT_TRUE(hAverageTest != NULL);

    WaitForSingleObject(hAverageTest, INFINITE);

    DWORD exitCode;
    BOOL result = GetExitCodeThread(hAverageTest, &exitCode);

    EXPECT_TRUE(result);
    EXPECT_EQ(exitCode, ReturnCoreCodes::SUCCESS);
    EXPECT_EQ(struc.average, 24000);

    CloseHandle(hAverageTest);
}

TEST(AverageThreadTest, HandlesRandomNumbers) {
    ParamStructure struc(11);
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

    HANDLE hAverageTest = CreateThread(NULL, 0, AverageThread, &struc, 0, NULL);
    ASSERT_TRUE(hAverageTest != NULL);

    WaitForSingleObject(hAverageTest, INFINITE);

    DWORD exitCode;
    BOOL result = GetExitCodeThread(hAverageTest, &exitCode);

    EXPECT_TRUE(result);
    EXPECT_EQ(exitCode, ReturnCoreCodes::SUCCESS);
    EXPECT_EQ(struc.average, 372);

    CloseHandle(hAverageTest);
}

TEST(AverageThreadTest, NULLPointer) {
    ParamStructure struc;

    HANDLE hAverageTest = CreateThread(NULL, 0, AverageThread, &struc, 0, NULL);
    ASSERT_TRUE(hAverageTest != NULL);

    WaitForSingleObject(hAverageTest, INFINITE);

    DWORD exitCode;
    BOOL result = GetExitCodeThread(hAverageTest, &exitCode);

    EXPECT_TRUE(result);
    EXPECT_EQ(exitCode, ReturnCoreCodes::ERROR_AVERAGE_SEARCH);
    EXPECT_EQ(struc.average, 0);

    CloseHandle(hAverageTest);
}

TEST(AverageThreadTest, ZeroLenghtArray) {
    ParamStructure struc(0);

    HANDLE hAverageTest = CreateThread(NULL, 0, AverageThread, &struc, 0, NULL);
    ASSERT_TRUE(hAverageTest != NULL);

    WaitForSingleObject(hAverageTest, INFINITE);

    DWORD exitCode;
    BOOL result = GetExitCodeThread(hAverageTest, &exitCode);

    EXPECT_TRUE(result);
    EXPECT_EQ(exitCode, ReturnCoreCodes::ERROR_AVERAGE_SEARCH);
    EXPECT_EQ(struc.average, 0);

    CloseHandle(hAverageTest);
}

TEST(AverageThreadTest, InvalidLenghtArray) {
    ParamStructure struc(-5);

    HANDLE hAverageTest = CreateThread(NULL, 0, AverageThread, &struc, 0, NULL);
    ASSERT_TRUE(hAverageTest != NULL);

    WaitForSingleObject(hAverageTest, INFINITE);

    DWORD exitCode;
    BOOL result = GetExitCodeThread(hAverageTest, &exitCode);

    EXPECT_TRUE(result);
    EXPECT_EQ(exitCode, ReturnCoreCodes::ERROR_AVERAGE_SEARCH);
    EXPECT_EQ(struc.average, 0);

    CloseHandle(hAverageTest);
}

TEST(AverageThreadTest, HandlesSingleElement) {
    ParamStructure struc(1);
    struc.Mas[0] = 42;
    HANDLE hAverageTest = CreateThread(NULL, 0, AverageThread, &struc, 0, NULL);
    ASSERT_TRUE(hAverageTest != NULL);

    WaitForSingleObject(hAverageTest, INFINITE);

    DWORD exitCode;
    BOOL result = GetExitCodeThread(hAverageTest, &exitCode);

    EXPECT_TRUE(result);
    EXPECT_EQ(exitCode, ReturnCoreCodes::SUCCESS);
    EXPECT_EQ(struc.average, 42);


    CloseHandle(hAverageTest);
}
