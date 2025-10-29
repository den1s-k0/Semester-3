#include "test_big_int.h"

TEST(BigInt, DefaultConstructor) {
	BigInt a;
	EXPECT_EQ(a, 0);
}

TEST(BigInt, ParamIntConstructor) {
	BigInt a(123456789);
	EXPECT_EQ(a, 123456789);
}

TEST(BigInt, ParamNegativeIntConstructor) {
	BigInt a(-123456789);
	EXPECT_EQ(a, -123456789);
}

TEST(BigInt, ParamLongLongConstructor) {
	BigInt a(123456789123456789);
	EXPECT_EQ(a, 123456789123456789);
}

TEST(BigInt, ParamNegativeLongLongConstructor) {
	BigInt a(-123456789123456789);
	EXPECT_EQ(a, -123456789123456789);
}

TEST(BigInt, CopyConstructor) {
	BigInt a(123456789123456789);
	BigInt b(a);
	EXPECT_EQ(a, b);
}

TEST(BigInt, NegativeCopyConstructor) {
	BigInt b(-123456789123456789);
	BigInt a(b);
	EXPECT_EQ(a, b);
}

TEST(BigInt, OperatorEqually) {
	BigInt a(123456789123456789);
	BigInt b(1);
	b = a;
	EXPECT_EQ(a, b);
}

TEST(BigInt, NegativeOperatorEqually) {
	BigInt b(-123456789123456789);
	BigInt a(1);
	a = b;
	EXPECT_EQ(a, b);
}

TEST(BigInt, OperatorPlusEqually) {
	BigInt a(100000000000000000);
	int result = 1;
	string output;
	for (int i = 0; i < 10; i++) {
		a += a;
		result += result;
		testing::internal::CaptureStdout();
		cout << a;
		output = testing::internal::GetCapturedStdout();
		EXPECT_TRUE(output.find(to_string(result) + "00000000000000000") != string::npos);
	}
}

TEST(BigInt, OperatorPlus) {
	BigInt a(100000000000000000);
	int result = 1;
	string output;
	for (int i = 0; i < 10; i++) {
		a = a + a;
		result = result + result;
		testing::internal::CaptureStdout();
		cout << a;
		output = testing::internal::GetCapturedStdout();
		EXPECT_TRUE(output.find(to_string(result) + "00000000000000000") != string::npos);
	}
}




