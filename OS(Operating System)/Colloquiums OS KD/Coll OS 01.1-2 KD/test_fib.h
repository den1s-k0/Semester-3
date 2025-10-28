#pragma once

#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include <tuple>
#include "fib.h"
#include "bigint.h"

using namespace std;

class FibControlTest : public ::testing::TestWithParam<std::tuple<int, vector<long long>>> {};
