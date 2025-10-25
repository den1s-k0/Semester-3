#include "core.h"

vector <int> createVectorOfZeros() {
	int n;
	cout << "Enter array size: ";
	cin >> n;
	while (cin.fail() || n > 2000000000 || n < 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Wrong input\nEnter number from 0 to 2 000 000 000: ";
		cin >> n;
	}
	return vector<int>(n);
}

int cinThreadCount() {
	int n;
	cout << "Enter count of threads: ";
	cin >> n;
	while (cin.fail() || n > 2000000000 || n < 0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Wrong input\nEnter number from 0 to 2 000 000 000: ";
		cin >> n;
	}
	return n;
}
