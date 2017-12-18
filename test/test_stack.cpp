// тесты для стека



#include "stack.h"
#include <gtest.h>


TEST(TestStack, can_Pop_value)
{
	Stack<int> a(30);
	a.Push(9);
	EXPECT_EQ (9, a.Pop());
}

TEST(Stack, can_Peek_value)
{
	Stack<int> a(30);
	a.Push(6);
	EXPECT_EQ (a.Peek(), 6);
}

TEST(Stack, can_Push_newEl)
{
	Stack<int> a(30);
	a.Push(10);
	EXPECT_EQ (a.Peek(),10);
}

TEST(Stack, can_not_Peek_IsEmpty_stack)
{
	Stack<int> a(30);
	ASSERT_ANY_THROW (a.Peek());
}

TEST(Stack, can_not_Pop_IsEmpty_stack)
{
	Stack<int> a(30);
	ASSERT_ANY_THROW (a.Pop());
}


TEST(TestStack, can_check_stack_status)
{
	Stack<int> b(1);
	EXPECT_EQ (b.IsEmpty(), true);
}

TEST(TestStack, can_create_empty_stack)
{
	ASSERT_NO_THROW (Stack<int> b);
}

TEST(TestStack, can_get_Size)
{
	Stack<int> a(30);
	EXPECT_EQ (0, a.GetSize());
}