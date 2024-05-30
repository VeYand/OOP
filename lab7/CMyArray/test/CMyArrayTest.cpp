#include <gtest/gtest.h>
#include "../include/CMyArray.h"

TEST(CMyArrayTest, EmptyArray)
{
	CMyArray<int> array;
	EXPECT_EQ(array.Size(), 0);
	EXPECT_EQ(array.Capacity(), 0);
}

TEST(CMyArrayTest, CapacityConstructor)
{
	CMyArray<int> array(10);
	EXPECT_EQ(array.Size(), 0);
	EXPECT_EQ(array.Capacity(), 10);
	array.Add(7);
	EXPECT_EQ(array.Size(), 1);
	EXPECT_EQ(array.Capacity(), 10);
}

TEST(CMyArrayTest, StringArray)
{
	CMyArray<std::string> array;
	array.Add("Hello");
	array.Add("World");
	EXPECT_EQ(array.Size(), 2);
	EXPECT_EQ(array.Capacity(), 2);
	EXPECT_EQ(array[0], "Hello");
	EXPECT_EQ(array[1], "World");
}

TEST(CMyArrayTest, DoubleArray)
{
	CMyArray<double> array;
	array.Add(3.14);
	array.Add(2.71);
	EXPECT_EQ(array.Size(), 2);
	EXPECT_EQ(array.Capacity(), 2);
	EXPECT_DOUBLE_EQ(array[0], 3.14);
	EXPECT_DOUBLE_EQ(array[1], 2.71);
}

TEST(CMyArrayTest, ClearAndAccess)
{
	CMyArray<int> array;
	array.Add(1);
	array.Add(2);
	array.Clear();

	EXPECT_EQ(array.Size(), 0);
	EXPECT_EQ(array.Capacity(), 2);

	EXPECT_THROW(array[0], std::out_of_range);

	array.Add(3);

	EXPECT_EQ(array.Size(), 1);
	EXPECT_EQ(array[0], 3);
}

TEST(CMyArrayTest, OutOfRangeOperator)
{
	CMyArray<int> array;
	array.Add(1);
	EXPECT_NO_THROW(array[0]);
	EXPECT_THROW(array[1], std::out_of_range);
}

TEST(CMyArrayTest, AddElementToArray)
{
	CMyArray<int> array;
	array.Add(42);
	EXPECT_EQ(array.Size(), 1);
	EXPECT_EQ(array.Capacity(), 1);
	EXPECT_EQ(array[0], 42);
}


TEST(CMyArrayTest, CopyConstructor)
{
	CMyArray<int> array;
	array.Add(1);
	array.Add(2);
	CMyArray<int> copyArray = array;
	EXPECT_EQ(copyArray.Size(), 2);
	EXPECT_EQ(copyArray[0], 1);
	EXPECT_EQ(copyArray[1], 2);
}

TEST(CMyArrayTest, AssignmentOperator)
{
	CMyArray<int> array;
	array.Add(1);
	array.Add(2);
	CMyArray<int> assignArray;
	assignArray = array;
	EXPECT_EQ(assignArray.Size(), 2);
	EXPECT_EQ(assignArray[0], 1);
	EXPECT_EQ(assignArray[1], 2);
}

TEST(CMyArrayTest, AssignmentOperatorSelfAssigment)
{
	CMyArray<int> array;
	array.Add(1);
	array.Add(2);
	array = array;
	EXPECT_EQ(array.Size(), 2);
	EXPECT_EQ(array[0], 1);
	EXPECT_EQ(array[1], 2);
}

TEST(CMyArrayTest, MoveConstructor)
{
	CMyArray<int> array;
	array.Add(1);
	array.Add(2);
	CMyArray<int> newArray = std::move(array);
	EXPECT_EQ(newArray.Size(), 2);
	EXPECT_EQ(newArray[0], 1);
	EXPECT_EQ(newArray[1], 2);
	EXPECT_EQ(array.Size(), 0);
	EXPECT_THROW(array[0], std::out_of_range);
}

TEST(CMyArrayTest, MoveOperator)
{
	CMyArray<int> array;
	array.Add(1);
	array.Add(2);
	CMyArray<int> assignArray;
	assignArray = array;
	EXPECT_EQ(assignArray.Size(), 2);
	EXPECT_EQ(assignArray[0], 1);
	EXPECT_EQ(assignArray[1], 2);
}

TEST(CMyArrayTest, MoveOperatorSelfMove)
{
	CMyArray<int> array;
	array.Add(1);
	array.Add(2);
	array = std::move(array);
	EXPECT_EQ(array.Size(), 2);
	EXPECT_EQ(array[0], 1);
	EXPECT_EQ(array[1], 2);
}

TEST(CMyArrayTest, BeginEndIterator)
{
	CMyArray<int> array;
	array.Add(1);
	array.Add(2);
	array.Add(3);

	auto it = array.begin();
	EXPECT_EQ(*it, 1);
	++it;
	EXPECT_EQ(*it, 2);
	++it;
	EXPECT_EQ(*it, 3);
	++it;
	EXPECT_EQ(it, array.end());
}

