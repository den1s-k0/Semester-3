#pragma once

#include <gtest/gtest.h>
#include <tuple>
#include <filesystem>
#include "../function.h"
#include "../employee.h"
#include "test_core.h"

void WriteTxtFile(string TextFileName, employee testemp);

class FunctionBinContolTest : public ::testing::TestWithParam<std::tuple<int, const char*, double>> {};

class FunctionTxtControlTest : public ::testing::TestWithParam<std::tuple<int, const char*, double>> {};