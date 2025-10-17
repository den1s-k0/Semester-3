#pragma once

#include <gtest/gtest.h>
#include <tuple>
#include <filesystem>
#include "../employee.h"

class EmployeeControlTest : public ::testing::TestWithParam<std::tuple<int, const char*, double>> {};
