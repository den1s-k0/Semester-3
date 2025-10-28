#pragma once

#include <iostream>
#include "bigint.h"

using namespace std;

struct fib {

private:
	int size;
	BigInt* fib_arr;

	void CalculateFib();

	int Min(int size_1, int size_2);

public:
	fib();
	fib(int s);

	~fib();

	int GetSize();
	void GetFibArr();

	const BigInt& operator[](int ind) const;
};