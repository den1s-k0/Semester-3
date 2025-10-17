#include "test_core.h"

void WriteBinFile(string BinFileName, employee testemp) {
	ofstream out(BinFileName, ios::binary);
	if (out.is_open()) {
		testemp.serialize(out);
	}
	out.close();
}