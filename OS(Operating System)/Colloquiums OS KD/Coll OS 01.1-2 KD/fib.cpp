#include "fib.h"

fib::fib()
{
	size = 1;
	fib_arr = new BigInt[1];
	fib_arr[0] = 0;
}

fib::fib(int s): size(s + 1)
{
	if (size < 1) {
		cout << "Size too small\nSize = 1\n";
		size = 1;
	}
	if (size > 501) {
		cout << "Size too big\nSize = 501 (with 0 position)\n";
		size = 501;
	}
	fib_arr = new BigInt[size];
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

int fib::Min(int size_1, int size_2)
{
	if(size_1 > size_2)
		return size_2;
	return size_1;
}

void fib::GetFibArr()
{
	for (int i = 0; i < size; i++) {
		cout << i << ": " << fib_arr[i] << "\n";
	}
}

const BigInt& fib::operator[](int ind) const
{
	if (ind >= this->size) {
		throw std::out_of_range("Index out of range");
	}
	return (this->fib_arr)[ind];
}


