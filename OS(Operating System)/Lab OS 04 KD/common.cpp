#include "common.h"

string cinString(int min, int max, string message) {
	string str;
	cout << message;
	getline(cin, str);
	while (str.size() < min) {
		cout << "\nString size is wrong\n" << message;
		getline(cin, str);
	}
	if (str.size() > max) {
		cout << "\nMessage will be cut off\n";
		return str.substr(0, max);
	}
	return str;
}

int cinInt(int min, int max, string message) {
	int n;
	cout << message;
	cin >> n;

	while (cin.fail() || n < min || n > max) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "\nWrong input\nEnter number from " << min << " to " << max << "\n" << message;
		cin >> n;
	}
	cin.ignore(10000, '\n');
	return n;
}