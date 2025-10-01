#pragma once

#include <gtest/gtest.h>
#include <tuple>
#include "../header.h"

class EmployeeConstructorTest : public ::testing::TestWithParam<std::tuple<int, const char*, double>> {};

class FunctionReadBinTest : public ::testing::TestWithParam<std::tuple<int, const char*, double>> {};

class FunctionReadTxtTest : public ::testing::TestWithParam<std::tuple<int, const char*, double>> {};