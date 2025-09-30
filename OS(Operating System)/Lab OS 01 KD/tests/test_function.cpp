#include <gtest/gtest.h>
#include "../header.h"

void WriteBinFile(string BinFileName) {
	ofstream out(BinFileName, ios::binary);
	if (out.is_open()) {
		employee testTip;
		out.write(reinterpret_cast<char*>(&testTip), sizeof(employee));
	}
	out.close();
}

void WriteTextFile(string TextFileName) {
	ofstream out(TextFileName);
	if (out.is_open()) {
		employee testTip;
		out << testTip;
	}
	out.close();
}