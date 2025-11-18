#include <iostream>
#include <cmath>
#include <string>

using namespace std;

long long FindSum(long long* mas, long long* sq_mas, int k, int left, int right) {
	long long sum = 0;
	if (right / k - left / k < 2) {
		for (int i = left; i < right; i++)
			sum += mas[i];
		cout << sum << endl;
		return sum;
	}
	for (int i = left; i < (left / k + 1) * k; i++)
		sum += mas[i];
	for (int i = (left / k) + 1; i < right / k; i++) 
		sum += sq_mas[i];
	for (int i = right - 1; i >= (right / k) * k; i--)
		sum += mas[i];
	cout << sum << endl;
	return sum;
}

void Add(long long* mas, long long* sq_mas, int k, int ind, int x) {
	mas[ind] += x;
	sq_mas[ind / k] += x;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int n, k, q, ind, x, l, r;
	string command;
	cin >> n;
	k = sqrt(n) + 1;
	long long* mas = new long long[n] {0};
	long long* sq_mas = new long long[n / k + 1] {0};
	for (int i = 0; i < n; i++) {
		cin >> mas[i];
		sq_mas[i / k] += mas[i];
	}
	cin >> q;
	for (int i = 0; i < q; i++) {
		cin >> command;
		if (command[0] == 'A') {
			cin >> ind >> x;
			Add(mas, sq_mas, k, ind, x);
		}
		if (command[0] == 'F') {
			cin >> l >> r;
			FindSum(mas, sq_mas, k, l, r);
		}
	}

	delete[] mas;
	delete[] sq_mas;
}
