#pragma once

#include <iostream>
#include <stdlib.h>

namespace ReturnLinkedListCodes{

	const int SUCCESS = 0;

	const int WRONG_INDEX = -1;

	const int HEAD_ISNT_EXIST = -2;

	const int ERROR_POP_BACK = -3;

	const int ERROR_PUSH_BACK = -4;
}

using namespace std;

template<typename T>
class LinkedList {
	template<typename T>
	class Node {
	public:
		Node* pnext;
		T data;
		Node(T data = T(), Node* pnext = nullptr) {
			this->data = data;
			this->pnext = pnext;
		}
	};
	Node<T>* head;
	int size;


public:
	LinkedList();
	~LinkedList();

	void swap_node(Node<T>* A, Node<T>* B);
	int push_back(T data);
	int push_head(T data);
	int push_ind(T data, const int index);
	int pop_back();
	int pop_head();
	int pop_ind(const int index);
	int clear();
	int Get_Size() { return size; }
	T& operator[](const int index);
	int print();
	int reverse();
	int ListMenu();
};

template<typename T>
void LinkedList<T>::swap_node(Node<T>* A, Node<T>* B) {
	Node<T>* prevA = nullptr;
	Node<T>* prevB = nullptr;
	Node<T>* current = head;

	while (current) {
		if (current->pnext == A) prevA = current;
		if (current->pnext == B) prevB = current;
		current = current->pnext;
	}

	if (A == head) head = B;
	else if (B == head) head = A;

	if (A->pnext == B) {
		prevA->pnext = B;
		A->pnext = B->pnext;
		B->pnext = A;
	}
	else if (B->pnext == A) {
		prevB->pnext = A;
		B->pnext = A->pnext;
		A->pnext = B;
	}
	else {
		prevA->pnext = B;
		prevB->pnext = A;
		current = B->pnext;
		B->pnext = A->pnext;
		A->pnext = current;
	}
}

template<typename T>
LinkedList<T>::LinkedList() {
	size = 0;
	head = nullptr;
}

template<typename T>
LinkedList<T>::~LinkedList() {
	Node<T>* current = head;
	Node<T>* next;
	while (current != nullptr) {
		next = current->pnext;
		delete current;
		current = next;
	}
}

template<typename T>
int LinkedList<T>::push_back(T data) {
	if (head) {
		Node<T>* current = head;
		while (current->pnext)
			current = current->pnext;
		if (current->pnext == nullptr) {
			current->pnext = new Node<T>(data);
			size++;
			return ReturnLinkedListCodes::SUCCESS;
		}
		return ReturnLinkedListCodes::ERROR_PUSH_BACK;
	}
	else {
		head = new Node<T>(data);
		size++;
		return ReturnLinkedListCodes::SUCCESS;
	}
}

template<typename T>
int LinkedList<T>::push_head(T data) {
	head = new Node<T>(data, head);
	size++;
	return ReturnLinkedListCodes::SUCCESS;
}

template<typename T>
int LinkedList<T>::push_ind(T data, const int index) {
	if (index == 0)
		return push_head(data);
	if (index == size)
		return push_back(data);
	if (index < 0 || index > size)
		return ReturnLinkedListCodes::WRONG_INDEX;

	Node<T>* current = head;
	for(int i = 0; i < index - 1; i++)
		current = current->pnext;
	current->pnext = new Node<T>(data, current->pnext);
	size++;
	return ReturnLinkedListCodes::SUCCESS;
}

template<typename T>
int LinkedList<T>::pop_back() {
	if (head) {
		if (size == 1) {
			delete head;
			head = nullptr;
			size--;
			return ReturnLinkedListCodes::SUCCESS;
		}
		Node<T>* current = head;
		while (current->pnext->pnext)
			current = current->pnext;
		if (current->pnext->pnext == nullptr) {
			delete current->pnext;
			current->pnext = nullptr;
			size--;
			return ReturnLinkedListCodes::SUCCESS;
		}
		return ReturnLinkedListCodes::ERROR_POP_BACK;
	}
	else 
		return ReturnLinkedListCodes::HEAD_ISNT_EXIST;
}

