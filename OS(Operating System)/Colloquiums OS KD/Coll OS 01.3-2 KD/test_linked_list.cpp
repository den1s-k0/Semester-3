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
	A.push_back(1);
	A.push_back(2);
	A.push_back(3);
	A.push_back(4);
	A.push_back(5);
	A.push_back(6);
	A.push_back(7);
	A.push_back(8);
	A.push_back(9);
	A.push_back(10);
	EXPECT_EQ(A.Get_Size(), 10);
	EXPECT_EQ(A[0], 1);
	EXPECT_EQ(A[1], 2);
	EXPECT_EQ(A[2], 3);
	EXPECT_EQ(A[3], 4);
	EXPECT_EQ(A[4], 5);
	EXPECT_EQ(A[5], 6);
	EXPECT_EQ(A[6], 7);
	EXPECT_EQ(A[7], 8);
	EXPECT_EQ(A[8], 9);
	EXPECT_EQ(A[9], 10);
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
	A.push_back(1);
	A.push_back(2);
	A.pop_back();
	A.push_back(3);
	A.push_back(4);
	A.pop_back();
	A.push_back(5);
	A.push_back(6);
	A.pop_back();
	A.push_back(7);
	A.push_back(8);
	A.pop_back();
	A.push_back(9);
	A.push_back(10);
	A.pop_back();
	EXPECT_EQ(A.Get_Size(), 5);
	EXPECT_EQ(A[0], 1);
	EXPECT_EQ(A[1], 3);
	EXPECT_EQ(A[2], 5);
	EXPECT_EQ(A[3], 7);
	EXPECT_EQ(A[4], 9);
}

TEST(PushHeadTests, PushHeadOneIntElem) {
	LinkedList<int> A;
	A.push_head(1);
	EXPECT_EQ(A.Get_Size(), 1);
	EXPECT_EQ(A[0], 1);
}

TEST(PushHeadTests, PushHeadIntElem) {
	LinkedList<int> A;
	A.push_head(1);
	A.push_head(2);
	A.push_head(3);
	A.push_head(4);
	A.push_head(5);
	A.push_head(6);
	A.push_head(7);
	A.push_head(8);
	A.push_head(9);
	A.push_head(10);
	EXPECT_EQ(A.Get_Size(), 10);
	EXPECT_EQ(A[0], 10);
	EXPECT_EQ(A[1], 9);
	EXPECT_EQ(A[2], 8);
	EXPECT_EQ(A[3], 7);
	EXPECT_EQ(A[4], 6);
	EXPECT_EQ(A[5], 5);
	EXPECT_EQ(A[6], 4);
	EXPECT_EQ(A[7], 3);
	EXPECT_EQ(A[8], 2);
	EXPECT_EQ(A[9], 1);
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
	A.push_head(1);
	A.push_head(2);
	A.pop_head();
	A.push_head(3);
	A.push_head(4);
	A.pop_head();
	A.push_head(5);
	A.push_head(6);
	A.pop_head();
	A.push_head(7);
	A.push_head(8);
	A.pop_head();
	A.push_head(9);
	A.push_head(10);
	A.pop_head();
	EXPECT_EQ(A.Get_Size(), 5);
	EXPECT_EQ(A[0], 9);
	EXPECT_EQ(A[1], 7);
	EXPECT_EQ(A[2], 5);
	EXPECT_EQ(A[3], 3);
	EXPECT_EQ(A[4], 1);
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
	A.push_head(1);
	A.push_head(2);
	A.push_head(3);
	A.push_head(4);
	A.push_head(5);
	A.push_head(6);
	A.push_head(7);
	A.push_head(8);
	A.push_head(9);
	A.push_head(10);
	EXPECT_EQ(A.clear(), ReturnLinkedListCodes::SUCCESS);
	EXPECT_EQ(A.Get_Size(), 0);
}