TEST(CMyArrayTest, ConstBeginEndIterator)
{
	CMyArray<int> array;
	array.Add(1);
	array.Add(2);
	array.Add(3);

	const CMyArray<int>& constArray = array;
	auto it = constArray.begin();
	EXPECT_EQ(*it, 1);
	++it;
	EXPECT_EQ(*it, 2);
	++it;
	EXPECT_EQ(*it, 3);
	++it;
	EXPECT_EQ(it, constArray.end());
}

TEST(CMyArrayTest, ReverseIterator)
{
	CMyArray<int> array;
	array.Add(1);
	array.Add(2);
	array.Add(3);

	auto rit = array.rbegin();
	EXPECT_EQ(*rit, 3);
	++rit;
	EXPECT_EQ(*rit, 2);
	++rit;
	EXPECT_EQ(*rit, 1);
	++rit;
	EXPECT_EQ(rit, array.rend());
}

TEST(CMyArrayTest, ConstReverseIterator)
{
	CMyArray<int> array;
	array.Add(1);
	array.Add(2);
	array.Add(3);

	const CMyArray<int>& constArray = array;
	auto rit = constArray.rbegin();
	EXPECT_EQ(*rit, 3);
	++rit;
	EXPECT_EQ(*rit, 2);
	++rit;
	EXPECT_EQ(*rit, 1);
	++rit;
	EXPECT_EQ(rit, constArray.rend());
}

TEST(CMyArrayTest, IteratorBeginEnd)
{
	CMyArray<int> array;
	array.Add(1);
	array.Add(2);
	array.Add(3);

	auto it = array.begin();
	auto endIt = array.end();

	EXPECT_NE(it, endIt);
	EXPECT_EQ(*it, 1);
	++it;
	EXPECT_NE(it, endIt);
	EXPECT_EQ(*it, 2);
	++it;
	EXPECT_NE(it, endIt);
	EXPECT_EQ(*it, 3);
	++it;
	EXPECT_EQ(it, endIt);
}

TEST(CMyArrayTest, ConstIteratorBeginEnd)
{
	CMyArray<int> array;
	array.Add(1);
	array.Add(2);
	array.Add(3);

	const CMyArray<int>& constArray = array;

	auto it = constArray.begin();
	auto endIt = constArray.end();

	EXPECT_NE(it, endIt);
	EXPECT_EQ(*it, 1);
	++it;
	EXPECT_NE(it, endIt);
	EXPECT_EQ(*it, 2);
	++it;
	EXPECT_NE(it, endIt);
	EXPECT_EQ(*it, 3);
	++it;
	EXPECT_EQ(it, endIt);
}

TEST(CMyArrayTest, ReverseIteratorBeginEnd)
{
	CMyArray<int> array;
	array.Add(1);
	array.Add(2);
	array.Add(3);

	auto it = array.rbegin();
	auto endIt = array.rend();

	EXPECT_NE(it, endIt);
	EXPECT_EQ(*it, 3);
	++it;
	EXPECT_NE(it, endIt);
	EXPECT_EQ(*it, 2);
	++it;
	EXPECT_NE(it, endIt);
	EXPECT_EQ(*it, 1);
	++it;
	EXPECT_EQ(it, endIt);
}

TEST(CMyArrayTest, ConstReverseIteratorBeginEnd)
{
	CMyArray<int> array;
	array.Add(1);
	array.Add(2);
	array.Add(3);

	const CMyArray<int>& constArray = array;

	auto it = constArray.rbegin();
	auto endIt = constArray.rend();

	EXPECT_NE(it, endIt);
	EXPECT_EQ(*it, 3);
	++it;
	EXPECT_NE(it, endIt);
	EXPECT_EQ(*it, 2);
	++it;
	EXPECT_NE(it, endIt);
	EXPECT_EQ(*it, 1);
	++it;
	EXPECT_EQ(it, endIt);
}

TEST(CMyArrayTest, ResizeIncreaseCapacity)
{
	CMyArray<int> array;
	array.Add(1);
	array.Add(2);
	array.Resize(5);
	EXPECT_EQ(array.Size(), 2);
	EXPECT_EQ(array.Capacity(), 5);
	EXPECT_EQ(array[0], 1);
	EXPECT_EQ(array[1], 2);
	EXPECT_THROW(array[2], std::out_of_range);
}

TEST(CMyArrayTest, ResizeDecreaseCapacity)
{
	CMyArray<int> array;
	array.Add(1);
	array.Add(2);
	array.Add(3);
	array.Resize(2);
	EXPECT_EQ(array.Size(), 2);
	EXPECT_EQ(array.Capacity(), 2);
	EXPECT_EQ(array[0], 1);
	EXPECT_EQ(array[1], 2);
	EXPECT_THROW(array[2], std::out_of_range);
}

TEST(CMyArrayTest, ResizeToZero)
{
	CMyArray<int> array;
	array.Add(1);
	array.Add(2);
	array.Resize(0);
	EXPECT_EQ(array.Size(), 0);
	EXPECT_EQ(array.Capacity(), 0);
	EXPECT_THROW(array[0], std::out_of_range);
}

TEST(CMyArrayTest, ResizeMaintainElements)
{
	CMyArray<int> array;
	array.Add(1);
	array.Add(2);
	array.Resize(2);
	EXPECT_EQ(array.Size(), 2);
	EXPECT_EQ(array.Capacity(), 2);
	EXPECT_EQ(array[0], 1);
	EXPECT_EQ(array[1], 2);
}

GTEST_API_ int main (int argc, char **argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}