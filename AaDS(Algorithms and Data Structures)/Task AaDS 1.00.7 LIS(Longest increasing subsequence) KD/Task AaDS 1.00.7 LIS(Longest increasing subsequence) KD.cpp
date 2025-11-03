#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int LowerBound(vector<int>& mas, int x) {
	//if (mas.empty()) return 0;

	int left = 0, right = mas.size(), k;
	while (left < right) {
		k = (left + right) / 2;
		if (x <= mas[k])
			right = k;
		else
			left = k + 1;
	}
	return left;
}

int main()
{
	ifstream in("input.txt");
	if (!in.is_open())
		return 1;
	int size;
	in >> size;
	vector<int> result;
	vector<int> input(size);

	for (int i = 0; i < size; i++) {
		in >> input[i];
		int ind = LowerBound(result, input[i]);
		if (ind == result.size())
			result.push_back(input[i]);
		else
			result[ind] = input[i];
	}
	in.close();


	ofstream out("output.txt");
	if (!out.is_open()) {
		return 1;
	}
	out << result.size();
	out.close();

	return 0;
}