#include "creator.h"


int main(int argc, char* argv[]) {
	ofstream out(argv[1], ios::binary);
	if (!out.is_open()) {
		cerr << "Error\nBinFile isn't create";
		return 1;
	}
	employee tipok;
	for (int i = 0; i < stoi(argv[2]); i++) {
		cin >> tipok;
		tipok.serialize(out);
	}
	out.close();
	return 0;
}