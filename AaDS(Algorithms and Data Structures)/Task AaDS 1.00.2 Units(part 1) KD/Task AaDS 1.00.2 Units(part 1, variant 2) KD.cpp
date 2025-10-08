#include <iostream>

using namespace std;

int main()
{
	int n, k, mod = 1000000007;
	cin >> n >> k;
	if (k > n / 2) k = n - k;
	int hight = n - k + 1;
	long long* N0 = new long long[hight] {};
	long long* N1 = new long long[hight] {};
	for (int i = 0; i < hight; i++) N0[i] = 1;

	for (int i = 1; i <= k; i++) {
		hight--;
		if (i % 2 == 1)
			N1[0] = ((N0[1] % mod) * 2) % mod;
		else
			N0[0] = ((N1[1] % mod) * 2) % mod;
		for (int j = 1; j < hight; j++) {
			if (i % 2 == 1) {
				N1[j] = ((N0[j + 1] % mod) + (N1[j - 1] % mod)) % mod;
			}
			else {
				N0[j] = ((N1[j + 1] % mod) + (N0[j - 1] % mod)) % mod;
			}
		}
	}
	if (k % 2 == 1) cout << N1[hight - 1];
	else cout << N0[hight - 1];
	delete[] N0;
	delete[] N1;
}
