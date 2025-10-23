#include "fib.h"

fib::fib()
{
	size = 1;
	fib_arr = new long long[1] {1};
}

fib::fib(int s): size(s + 1)
{
	if (size < 1) {
		cout << "Size too small\nSize = 1\n";
		size = 1;
	}
	if (size > 92) {
		cout << "Size too big\nSize = 92 (with 0 position)\n";
		size = 92;
	}
	fib_arr = new long long[size] {1};
	CalculateFib();
}

fib::~fib()
{
	if (fib_arr != NULL)
		delete[] fib_arr;
}

int fib::GetSize()
{
	return size;
}

void fib::CalculateFib()
{
	
	if (size > 1) {
		fib_arr[1] = 1;
		for (int i = 2; i < size; i++) {
			fib_arr[i] = fib_arr[i - 1] + fib_arr[i - 2];
		}
	}
}

void fib::GetFibArr()
{
	for (int i = 0; i < size; i++) {
		cout << i << ": " << fib_arr[i] << "\n";
	}
}

const long long& fib::operator[](int ind) const
{
	if (ind >= this->size) {
		throw std::out_of_range("Index out of range");
	}
	return (this->fib_arr)[ind];
}


