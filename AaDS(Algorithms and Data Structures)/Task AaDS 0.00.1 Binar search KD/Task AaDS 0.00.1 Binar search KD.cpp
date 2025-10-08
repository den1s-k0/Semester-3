#include <iostream>

using namespace std;

int LowerBound(int* A, int x, int size){
	int start = 0, end = size, middle;
	while (start < end) {
		middle = (start + end) / 2;
		if (A[middle] >= x) {
			end = middle;
		}
		else {
			start = middle + 1;
		}
	}
	return start;
}

int UpperBound(int* A, int x, int size, int LB){
	if (x < A[LB])
		return LB;
	int start = LB, end = size, middle;
	while (start < end) {
		middle = (start + end) / 2;
		if (A[middle] > x) {
			end = middle;
		}
		else {
			start = middle + 1;
		}
	}
	return start;
}

int main()
{
	int n, k, p1, p2;
	bool t;
	cin >> n;
	int* Data = new int[n];
	for (int i = 0; i < n; i++) cin >> Data[i];
	cin >> k;
	int* Wanted = new int[k];
	for (int i = 0; i < k; i++) cin >> Wanted[i];
	cout << endl;
	for (int i = 0; i < k; i++) {
		t = 0;
		p1 = LowerBound(Data, Wanted[i], n);
		if (p1 == n) {
			cout << 0 << ' ' << n << ' ' << n << endl;
		}
		else {
			p2 = UpperBound(Data, Wanted[i], n, p1);
			if (p1 != p2) {
				t = 1;
			}
			cout << t << ' ' << p1 << ' ' << p2 << endl;
		}
	}
 delete[] Data;
 delete[] Wanted;
}
