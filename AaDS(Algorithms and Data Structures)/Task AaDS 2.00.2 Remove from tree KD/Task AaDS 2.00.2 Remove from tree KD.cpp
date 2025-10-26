#include <iostream>
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
		Node* right;
		Node* left;

		Node(T d = T()) : data(d), right(nullptr), left(nullptr) {}
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

	int RightRemoveElem(T key, Node*& current);

	int LeftPreOrderTraversal(Node* current, ofstream& out);

public:
	SearchTree();

	~SearchTree();

	void Clear(Node* current);

	int AddElem(T d);

	int RightRemoveElem(T key);

	int LeftPreOrderTraversal(ofstream& out);
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
int SearchTree<T>::LeftPreOrderTraversal(ofstream& out)
{
	return LeftPreOrderTraversal(root, out);
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
int SearchTree<T>::LeftPreOrderTraversal(Node* current, ofstream& out) {
	if (!current)
		return ReturnSearchTreeCodes::SUCCESS;
	out << current->data << "\n";
	LeftPreOrderTraversal(current->left, out);
	LeftPreOrderTraversal(current->right, out);
	return ReturnSearchTreeCodes::SUCCESS;
}

int main()
{
	SearchTree<int> tree;
	int key, x;
	ifstream in("input.txt");
	if (!in.is_open()) {
		return ReturnMainCodes::INPUT_ERROR;
	}
	in >> key;
	while (in >> x) {
		tree.AddElem(x);
	}
	in.close();

	tree.RightRemoveElem(key);

	ofstream out("output.txt");
	if (!out.is_open()) {
		return ReturnMainCodes::OUTPUT_ERROR;
	}
	tree.LeftPreOrderTraversal(out);
	out.close();

	return ReturnMainCodes::SUCCESS;
}