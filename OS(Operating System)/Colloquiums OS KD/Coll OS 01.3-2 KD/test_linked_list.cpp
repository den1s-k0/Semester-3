#include "test_linked_list.h"

TEST(LinkedListTests, DefaultIntConstructor) {
	LinkedList<int> A;
	EXPECT_EQ(A.Get_Size(), 0);
}

TEST(PushBackTests, PushBackOneIntElem) {
	LinkedList<int> A;
	A.push_back(1);
	EXPECT_EQ(A.Get_Size(), 1);
	EXPECT_EQ(A[0], 1);
}

TEST(PushBackTests, PushBackIntElem) {
	LinkedList<int> A;
	for (int i = 0; i < 10; i++)
		A.push_back(i);
	EXPECT_EQ(A.Get_Size(), 10);
	for (int i = 0; i < 10; i++)
		EXPECT_EQ(A[i], i);
}

TEST(PopBackTests, PopBackZeroIntElem) {
	LinkedList<int> A;
	EXPECT_EQ(A.pop_back(), ReturnLinkedListCodes::HEAD_ISNT_EXIST);
	EXPECT_EQ(A.Get_Size(), 0);
}

TEST(PopBackTests, PopBackOneIntElem) {
	LinkedList<int> A;
	A.push_back(1);
	A.pop_back();
	EXPECT_EQ(A.Get_Size(), 0);
}

TEST(PopBackTests, PopBackIntElem) {
	LinkedList<int> A;
	for (int i = 1; i < 11; i++) {
		A.push_back(i);
		i++;
		A.push_back(i);
		A.pop_back();
	}
	EXPECT_EQ(A.Get_Size(), 5);
	for (int i = 0; i < A.Get_Size(); i++) {
		EXPECT_EQ(A[i], 2 * i + 1);
	}
}

TEST(PushHeadTests, PushHeadOneIntElem) {
	LinkedList<int> A;
	A.push_head(1);
	EXPECT_EQ(A.Get_Size(), 1);
	EXPECT_EQ(A[0], 1);
}

TEST(PushHeadTests, PushHeadIntElem) {
	LinkedList<int> A;
	for (int i = 1; i < 11; i++)
		A.push_head(i);
	EXPECT_EQ(A.Get_Size(), 10);
	for (int i = 0; i < 10; i++)
		EXPECT_EQ(A[i], A.Get_Size() - i);
}

TEST(PopHeadTests, PopHeadZeroIntElem) {
	LinkedList<int> A;
	EXPECT_EQ(A.pop_head(), ReturnLinkedListCodes::HEAD_ISNT_EXIST);
	EXPECT_EQ(A.Get_Size(), 0);
}

TEST(PopHeadTests, PopHeadOneIntElem) {
	LinkedList<int> A;
	A.push_head(1);
	A.pop_head();
	EXPECT_EQ(A.Get_Size(), 0);
}

TEST(PopHeadTests, PopHeadIntElem) {
	LinkedList<int> A;
	for (int i = 1; i < 11; i++) {
		A.push_head(i);
		i++;
		A.push_head(i);
		A.pop_head();
	}
	EXPECT_EQ(A.Get_Size(), 5);
	for (int i = 0; i < A.Get_Size(); i++) {
		EXPECT_EQ(A[i], 2 * A.Get_Size() - (2 * i + 1));
	}
}

TEST(PushIndTests, PushWrongIndOneIntElem) {
	LinkedList<int> A;
	
	EXPECT_EQ(A.push_ind(1, 10), ReturnLinkedListCodes::WRONG_INDEX);
	EXPECT_EQ(A.Get_Size(), 0);
}

TEST(PushIndTests, PushIndOneIntElem) {
	LinkedList<int> A;
	A.push_ind(1, 0);
	EXPECT_EQ(A.Get_Size(), 1);
	EXPECT_EQ(A[0], 1);
}

