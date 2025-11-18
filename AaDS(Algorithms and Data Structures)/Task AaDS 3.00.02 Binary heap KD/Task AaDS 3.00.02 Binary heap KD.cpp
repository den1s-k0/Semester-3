#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	ifstream in("input.txt");
	if (!in.is_open()) {
		return 1;
	}
	int size;
	bool result = true;
	in >> size;
	vector<int> input(size);
	for (int i = 0; i < size; i++) {
		in >> input[i];
		if (input[i] < input[(i - 1) / 2]) {
			result = false;
			break;
		}
	}
	in.close();
	
	ofstream out("output.txt");
	if (!out.is_open()) {
		return 1;
	}
	if (result)
		out << "Yes";
	else
		out << "No";
	out.close();
	return 0;
}
