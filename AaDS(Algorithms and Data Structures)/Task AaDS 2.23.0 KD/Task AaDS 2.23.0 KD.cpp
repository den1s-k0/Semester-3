#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <fstream>

using namespace std;

namespace ReturnMainCodes {
	const int SUCCESS = 0;

	const int INPUT_ERROR = -1;

	const int OUTPUT_ERROR = -2;


}

namespace ReturnSearchTreeCodes {
	const int SUCCESS = 0;

	const int ELEM_IS_ALREADY_EXISTS = 1;

	const int ELEM_ISNT_EXISTS = 2;

	const int NOTHING_WAS_RETURN = -1;

}



template<typename T>
class SearchTree {
private:
	class Node {
	public:
		T data;
		bool isK;
		vector<int> left_ways;
		vector<int> right_ways;
		Node* right;
		Node* left;

		Node(T d = T()) : data(d), isK(false), right(nullptr), left(nullptr) {}
	};
	Node* root;

	int AddElem(T d, Node*& current);

	Node* FindLeftElem(Node* start) {
		Node* current = start;
		while (current && current->left) {
			current = current->left;
		}
		return current;
	}

	Node* FindRightElem(Node* start) {
		Node* current = start;
		while (current && current->right) {
			current = current->right;
		}
		return current;
	}

	int RightRemoveElem(T key, Node*& current);

	int LeftRemoveElem(T key, Node*& current);

	int LeftPreOrderTraversal(Node* current, ofstream& out);

	int CopyPaths(vector<int>& current, Node* to_copy);

	bool IsKWay(vector<int>& leftway, vector<int>& rightway, int k);

	int LeftPostOrderTraversal(Node* current, int k);

	vector<T> FindAllKBFS(Node* root);

	void Problem(Node* root, int k, ofstream& out);

public:
	SearchTree();

	~SearchTree();

	void Clear(Node* current);

	int AddElem(T d);

	int RightRemoveElem(T key);

	int LeftRemoveElem(T key);

	int LeftPreOrderTraversal(ofstream& out);

	int LeftPostOrderTraversal(int k);

	vector<T> FindAllKBFS();

	void Problem(int k, ofstream& out);

};

template<typename T>
SearchTree<T>::SearchTree() {
	root = nullptr;
}

template<typename T>
SearchTree<T>::~SearchTree() {
	Clear(root);
}

template<typename T>
void SearchTree<T>::Clear(Node* current) {
	if (current) {
		Clear(current->left);
		Clear(current->right);
		delete current;
	}
}

template<typename T>
int SearchTree<T>::AddElem(T d)
{
	return AddElem(d, root);
}

template<typename T>
int SearchTree<T>::RightRemoveElem(T key)
{
	return RightRemoveElem(key, root);
}

template<typename T>
int SearchTree<T>::LeftRemoveElem(T key)
{
	return LeftRemoveElem(key, root);
}

template<typename T>
int SearchTree<T>::LeftPreOrderTraversal(ofstream& out)
{
	return LeftPreOrderTraversal(root, out);
}

template<typename T>
int SearchTree<T>::LeftPostOrderTraversal(int k)
{
	return LeftPostOrderTraversal(root, k);
}

template<typename T>
vector<T> SearchTree<T>::FindAllKBFS()
{
	return FindAllKBFS(root);
}

template<typename T>
void SearchTree<T>::Problem(int k, ofstream& out)
{
	Problem(root, k, out);
}

template<typename T>
int SearchTree<T>::AddElem(T d, Node*& current) {
	if (!current) {
		current = new Node(d);
		return ReturnSearchTreeCodes::SUCCESS;
	}
	if (d > current->data)
		return AddElem(d, current->right);
	if (d < current->data)
		return AddElem(d, current->left);
	if (d == current->data)
		return ReturnSearchTreeCodes::ELEM_IS_ALREADY_EXISTS;
	return ReturnSearchTreeCodes::NOTHING_WAS_RETURN;
}

template<typename T>
int SearchTree<T>::RightRemoveElem(T key, Node*& current)
{
	if (!current)
		return ReturnSearchTreeCodes::ELEM_ISNT_EXISTS;
	if (key > current->data)
		return RightRemoveElem(key, current->right);
	if (key < current->data)
		return RightRemoveElem(key, current->left);
	if (key == current->data) {
		Node* C = current;
		if (!C->left && !C->right) {
			delete current;
			current = nullptr;
			return ReturnSearchTreeCodes::SUCCESS;
		}
		if (!C->left) {
			C = current->right;
			delete current;
			current = C;
			return ReturnSearchTreeCodes::SUCCESS;
		}
		if (!C->right) {
			C = current->left;
			delete current;
			current = C;
			return ReturnSearchTreeCodes::SUCCESS;
		}
		if (C->left && C->right) {
			Node* C = FindLeftElem(current->right);
			current->data = C->data;
			return RightRemoveElem(C->data, current->right);
		}
	}
	return ReturnSearchTreeCodes::NOTHING_WAS_RETURN;
}

