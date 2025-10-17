#pragma once

#include <gtest/gtest.h>
#include <tuple>
#include <filesystem>
#include "../function.h"
#include "../employee.h"

class CreatorControlTest : public ::testing::TestWithParam<std::tuple<int, const char*, double>> {};
