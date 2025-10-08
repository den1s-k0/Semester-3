#include <iostream>

using namespace std;

int max(int a, int b) {
	if (a > b) return a;
	return b;
}

int main()
{
	int n;
	cin >> n;
	int* mosquito = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> mosquito[i];
	}

	if (n == 1) {
		cout << mosquito[0] << endl << 1;
		delete[] mosquito;
		return 0;
	}
	if (n == 2) {
		cout << -1;
		delete[] mosquito;
		return 0;
	}

	int* profit = new int[n] {mosquito[0], -1};
	profit[2] = profit[0] + mosquito[2];
	for (int i = 3; i < n; i++) {
		profit[i] = max(profit[i - 2], profit[i - 3]) + mosquito[i];
	}

	int* path = new int[n] {0};
	path[n - 1] = 1;
	int i = n - 1;
	while (i > 0) {
		if (profit[i] - mosquito[i] == profit[i - 3]) {
			path[i - 3] = 1;
			i -= 3;
		}
		else {
			path[i - 2] = 1;
			i -= 2;
		}
	}
	if (i != 0) {
		cout << -1;
		delete[] mosquito;
		delete[] profit;
		delete[] path;
		return 0;
	}
	cout << profit[n - 1] << endl;
	for (int j = 0; j < n; j++) {
		if (path[j] == 1) cout << ++j << " ";
	}
	delete[] mosquito;
	delete[] profit;
	delete[] path;
	return 0;
}