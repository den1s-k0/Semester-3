#include <iostream>
#include <fstream>
#include <string>
#include <string_view>

using namespace std;

int find_min_k_ind(int** dp, int i, int j) {
    int ind_k = -1, min_val = 10000;
    for (int k = i + 1; k < j; k++) {
        if (min_val > dp[i][k] + dp[k][j]) {
            min_val = dp[i][k] + dp[k][j];
            ind_k = k;
        }
    }
    return ind_k;
}

bool is_repeat(const string& s, int i, int j, int p) {

    string_view sv(s);
    string_view pattern = sv.substr(i, p);

    for (int r = 1; r < (j - i) / p; r++) {
        string_view segment = sv.substr(i + r * p, p);
        if (pattern != segment) {
            return false;
        }
    }
    return true;
}

int find_best_p(int** dp, const string& s, int i, int j) {
    int candidate_len, min_len = 10000, best_p = -1;
    for (int p = 1; p <= (j - i) / 2; p++) {
        if ((j - i) % p != 0) continue;

        if (is_repeat(s, i, j, p)) {
            candidate_len = to_string((j - i) / p).length() + 2 + dp[i][i + p];
            if (candidate_len < min_len) {
                min_len = candidate_len;
                best_p = p;
            }
        }
    }
    return best_p;
}

int main() {
    string input_str;
    ifstream in("folding.in");
    if (!in.is_open()) {
        return 0;
    }
    getline(in, input_str);
    in.close();

    int n = input_str.length();
    int** dp = new int* [n];
    string** way = new string* [n];

    for (int i = 0; i < n; i++) {
        dp[i] = new int[n + 1]();
        way[i] = new string[n + 1];
    }

    for (int len = 1; len <= n; len++) {
        for (int i = 0; i + len <= n; i++) {
            int j = i + len;

            dp[i][j] = j - i;
            way[i][j] = input_str.substr(i, j - i);

            int k = find_min_k_ind(dp, i, j);
            if (k != -1 && dp[i][k] + dp[k][j] < dp[i][j]) {
                dp[i][j] = dp[i][k] + dp[k][j];
                way[i][j] = way[i][k] + way[k][j];
            }

            int p = find_best_p(dp, input_str, i, j);
            if (p != -1 && to_string(len / p).length() + 2 + dp[i][i + p] < dp[i][j]) {
                way[i][j] = to_string(len / p) + "(" + way[i][i + p] + ")";
                dp[i][j] = way[i][j].length();
            }
        }
    }

    ofstream out("folding.out");
    if (out.is_open()) {
        out << way[0][n];
        out.close();
    }

    for (int i = 0; i < n; i++) {
        delete[] dp[i];
        delete[] way[i];
    }
    delete[] dp;
    delete[] way;

    return 0;
}
