#pragma once

#include <gtest/gtest.h>
#include <tuple>
#include <filesystem>
#include "../header.h"

void WriteBinFile(string BinFileName, employee testemp) {
	ofstream out(BinFileName, ios::binary);
	if (out.is_open()) {
		out.write(reinterpret_cast<char*>(&testemp), sizeof(employee));
	}
	out.close();
}

void WriteTxtFile(string TextFileName, employee testemp) {
	ofstream out(TextFileName);
	if (out.is_open()) {
		out << testemp;
	}
	out.close();
}

class EmployeeControlTest : public ::testing::TestWithParam<std::tuple<int, const char*, double>> {};

class FunctionBinContolTest : public ::testing::TestWithParam<std::tuple<int, const char*, double>> {};

class FunctionTxtControlTest : public ::testing::TestWithParam<std::tuple<int, const char*, double>> {};

class CreatorControlTest : public ::testing::TestWithParam<std::tuple<int, const char*, double>> {};

class ReporterControlTest : public ::testing::TestWithParam<std::tuple<int, const char*, double, int>> {};
