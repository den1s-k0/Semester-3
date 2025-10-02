#pragma once

#include <gtest/gtest.h>
#include <tuple>
#include <filesystem>
#include "../header.h"

void WriteBinFile(string BinFileName, employee testemp);

void WriteTxtFile(string TextFileName, employee testemp);

class EmployeeControlTest : public ::testing::TestWithParam<std::tuple<int, const char*, double>> {};

class FunctionBinContolTest : public ::testing::TestWithParam<std::tuple<int, const char*, double>> {};

class FunctionTxtControlTest : public ::testing::TestWithParam<std::tuple<int, const char*, double>> {};

class CreatorControlTest : public ::testing::TestWithParam<std::tuple<int, const char*, double>> {};