TEST(PushIndTests, PushWrongIndIntElem) {
	LinkedList<int> A;
	A.push_ind(1, 0);
	A.push_ind(2, 0);
	A.push_ind(3, 1);
	A.push_ind(4, 1);
	A.push_ind(5, 2);
	A.push_ind(6, 2);
	A.push_ind(7, 3);
	A.push_ind(8, 3);
	A.push_ind(9, 4);
	A.push_ind(10, 4);
	EXPECT_EQ(A.push_ind(1, -7), ReturnLinkedListCodes::WRONG_INDEX);
	EXPECT_EQ(A.push_ind(1, 13), ReturnLinkedListCodes::WRONG_INDEX);
	EXPECT_EQ(A.push_ind(1, 24), ReturnLinkedListCodes::WRONG_INDEX);
	EXPECT_EQ(A.push_ind(1, 100), ReturnLinkedListCodes::WRONG_INDEX);
	EXPECT_EQ(A.push_ind(1, 125), ReturnLinkedListCodes::WRONG_INDEX);
	EXPECT_EQ(A.push_ind(1, -99), ReturnLinkedListCodes::WRONG_INDEX);
	EXPECT_EQ(A.Get_Size(), 10);
	EXPECT_EQ(A[0], 2);
	EXPECT_EQ(A[1], 4);
	EXPECT_EQ(A[2], 6);
	EXPECT_EQ(A[3], 8);
	EXPECT_EQ(A[4], 10);
	EXPECT_EQ(A[5], 9);
	EXPECT_EQ(A[6], 7);
	EXPECT_EQ(A[7], 5);
	EXPECT_EQ(A[8], 3);
	EXPECT_EQ(A[9], 1);
}

TEST(PushIndTests, PushIndIntElem) {
	LinkedList<int> A;
	A.push_ind(1, 0);
	A.push_ind(2, 0);
	A.push_ind(3, 1);
	A.push_ind(4, 1);
	A.push_ind(5, 2);
	A.push_ind(6, 2);
	A.push_ind(7, 3);
	A.push_ind(8, 3);
	A.push_ind(9, 4);
	A.push_ind(10, 4);
	EXPECT_EQ(A.Get_Size(), 10);
	EXPECT_EQ(A[0], 2);
	EXPECT_EQ(A[1], 4);
	EXPECT_EQ(A[2], 6);
	EXPECT_EQ(A[3], 8);
	EXPECT_EQ(A[4], 10);
	EXPECT_EQ(A[5], 9);
	EXPECT_EQ(A[6], 7);
	EXPECT_EQ(A[7], 5);
	EXPECT_EQ(A[8], 3);
	EXPECT_EQ(A[9], 1);
}

TEST(PopIndTests, PopWrongIndZeroIntElem) {
	LinkedList<int> A;
	EXPECT_EQ(A.pop_ind(10), ReturnLinkedListCodes::WRONG_INDEX);
	EXPECT_EQ(A.Get_Size(), 0);
}

TEST(PopIndTests, PopIndZeroIntElem) {
	LinkedList<int> A;
	EXPECT_EQ(A.pop_ind(0), ReturnLinkedListCodes::HEAD_ISNT_EXIST);
	EXPECT_EQ(A.Get_Size(), 0);
}

TEST(PopIndTests, PopWrongIndOneIntElem) {
	LinkedList<int> A;
	A.push_ind(1, 0);
	EXPECT_EQ(A.pop_ind(10), ReturnLinkedListCodes::WRONG_INDEX);
	EXPECT_EQ(A.Get_Size(), 1);
}

TEST(PopIndTests, PopIndOneIntElem) {
	LinkedList<int> A;
	A.push_ind(1, 0);
	A.pop_ind(0);
	EXPECT_EQ(A.Get_Size(), 0);
}

