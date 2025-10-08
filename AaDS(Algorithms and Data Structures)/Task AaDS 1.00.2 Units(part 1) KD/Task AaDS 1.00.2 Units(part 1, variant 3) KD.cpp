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
    if (k == 0 || k == n) {
        return 1;
    }
    else {
        return ((((calculateC(n - 1, k - 1, mod) % mod) * (n % mod)) % mod) * degree(k, mod - 2, mod)) % mod;
    }
}

int main()
{
    int n, k, mod = 1000000007;
    cin >> n >> k;
    cout << calculateC(n, k, mod);
    return 0;
}
