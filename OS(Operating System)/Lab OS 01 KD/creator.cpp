#include "header.h"


int main(int argc, char* argv[]) {
	ofstream out(argv[1], ios::binary);
	if (!out.is_open()) {
		cout << "Error\nBinFile isn't create";
		return 1;
	}
	employee tipok;
	for (int i = 0; i < stoi(argv[2]); i++) {
		cin >> tipok;
		out.write(reinterpret_cast<char*>(&tipok), sizeof(employee));
	}
	out.close();
	return 0;
}