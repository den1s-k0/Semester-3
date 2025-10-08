#include <iostream>

using namespace std;

int main()
{
	int n, k, mod = 1000000007;
	cin >> n >> k;
	long long* N = new long long[k + 1] {1};
	for (int j = 0; j <= n - k; j++) {
		for (int i = 1; i <= k; i++) {
			N[i] = ((N[i - 1] % mod) + (N[i] % mod)) % mod;
		}
	}
	cout << N[k];
}
