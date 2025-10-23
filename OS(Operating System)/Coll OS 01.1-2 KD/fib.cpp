#include "fib.h"

fib::fib()
{
	size = 0;
	fib_arr = new long long[0];
}

fib::fib(int s): size(s)
{
	if (size > 92) {
		cout << "Size too big\nSize = 94 (with 0 position)\n";
		size = 92;
	}
	fib_arr = new long long[size] {1, 1};
	CalculateFib();
}

fib::~fib()
{
	if (fib_arr != NULL)
		delete[] fib_arr;
}

void fib::CalculateFib()
{
	for (int i = 2; i < size; i++) {
		fib_arr[i] = fib_arr[i - 1] + fib_arr[i - 2];
	}
}

void fib::GetFibArr()
{
	for (int i = 0; i < size; i++) {
		cout << i << ": " << fib_arr[i] << "\n";
	}
}