template<typename T>
int LinkedList<T>::pop_head() {
	if (head) {
		Node<T>* current = head;
		head = head->pnext;
		delete current;
		size--;
		return ReturnLinkedListCodes::SUCCESS;
	}
	else
		return ReturnLinkedListCodes::HEAD_ISNT_EXIST;
}

template<typename T>
int LinkedList<T>::pop_ind(const int index) {
	if (index == 0)
		return pop_head();
	if (index == size - 1)
		return pop_back();
	if (index < 0 || index >= size)
		return ReturnLinkedListCodes::WRONG_INDEX;

	Node<T>* current = head;
	Node<T>* next;
	for (int i = 0; i < index - 1; i++)
		current = current->pnext;
	next = current->pnext->pnext;
	delete current->pnext;
	current->pnext = next;
	size--;
	return ReturnLinkedListCodes::SUCCESS;
}

template<typename T>
int LinkedList<T>::clear() {
	while (size) {
		pop_head();
	}
	return ReturnLinkedListCodes::SUCCESS;
}

template<typename T>
T& LinkedList<T>::operator[](const int index)
{
	if (index < 0 || index >= size) {
		throw out_of_range("Index out of range");
	}

	Node<T>* current = head;
	for (int i = 0; i < index; i++) {
		current = current->pnext;
	}
	return current->data;
}

template<typename T>
int LinkedList<T>::print()
{
	Node<T>* current = head;
	cout << "List:\n";
	for (int i = 0; i < size; i++) {
		cout << i << ": " << current->data << "\n";
		current = current->pnext;
	}
	return ReturnLinkedListCodes::SUCCESS;
}

template<typename T>
int LinkedList<T>::reverse()
{
	if (head) {
		Node<T>* current = head;
		Node<T>* next = nullptr;
		Node<T>* prev = nullptr;
		while (current->pnext) {
			next = current->pnext;
			current->pnext = prev;
			prev = current;
			current = next;
		}
		current->pnext = prev;
		head = current;
		return ReturnLinkedListCodes::SUCCESS;
	}
	else
		return ReturnLinkedListCodes::HEAD_ISNT_EXIST;
}

template<typename T>
int LinkedList<T>::ListMenu() {
	int choice, ind;
	T input;
	do {
		system("CLS");
		cout << "Menu:\n";
		cout << "0->Close\n";
		cout << "1->Add to the end\n";
		cout << "2->Add to the start\n";
		cout << "3->Add to the selected position\n";
		cout << "4->Delete the end\n";
		cout << "5->Delete the start\n";
		cout << "6->Delete the selected position\n";
		cout << "7->Clear the list\n";
		cout << "8->Get list size\n";
		cout << "9->Print the list\n";
		cout << "10->Reverse the list\n";
		cout << "Enter your choice: ";
		cin >> choice;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Wrong input\nEnter number from 0 to 10: ";
			cin >> choice;
		}

		switch (choice) {
		case 0:
			break;
		case 1:
			cout << "\nEnter the data: ";
			cin >> input;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Wrong input\nEnter the data: ";
				cin >> input;
			}
			push_back(input);
			break;
		case 2:
			cout << "\nEnter the data: ";
			cin >> input;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Wrong input\nEnter the data: ";
				cin >> input;
			}
			push_head(input);
			break;
		case 3: {
			cout << "\nEnter the data: ";
			cin >> input;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Wrong input\nEnter the data: ";
				cin >> input;
			}
			cout << "\nEnter the index: ";
			cin >> ind;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Wrong input\nEnter the index: ";
				cin >> ind;
			}
			push_ind(input, ind);
			break;
		}
		case 4:
			pop_back();
			break;
		case 5:
			pop_head();
			break;
		case 6: {
			cout << "\nEnter the index: ";
			cin >> ind;
			while (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Wrong input\nEnter the index: ";
				cin >> ind;
			}
			pop_ind(ind);
			break;
		}
		case 7:
			clear();
			break;
		case 8:
			cout << "Size: " << Get_Size();
			break;
		case 9:
			print();
			system("pause");
			break;
		case 10:
			reverse();
			break;
		default:
			break;
		}
	} while (choice != 0);

	return ReturnLinkedListCodes::SUCCESS;
}
