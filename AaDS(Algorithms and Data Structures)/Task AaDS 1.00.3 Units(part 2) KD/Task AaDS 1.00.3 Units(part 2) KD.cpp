#include <iostream>

using namespace std;

long long degree(int a, int d, int mod) {
    if (d == 1) return a;
    if (d == 0) return 1;

    long long prom;
    if (d % 2 == 0) {
        prom = degree(a, d / 2, mod);
        return ((prom % mod) * (prom % mod)) % mod;
    }
    else {
        prom = degree(a, (d - 1) / 2, mod);
        return ((((prom % mod) * (prom % mod)) % mod) * (a % mod)) % mod;
    }
    
}

long long calculateC(int n, int k, int mod) {
    long long result = 1;
    for (int i = 1; i <= n - k; i++) {
        result = ((result * ((i + k) % mod) % mod) * (degree(i, mod - 2, mod) % mod)) % mod;
    }
    return result;
}

int main()
{
    int n, k, mod = 1000000007;
    cin >> n >> k;
    if (k < n - k) k = n - k;
    cout << calculateC(n, k, mod);
    return 0;
}
