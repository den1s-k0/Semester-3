#include "bigint.h"

BigInt::BigInt() {
	for (int i = 0; i < SIZE; i++)
		digits[i] = 0;
}

BigInt::BigInt(long long x) {
	for (int i = 0; i < SIZE; i++)
		digits[i] = 0;

	int next = 0;
	while (x) {
		digits[next++] = x % BASE;
		x /= BASE;
	}
}

BigInt::BigInt(const BigInt& other) {
	for (int i = 0; i < SIZE; i++)
		digits[i] = other.digits[i];
}

BigInt& BigInt::operator=(const BigInt other) {
	for (int i = 0; i < SIZE; i++)
		digits[i] = other.digits[i];

	return *this;
}

BigInt::~BigInt() {
	delete[] digits;
}

void BigInt::operator+=(const BigInt& other) {
	for (int i = 0; i < SIZE; i++)
		digits[i] += other.digits[i];

	for (int i = 0; i < SIZE - 1; i++) {
		if (digits[i] >= BASE) {
			digits[i] -= BASE;
			digits[i + 1]++;
		}
	}
}

BigInt BigInt::operator+(const BigInt& other) {
	BigInt N(*this);
	N += other;

	return N;
}

bool BigInt::operator==(const BigInt& other) const {
	for (int i = 0; i < SIZE; i++)
		if (digits[i] != other.digits[i])
			return false;
	return true;
}

bool BigInt::operator==(const int& other) const
{
	BigInt oth(other);
	for (int i = 1; i < SIZE; i++)
		if (digits[i] != oth.digits[i])
			return false;
	return true;
}

bool BigInt::operator==(const long long& other) const
{
	BigInt oth(other);
	for (int i = 1; i < SIZE; i++)
		if (digits[i] != oth.digits[i])
			return false;
	return true;
}

ostream& operator<<(ostream& out, const BigInt& num) {
	string result;

	char buffer[10];

	for (int i = BigInt::SIZE - 1; i >= 0; i--) {
		sprintf(buffer, "%09d", num.digits[i]);
		result += buffer;
	}

	int first_idx = result.find_first_not_of('0');
	if (first_idx == string::npos) {
		out << "0";
	}
	else {
		out << result.substr(first_idx);
	}

	return out;
}
