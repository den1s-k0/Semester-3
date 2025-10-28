#pragma once

#include <iostream>

using namespace std;

class BigInt {
public:

	long long* digits = new long long[SIZE];
	static const long long BASE = 1000000000;
	static const long long SIZE = 13;

	BigInt();

	BigInt(long long x);

	BigInt(const BigInt& other);

	BigInt& operator=(const BigInt other);

	~BigInt();

	void operator+=(const BigInt& other);

	BigInt operator+(const BigInt& other);

	BigInt& operator++();

	void operator-=(const BigInt& other);

	BigInt operator-(const BigInt& other);

	BigInt& operator--();

	bool operator==(const BigInt& other) const;

	friend ostream& operator<<(std::ostream& out, const BigInt& num);
};
