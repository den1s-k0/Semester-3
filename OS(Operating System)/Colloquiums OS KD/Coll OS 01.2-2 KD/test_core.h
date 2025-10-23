#pragma once

#include <iostream>
#include <string>
#include "core.h"
#include "gtest/gtest.h"
#include <tuple>

using namespace std;

class NumberControlTest : public ::testing::TestWithParam<std::tuple<string, bool>> {};

class PalendControlTest : public ::testing::TestWithParam<std::tuple<string, bool>> {};

class PalendNumberControlTest : public ::testing::TestWithParam<std::tuple<string, int>> {};

