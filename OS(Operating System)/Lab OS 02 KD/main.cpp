#include "core.h"

int main() {
	int size;
	cin >> size;
	int* Mas = new int[size];
	for (int i = 0; i < size; i++) {
		cin >> Mas[i];
	}

	delete[] Mas;
	return 0;
}