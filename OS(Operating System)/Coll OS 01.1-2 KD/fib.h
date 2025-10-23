#pragma once

#include <iostream>

using namespace std;

struct fib {
	int size;
	long long* fib_arr = new long long[size];

	fib();
	fib(int s);

	~fib();

	void CalculateFib();
	void GetFibArr();
	fib StartFib();
};