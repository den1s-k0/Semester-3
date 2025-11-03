#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int Max(int a, int b) {
	if (a > b)
		return a;
	return b;
}

int main()
{
	ifstream in("input.txt");
	if (!in.is_open())
		return 1;
	string A, B;
	getline(in, A);
	in.close();
	B = A;
	reverse(B.begin(), B.end());
	int n = A.length();
	int** dp = new int* [n + 1];
	for (int i = 0; i < n + 1; i++) {
		dp[i] = new int[n + 1];
		dp[0][i] = 0;
		dp[i][0] = 0;
	}

	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			if (A[i - 1] == B[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else {
				dp[i][j] = Max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	int size = dp[n][n];
	int* path_a = new int[size];
	int* path_b = new int[size];
	size--;
	int iw = n, jw = n;
	while (iw > 0 && jw > 0 && dp[iw][jw]) {
		if (A[iw - 1] == B[jw - 1]) {
			path_a[size] = iw - 1;
			iw--;
			path_b[size] = jw - 1;
			jw--;
			size--;
		}
		else if (dp[iw][jw] == dp[iw][jw - 1]) {
			jw--;
		}
		else if (dp[iw][jw] == dp[iw - 1][jw]) {
			iw--;
		}
	}


	ofstream out("output.txt");
	if (!out.is_open()) {
		for (int i = 0; i < n + 1; i++)
			delete[] dp[i];
		delete[] path_a;
		delete[] path_b;
		return 1;
	}
	out << dp[n][n] << "\n";
	for (int i = 0; i < dp[n][n]; i++)
		out << A[path_a[i]];
	out.close();

	for (int i = 0; i < n + 1; i++)
		delete[] dp[i];
	delete[] path_a;
	delete[] path_b;
	return 0;
}