template<typename T>
int SearchTree<T>::LeftRemoveElem(T key, Node*& current)
{
	if (!current)
		return ReturnSearchTreeCodes::ELEM_ISNT_EXISTS;
	if (key > current->data)
		return LeftRemoveElem(key, current->right);
	if (key < current->data)
		return LeftRemoveElem(key, current->left);
	if (key == current->data) {
		Node* C = current;
		if (!C->left && !C->right) {
			delete current;
			current = nullptr;
			return ReturnSearchTreeCodes::SUCCESS;
		}
		if (!C->left) {
			C = current->right;
			delete current;
			current = C;
			return ReturnSearchTreeCodes::SUCCESS;
		}
		if (!C->right) {
			C = current->left;
			delete current;
			current = C;
			return ReturnSearchTreeCodes::SUCCESS;
		}
		if (C->left && C->right) {
			Node* C = FindRightElem(current->left);
			current->data = C->data;
			return LeftRemoveElem(C->data, current->left);
		}
	}
	return ReturnSearchTreeCodes::NOTHING_WAS_RETURN;
}

template<typename T>
int SearchTree<T>::LeftPreOrderTraversal(Node* current, ofstream& out) {
	if (!current)
		return ReturnSearchTreeCodes::SUCCESS;
	out << current->data << "\n";
	LeftPreOrderTraversal(current->left, out);
	LeftPreOrderTraversal(current->right, out);
	return ReturnSearchTreeCodes::SUCCESS;
}

template<typename T>
int SearchTree<T>::CopyPaths(vector<int>& current, Node* to_copy)
{
	if (to_copy->left && to_copy->right) {
		current.resize(to_copy->left_ways.size() + to_copy->right_ways.size());
		int il = 0, ir = 0;

		for (int i = 0; i < current.size(); i++) {
			if (il < to_copy->left_ways.size() && ir == to_copy->right_ways.size() || 
				il < to_copy->left_ways.size() && ir < to_copy->right_ways.size() && to_copy->left_ways[il] < to_copy->right_ways[ir]) {
				current[i] = to_copy->left_ways[il];
				il++;
			}
			else {
				current[i] = to_copy->right_ways[ir];
				ir++;
			}
			current[i]++;
		}
	}
	else if (to_copy->left) {
		current = to_copy->left_ways;
		for (int i = 0; i < current.size(); i++)
			current[i]++;
	}
	else if (to_copy->right) {
		current = to_copy->right_ways;
		for (int i = 0; i < current.size(); i++)
			current[i]++;
	}
	else {
		current.push_back(1);
	}
	return ReturnSearchTreeCodes::SUCCESS;
}

template<typename T>
bool SearchTree<T>::IsKWay(vector<int>& leftway, vector<int>& rightway, int k)
{
	if(leftway[0] == 0 || rightway[0] == 0)
		return false;
	map<int, int> M;
	for (int i = 0; i < rightway.size() && rightway[i] < k; i++)
		M[rightway[i]] = i;
	for (int i = 0; i < leftway.size() && leftway[i] < k; i++)
		if (M.count(k - leftway[i]) == 1)
			return true;
	return false;
}

template<typename T>
int SearchTree<T>::LeftPostOrderTraversal(Node* current, int k)
{
	if (!current)
		return ReturnSearchTreeCodes::SUCCESS;
	LeftPostOrderTraversal(current->left, k);
	LeftPostOrderTraversal(current->right, k);

	if (current->left)
		CopyPaths(current->left_ways, current->left);
	if (current->right)
		CopyPaths(current->right_ways, current->right);
	if (current->left && current->right)
		current->isK = IsKWay(current->left_ways, current->right_ways, k);
	return ReturnSearchTreeCodes::SUCCESS;
}

template<typename T>
vector<T> SearchTree<T>::FindAllKBFS(Node* root)
{
	queue<Node*> q;
	vector<T> result;
	bool is_find = false;
	Node* current;
	int count;
	q.push(root);
	while (!q.empty() && !is_find) {
		count = q.size();
		for (int i = 0; i < count; i++) {
			current = q.front();
			q.pop();
			if (current->isK) {
				result.push_back(current->data);
				is_find = true;
			}
			if (current->left)
				q.push(current->left);
			if (current->right)
				q.push(current->right);
		}
	}
	return result;
}

template<typename T>
void SearchTree<T>::Problem(Node* root, int k, ofstream& out)
{
	LeftPostOrderTraversal(k);
	vector<T> mas = FindAllKBFS();
	if (mas.size() % 2 == 1) {
		sort(begin(mas), end(mas));
		LeftRemoveElem(mas[mas.size() / 2]);
	}
	LeftPreOrderTraversal(out);
}



int main()
{
	ifstream in("in.txt");
	ofstream out("out.txt");
	if (!in.is_open() || !out.is_open())
		return 1;
	SearchTree<int> tree;
	int k, x;
	in >> k;
	while (in >> x)
		tree.AddElem(x);
	tree.Problem(k, out);
	in.close();
	out.close();
	return 0;
}
