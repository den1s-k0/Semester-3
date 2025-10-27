#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

namespace ReturnMainCodes {
	const int SUCCESS = 0;

	const int INPUT_ERROR = -1;

	const int OUTPUT_ERROR = -2;


}

class SearchTreePrototipe {
public:
	long long key;
	int parent_string_number;
	char RL;
	long long left_border;
	long long right_border;

	SearchTreePrototipe() : key(0), parent_string_number(0), RL('-'), left_border(-2147483650), right_border(2147483650) {}

	SearchTreePrototipe(SearchTreePrototipe* mas, bool& result, int k = 0, int p = 0, char rl = '-'): key(k), parent_string_number(p), RL(rl) {
		if (p != 0) {
			if (RL == 'R') {
				left_border = mas[p - 1].key;
				right_border = mas[p - 1].right_border;
				if(key < left_border || key >= right_border)
					result = false;
			}
			if (RL == 'L') {
				right_border = mas[p - 1].key;
				left_border = mas[p - 1].left_border;
				if (key < left_border || key >= right_border)
					result = false;
			}
		}
		else {
			left_border = -2147483650;
			right_border = 2147483650;
		}

	}
};

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int size, parent;
	long long key, x;
	char rl;
	bool result = true;
	string line;

	ifstream in("bst.in");
	if (!in.is_open()) {
		return ReturnMainCodes::INPUT_ERROR;
	}

	in >> size;
	SearchTreePrototipe* Mas = new SearchTreePrototipe[size];
	in >> x;
	Mas[0] = SearchTreePrototipe(Mas, result, x, 0, '-');

	for (int i = 1; i < size; i++) {
		in >> key >> parent >> rl;
		Mas[i] = SearchTreePrototipe(Mas, result, key, parent, rl);
		if (!result) 
			break;
	}
	in.close();

	ofstream out("bst.out");
	if (!out.is_open()) {
		delete[] Mas;
		return ReturnMainCodes::OUTPUT_ERROR;
	}
	if (result)
		out << "YES";
	else
		out << "NO";
	out.close();

	delete[] Mas;
	return ReturnMainCodes::SUCCESS;
}