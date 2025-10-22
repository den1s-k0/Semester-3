#include <iostream>
#include <fstream>

using namespace std;

struct Matr {
	int n;
	int m;
};

int find_min_k_ind(long long** dp, Matr* mat, int i, int j) {
	int ind_k = i;
	long long min_val = dp[i][i] + dp[i + 1][j] + mat[i].n * mat[i].m * mat[j].m;
	for (int k = i; k < j; k++) {
		if (min_val > dp[i][k] + dp[k + 1][j] + mat[i].n * mat[k].m * mat[j].m) {
			min_val = dp[i][k] + dp[k + 1][j] + mat[i].n * mat[k].m * mat[j].m;
			ind_k = k;
		}
	}
	return ind_k;
}

int main()
{
	ifstream in("input.txt");
	if (!in.is_open()) {
		return 1;
	}
	int s, i = 0, j, k;
	in >> s;
	Matr* matrixes = new Matr[s];
	for (int i = 0; i < s; i++) {
		in >> matrixes[i].n >> matrixes[i].m;
	}
	in.close();

	long long** dp = new long long* [s];
	for (int i = 0; i < s - 1; i++) {
		dp[i] = new long long[s] {0};
		dp[i][i] = 0;
		dp[i][i + 1] = matrixes[i].n * matrixes[i].m * matrixes[i + 1].m;
	}
	dp[s - 1] = new long long[s] {0};
	dp[s - 1][s - 1] = 0;

	for(int diag = 2; diag < s; diag++)
		for (int i = 0; i + diag < s; i++) {
			j = i + diag;

			k = find_min_k_ind(dp, matrixes, i, j);
			dp[i][j] = dp[i][k] + dp[k + 1][j] + matrixes[i].n * matrixes[k].m * matrixes[j].m;

		}

	ofstream out("output.txt");
	if (out.is_open()) {
		out << dp[0][s - 1];
	}
	out.close();

	for (int i = 0; i < s; i++) {
		delete[] dp[i];
	}
	delete[] dp;
	delete[] matrixes;
}