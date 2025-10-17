#pragma once

#include <gtest/gtest.h>
#include <tuple>
#include <filesystem>
#include "../function.h"
#include "../employee.h"
#include "test_core.h"

class ReporterControlTest : public ::testing::TestWithParam<std::tuple<int, const char*, double, int>> {};
