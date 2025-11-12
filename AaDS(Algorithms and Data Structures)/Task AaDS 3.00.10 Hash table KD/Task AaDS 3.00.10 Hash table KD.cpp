#include <iostream>
#include <fstream>

using namespace std;

void AddToHashTable(int* mas, bool* f_mas, int m, int c, int x) {
	int h, base = x % m;
	for (int i = 0; i < m; i++) {
		h = (base + c * i) % m;
		if (!f_mas[h]) {
			mas[h] = x;
			f_mas[h] = true;
			break;
		}
		if (mas[h] == x)
			break;
	}
}

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	if (!in.is_open() || !out.is_open())
		return 1;
	int m, c, n, x;
	in >> m >> c >> n;
	int* mas = new int[m];
	bool* f_mas = new bool[m] {};
	for (int i = 0; i < n; i++) {
		in >> x;
		AddToHashTable(mas, f_mas, m, c, x);
	}

	for (int i = 0; i < m; i++) {
		if (f_mas[i] == false)
			out << -1 << ' ';
		else
			out << mas[i] << ' ';
	}
	in.close();
	out.close();
	delete[] mas;
	delete[] f_mas;
	return 0;
}
