#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

long long FindMin(queue<long long>& q1, queue<long long>& q2) {
	long long min = 0;

	if (q1.empty()) {
		min = q2.front();
		q2.pop();
		return min;
	}
	if (q2.empty()) {
		min = q1.front();
		q1.pop();
		return min;
	}

	if (q1.front() < q2.front()) {
		min = q1.front();
		q1.pop();
		return min;
	}
	else {
		min = q2.front();
		q2.pop();
		return min;
	}
}

int main()
{
	ifstream in("huffman.in");
	if (!in.is_open())
		return 1;
	int size;
	long long input, unsw = 0, sum;
	in >> size;
	queue<long long> inp;
	queue<long long> nodes;

	while (in >> input)
		inp.push(input);

	in.close();
	for (int i = 0; i < size - 1; i++) {
		sum = FindMin(inp, nodes);
		sum += FindMin(inp, nodes);
		nodes.push(sum);
		unsw += sum;
	}

	ofstream out("huffman.out");
	if (!out.is_open())
		return 1;
	out << unsw;
	out.close();
	return 0;
}