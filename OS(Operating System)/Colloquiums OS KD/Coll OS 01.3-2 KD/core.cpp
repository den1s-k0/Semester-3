#include "core.h"

int ChooseDataType()
{
	int choice;
	cout << "Menu:\n1->int\n2->long long\n3->string\n4->char\n5->bool\n\nEnter your choice: ";
	cin >> choice;
	while (cin.fail() || choice > 5 || choice < 1) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Wrong input\nEnter number from 1 to 5: ";
		cin >> choice;
	}
	return choice;
}

int RunList()
{
	int data_type = ChooseDataType();

	LinkedList<int> list_1;
	LinkedList<long long> list_2;
	LinkedList<string> list_3;
	LinkedList<char> list_4;
	LinkedList<bool> list_5;

	switch(data_type){
		case 1:
			list_1.ListMenu();
			break;
		case 2:
			list_2.ListMenu();
			break;
		case 3:			
			list_3.ListMenu();
			break;
		case 4:
			list_4.ListMenu();
			break;
		case 5:
			list_5.ListMenu();
			break;
		default: 
			return ReturnDataType::WRONG_INPUT;
			break;
	}
	return ReturnLinkedListCodes::SUCCESS;
}




