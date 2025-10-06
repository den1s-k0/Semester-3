#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;

int main()
{
	int x;
	vector <int> input;
	long long sum = 0;
	ifstream in("input.txt");
	if (in.is_open()) {
		while (in >> x) {
			input.push_back(x);
		}
	}
	in.close();
	sort(input.begin(), input.end());
	ofstream out("output.txt");
	for (int i = 0; i < input.size() - 1; i++) {
		if (input[i] != input[i + 1]) {
			sum += input[i];
		}
	}
	if (out.is_open()) {
		out << sum + input[input.size() - 1];
	}
	out.close();

	return 0;
}