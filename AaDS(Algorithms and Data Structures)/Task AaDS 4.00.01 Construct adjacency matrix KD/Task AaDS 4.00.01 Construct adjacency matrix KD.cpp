#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	if (!in.is_open() || !out.is_open())
		return 1;
	int n, m, x, y;
	in >> n >> m;
	int** matr = new int* [n];
	for (int i = 0; i < n; i++) {
		matr[i] = new int[n] {0};
	}
	while (in >> x >> y) {
		matr[x - 1][y - 1] = 1;
		matr[y - 1][x - 1] = 1;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			out << matr[i][j] << " ";
		out << endl;
	}

	in.close();
	out.close();
	for (int i = 0; i < n; i++)
		delete[] matr[i];
	delete[] matr;
}