TEST(PopIndTests, PopIndIntElem) {
	LinkedList<int> A;
	A.push_ind(1, 0);
	A.push_ind(2, 0);
	A.push_ind(3, 1);
	A.push_ind(4, 1);
	A.push_ind(5, 2);
	A.push_ind(6, 2);
	A.push_ind(7, 3);
	A.push_ind(8, 3);
	A.push_ind(9, 4);
	A.push_ind(10, 4);
	A.pop_ind(9);
	A.pop_ind(7);
	A.pop_ind(5);
	A.pop_ind(3);
	A.pop_ind(1);
	EXPECT_EQ(A.Get_Size(), 5);
	EXPECT_EQ(A[0], 2);
	EXPECT_EQ(A[1], 6);
	EXPECT_EQ(A[2], 10);
	EXPECT_EQ(A[3], 7);
	EXPECT_EQ(A[4], 3);
}

TEST(ClearTest, ClearZeroIntElem) {
	LinkedList<int> A;
	EXPECT_EQ(A.clear(), ReturnLinkedListCodes::SUCCESS);
	EXPECT_EQ(A.Get_Size(), 0);
}

TEST(ClearTest, ClearOneIntElem) {
	LinkedList<int> A;
	A.push_head(1);
	EXPECT_EQ(A.clear(), ReturnLinkedListCodes::SUCCESS);
	EXPECT_EQ(A.Get_Size(), 0);
}

TEST(ClearTest, ClearIntElem) {
	LinkedList<int> A;
	for (int i = 0; i < 10; i++)
		A.push_head(i);
	EXPECT_EQ(A.clear(), ReturnLinkedListCodes::SUCCESS);
	EXPECT_EQ(A.Get_Size(), 0);
}

TEST(PrintTest, PrintZeroIntElem) {
	LinkedList<int> A;
	testing::internal::CaptureStdout();
	EXPECT_EQ(A.print(), ReturnLinkedListCodes::SUCCESS);
	string output = testing::internal::GetCapturedStdout();
	EXPECT_TRUE(output.find("List:\n") != string::npos);
}

TEST(PrintTest, PrintOneIntElem) {
	LinkedList<int> A;
	A.push_back(1);
	testing::internal::CaptureStdout();
	EXPECT_EQ(A.print(), ReturnLinkedListCodes::SUCCESS);
	string output = testing::internal::GetCapturedStdout();
	EXPECT_TRUE(output.find("List:\n") != string::npos);
	EXPECT_TRUE(output.find("0: " + to_string(A[0])) != string::npos);
}

TEST(PrintTest, PrintIntElem) {
	LinkedList<int> A;
	for (int i = 0; i < 10; i++)
		A.push_back(i);
	testing::internal::CaptureStdout();
	EXPECT_EQ(A.print(), ReturnLinkedListCodes::SUCCESS);
	string output = testing::internal::GetCapturedStdout();
	EXPECT_TRUE(output.find("List:\n") != string::npos);
	for(int i = 0; i < 10; i++)
		EXPECT_TRUE(output.find(to_string(i) + ": " + to_string(A[i])) != string::npos);
}

TEST(ReverseTest, ReverseZeroIntElem) {
	LinkedList<int> A;
	EXPECT_EQ(A.reverse(), ReturnLinkedListCodes::HEAD_ISNT_EXIST);
	EXPECT_EQ(A.Get_Size(), 0);
}

TEST(ReverseTest, ReverseOneIntElem) {
	LinkedList<int> A;
	A.push_head(1);
	EXPECT_EQ(A.reverse(), ReturnLinkedListCodes::SUCCESS);
	EXPECT_EQ(A.Get_Size(), 1);
	EXPECT_EQ(A[0], 1);
}

TEST(ReverseTest, ReverseIntElem) {
	LinkedList<int> A;
	for (int i = 0; i < 10; i++)
		A.push_head(i);
	EXPECT_EQ(A.reverse(), ReturnLinkedListCodes::SUCCESS);
	EXPECT_EQ(A.Get_Size(), 10);
	for (int i = 0; i < 10; i++)
		EXPECT_EQ(A[i], i);
}
