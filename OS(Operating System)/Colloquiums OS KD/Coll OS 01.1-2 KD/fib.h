#pragma once

#include <iostream>

using namespace std;

struct fib {

private:
	int size;
	long long* fib_arr;

	void CalculateFib();

public:
	fib();
	fib(int s);

	~fib();

	int GetSize();
	void GetFibArr();

	const long long& operator[](int ind) const;
};