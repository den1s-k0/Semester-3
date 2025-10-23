#include "main.h"

int main()
{
	int n;
	cout << "Enter number: ";
	cin >> n;
	if (cin.fail()) {
		cout << "Wrong enter\nNumber = 0\n";
		n = 0;
	}
	fib answer(n);
	answer.GetFibArr();
}
