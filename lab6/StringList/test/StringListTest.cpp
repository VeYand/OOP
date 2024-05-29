#include <gtest/gtest.h>
#include "../include/StringList.h"

TEST(StringListTest, EmptyConstructor) {
	StringList list;

	EXPECT_EQ(list.Size(), 0);
	EXPECT_TRUE(list.IsEmpty());
	EXPECT_EQ(list.begin().operator->(), nullptr);
	EXPECT_EQ(list.end().operator->(), nullptr);
	EXPECT_EQ(list.rbegin().operator->(), nullptr);
	EXPECT_EQ(list.rend().operator->(), nullptr);
}


TEST(StringListTest, CopyConstructorEmptyList)
{
	StringList list1;
	StringList list2(list1);

	ASSERT_EQ(list1.Size(), list2.Size());
	ASSERT_TRUE(list2.IsEmpty());
}

TEST(StringListTest, CopyConstructorSingleElementList)
{
	StringList list1;
	list1.PushBack("element");

	StringList list2(list1);

	ASSERT_EQ(list1.Size(), list2.Size());
	ASSERT_FALSE(list2.IsEmpty());

	ASSERT_EQ(*list1.begin(), *list2.begin());
}

TEST(StringListTest, CopyConstructorSelfCopy)
{
	StringList list1;
	list1.PushBack("element");

	list1 = StringList(list1);

	ASSERT_EQ(list1.Size(), 7);
	ASSERT_FALSE(list1.IsEmpty());

	ASSERT_EQ(*list1.begin(), "element");
}

TEST(StringListTest, CopyConstructorMultipleElementList)
{
	StringList list1;
	list1.PushBack("element1");
	list1.PushBack("element2");
	list1.PushBack("element3");

	StringList list2(list1);

	ASSERT_EQ(list1.Size(), list2.Size());
	ASSERT_FALSE(list2.IsEmpty());

	auto it1 = list1.begin();
	auto it2 = list2.begin();
	while (it1 != list1.end() && it2 != list2.end())
	{
		ASSERT_EQ(*it1, *it2);
		it1++;
		it2++;
	}
}

TEST(StringListTest, MoveConstructorEmptyList) {
	StringList list1;
	StringList list2(std::move(list1));

	EXPECT_TRUE(list1.IsEmpty());
	EXPECT_TRUE(list2.IsEmpty());
}

TEST(StringListTest, MoveConstructorNonEmptyList) {
	StringList list1;
	list1.PushBack("foo");
	list1.PushBack("bar");

	StringList list2(std::move(list1));

	EXPECT_EQ(list1.Size(), 0);
	EXPECT_EQ(list2.Size(), 2);
	EXPECT_EQ(*list2.begin(), "foo");
	EXPECT_EQ(*list2.end(), "bar");
}

TEST(StringListTest, MoveConstructorMultipleMoves) {
	StringList list1;
	list1.PushBack("foo");

	StringList list2(std::move(list1));
	StringList list3(std::move(list2));

	EXPECT_TRUE(list1.IsEmpty());
	EXPECT_TRUE(list2.IsEmpty());
	EXPECT_FALSE(list3.IsEmpty());
}

TEST(StringListTest, MoveConstructorSelfMove) {
	StringList list;
	list.PushBack("foo");

	StringList* ptr = &list;
	StringList list2(std::move(list));

	EXPECT_TRUE(ptr->IsEmpty());
	EXPECT_FALSE(list2.IsEmpty());
}

TEST(StringListTest, AssignmentOperatorCopyEmptyList) {
	StringList list1;
	StringList list2;

	list2 = list1;

	EXPECT_EQ(list2.Size(), 0);
	EXPECT_TRUE(list2.IsEmpty());
}

TEST(StringListTest, AssignmentOperatorCopyNonEmptyList) {
	StringList list1;
	list1.PushBack("Hello");
	list1.PushBack("World");

	StringList list2;
	list2.PushBack("Goodbye");

	list2 = list1;

	EXPECT_EQ(list2.Size(), 2);
	EXPECT_FALSE(list2.IsEmpty());

	auto it = list2.begin();
	EXPECT_EQ(*it, "Hello");
	it++;
	EXPECT_EQ(*it, "World");
}

TEST(StringListTest, AssignmentOperatorSelfAssignment) {
	StringList list;
	list.PushBack("Hello");

	list = list;

	EXPECT_EQ(list.Size(), 1);
	EXPECT_FALSE(list.IsEmpty());
	EXPECT_EQ(*list.begin(), "Hello");
}

TEST(StringListTest, AssignmentOperatorChainAssignments) {
	StringList list1;
	list1.PushBack("Apple");

	StringList list2;
	list2.PushBack("Banana");

	StringList list3;
	list3.PushBack("Cherry");

	list3 = list2 = list1;

	EXPECT_EQ(list1.Size(), 1);
	EXPECT_EQ(list2.Size(), 1);
	EXPECT_EQ(list3.Size(), 1);

	EXPECT_EQ(*list1.begin(), "Apple");
	EXPECT_EQ(*list2.begin(), "Apple");
	EXPECT_EQ(*list3.begin(), "Apple");
}

TEST(StringListTest, AssignmentOperatorEmptyToNonEmpty) {
	StringList list1;

	StringList list2;
	list2.PushBack("Hello");

	list2 = list1;

	EXPECT_EQ(list2.Size(), 0);
	EXPECT_TRUE(list2.IsEmpty());
}

TEST(StringListTest, AssignmentOperatorNonEmptyToEmpty) {
	StringList list1;
	list1.PushBack("Hello");

	StringList list2;

	list2 = list1;

	EXPECT_EQ(list2.Size(), 1);
	EXPECT_FALSE(list2.IsEmpty());
	EXPECT_EQ(*list2.begin(), "Hello");
}

TEST(StringListTest, MoveAssignmentOperator) {
	StringList list1;
	list1.PushBack("apple");
	list1.PushBack("banana");
	list1.PushBack("cherry");

	StringList list2;
	list2.PushBack("orange");
	list2.PushBack("pear");

	list2 = std::move(list1);

	ASSERT_TRUE(list1.IsEmpty());
	ASSERT_EQ(list1.Size(), 0);

	ASSERT_EQ(list2.Size(), 3);
	ASSERT_EQ(*list2.begin(), "apple");
	ASSERT_EQ(*list2.end(), "cherry");
}

TEST(StringListTest, MoveAssignmentOperatorSelfAssignment) {
	StringList list;
	list.PushBack("apple");
	list.PushBack("banana");
	list.PushBack("cherry");

	list = std::move(list);

	ASSERT_EQ(list.Size(), 3);
	ASSERT_EQ(*list.begin(), "apple");
	ASSERT_EQ(*list.end(), "cherry");
}

TEST(StringListTest, MoveAssignmentOperatorEmptyList) {
	StringList list1;
	list1.PushBack("apple");
	list1.PushBack("banana");

	StringList list2;

	list1 = std::move(list2);

	ASSERT_TRUE(list1.IsEmpty());
	ASSERT_EQ(list1.Size(), 0);

	ASSERT_TRUE(list2.IsEmpty());
	ASSERT_EQ(list2.Size(), 0);
}

TEST(StringListTest, PushBackOnEmptyList) {
	StringList list;
	list.PushBack("A");

	EXPECT_EQ(list.Size(), 1);
	EXPECT_FALSE(list.IsEmpty());
	EXPECT_EQ(*list.begin(), "A");
	EXPECT_EQ(*list.end(), "A");
}

TEST(StringListTest, PushBackOnNonEmptyList) {
	StringList list;
	list.PushBack("A");
	list.PushBack("B");

	EXPECT_EQ(list.Size(), 2);
	EXPECT_FALSE(list.IsEmpty());
	EXPECT_EQ(*list.begin(), "A");
	EXPECT_EQ(*list.end(), "B");
}

TEST(StringListTest, PushBackMultipleElements) {
	StringList list;
	list.PushBack("A");
	list.PushBack("B");
	list.PushBack("C");

	EXPECT_EQ(list.Size(), 3);
	EXPECT_FALSE(list.IsEmpty());
	EXPECT_EQ(*list.begin(), "A");
	EXPECT_EQ(*list.end(), "C");
}

TEST(StringListTest, PushFrontAddOneElementSizeIncreased)
{
	StringList list;
	list.PushFront("test");
	EXPECT_EQ(list.Size(), 1);
}

TEST(StringListTest, PushFrontAddMultipleElementsSizeIncreased)
{
	StringList list;
	list.PushFront("test1");
	list.PushFront("test2");
	list.PushFront("test3");
	EXPECT_EQ(list.Size(), 3);
}

TEST(StringListTest, PushFrontAddEmptyStringSizeIncreased)
{
	StringList list;
	list.PushFront("");
	EXPECT_EQ(list.Size(), 1);
}

TEST(StringListTest, PushFrontAddStringsSizeCorrectOrder)
{
	StringList list;
	list.PushFront("test1");
	list.PushFront("test2");
	list.PushFront("test3");

	auto node = list.begin();
	EXPECT_EQ(*node, "test3");
	node++;
	EXPECT_EQ(*node, "test2");
	node++;
	EXPECT_EQ(*node, "test1");
}

TEST(StringListTest, PushFrontAddToEmptyListBeginAndEndAreEqual)
{
	StringList list;
	list.PushFront("test");
	EXPECT_EQ(list.begin(), list.end());
}

TEST(StringListTest, PushFrontAddToNonEmptyListBeginNotEqualEnd)
{
	StringList list;
	list.PushFront("test1");
	list.PushFront("test2");
	EXPECT_NE(list.begin(), list.end());
}

TEST(StringListTest, InsertEmptyList)
{
	StringList list;
	list.Insert(list.begin(), "test");
	ASSERT_EQ(list.Size(), 1);
	ASSERT_EQ(*list.begin(), "test");
}

TEST(StringListTest, InsertFront)
{
	StringList list;
	list.PushFront("second");
	list.Insert(list.begin(), "first");
	ASSERT_EQ(list.Size(), 2);
	ASSERT_EQ(*list.begin(), "first");
	ASSERT_EQ(*list.end(), "second");
}

TEST(StringListTest, InsertBack)
{
	StringList list;
	list.PushBack("first");
	list.Insert(list.end(), "second");
	ASSERT_EQ(list.Size(), 2);
	ASSERT_EQ(*list.begin(), "first");
	ASSERT_EQ(*list.end(), "second");
}

TEST(StringListTest, InsertMiddle)
{
	StringList list;
	list.PushBack("first");
	list.PushBack("third");
	auto it = list.begin();
	it++;
	list.Insert(it, "second");
	ASSERT_EQ(list.Size(), 3);
	ASSERT_EQ(*list.begin(), "first");
	ASSERT_EQ(*(++list.begin()), "second");
	ASSERT_EQ(*list.end(), "third");
}

TEST(StringListTest, InsertEnd)
{
	StringList list;
	list.PushBack("first");
	list.Insert(list.end(), "second");
	ASSERT_EQ(list.Size(), 2);
	ASSERT_EQ(*list.begin(), "first");
	ASSERT_EQ(*list.end(), "second");
}

TEST(StringListTest, InsertOutOfBounds)
{
	StringList list;
	list.PushBack("first");

	ASSERT_THROW(list.Insert(list.end(), "second"), std::out_of_range);
}

TEST(StringListTest, EraseFromEmptyList) {
	StringList list;

	auto node = list.begin();

	ASSERT_NO_THROW(list.Erase(node));
	ASSERT_EQ(list.Size(), 0);
}

TEST(StringListTest, EraseFirstElement) {
	StringList list;
	list.PushBack("one");
	list.PushBack("two");
	list.PushBack("three");

	auto node = list.begin();
	list.Erase(node);
	ASSERT_EQ(list.Size(), 2);
	ASSERT_EQ(*list.begin(), "two");
}

TEST(StringListTest, EraseLastElement) {
	StringList list;
	list.PushBack("one");
	list.PushBack("two");
	list.PushBack("three");

	auto node = list.rbegin();
	list.Erase(node);
	ASSERT_EQ(list.Size(), 2);
	ASSERT_EQ(*list.rbegin(), "two");
}

TEST(StringListTest, EraseMiddleElement) {
	StringList list;
	list.PushBack("one");
	list.PushBack("two");
	list.PushBack("three");

	auto node = list.begin();
	list.Erase(node);
	ASSERT_EQ(list.Size(), 2);
	ASSERT_EQ(*(++list.begin()), "three");
}

TEST(StringListTest, EraseAllElements) {
	StringList list;
	list.PushBack("one");
	list.PushBack("two");
	list.PushBack("three");

	auto node = list.begin();
	while (node.operator->() != nullptr) {
		auto next_node = ++node;
		list.Erase(node);
		node = next_node;
	}
	ASSERT_EQ(list.Size(), 0);
}

TEST(StringListTest, ClearEmptyList) {
	StringList list;
	list.Clear();
	EXPECT_TRUE(list.IsEmpty());
	EXPECT_EQ(list.Size(), 0);
}

TEST(StringListTest, ClearNonEmptyList) {
	StringList list;
	list.PushBack("One");
	list.PushBack("Two");
	list.PushBack("Three");
	list.Clear();
	EXPECT_TRUE(list.IsEmpty());
	EXPECT_EQ(list.Size(), 0);
}

TEST(StringListTest, ClearMultipleClears) {
	StringList list;
	list.PushBack("One");
	list.PushBack("Two");
	list.Clear();
	list.Clear();
	EXPECT_TRUE(list.IsEmpty());
	EXPECT_EQ(list.Size(), 0);
}

TEST(StringListTest, ClearInsertAfterClear) {
	StringList list;
	list.PushBack("One");
	list.PushBack("Two");
	list.Clear();
	list.PushBack("Three");
	EXPECT_FALSE(list.IsEmpty());
	EXPECT_EQ(list.Size(), 1);
	EXPECT_EQ(*list.begin(), "Three");
}

TEST(StringListTest, ClearEraseAfterClear) {
	StringList list;
	list.PushBack("One");
	list.PushBack("Two");
	list.Clear();
	list.Erase(list.begin());
	EXPECT_TRUE(list.IsEmpty());
	EXPECT_EQ(list.Size(), 0);
}

TEST(StringListTest, ClearRBeginREndAfterClear) {
	StringList list;
	list.PushBack("One");
	list.PushBack("Two");
	list.PushBack("Three");
	list.Clear();
	EXPECT_EQ(list.rbegin().operator->(), nullptr);
	EXPECT_EQ(list.rend().operator->(), nullptr);
	EXPECT_EQ(list.rbegin(), list.rend());
}

TEST(StringListTest, PushBackAndSize) {
	StringList list;
	EXPECT_TRUE(list.IsEmpty());

	list.PushBack("hello");
	list.PushBack("world");
	EXPECT_EQ(list.Size(), 2);
}

TEST(StringListTest, PushFrontAndRangeBasedFor) {
	StringList list;
	list.PushFront("world");
	list.PushFront("hello");

	std::string result;
	for (const auto& str : list) {
		result += str;
	}

	EXPECT_EQ(result, "helloworld");
}

TEST(StringListTest, InsertAndSTLAlgorithm) {
	StringList list;
	list.PushBack("hello");
	list.PushBack("world");

	auto it = list.begin();
	++it;
	list.Insert(it, "beautiful");

	std::vector<std::string> result;
	std::copy(list.begin(), list.end(), std::back_inserter(result));

	std::string finalResult;
	for (const auto& str : result) {
		finalResult += str;
	}

	EXPECT_EQ(finalResult, "hellobeautifulworld");
}

TEST(StringListTest, EraseAndReverseIterator) {
	StringList list;
	list.PushBack("hello");
	list.PushBack("beautiful");
	list.PushBack("world");

	auto it = list.begin();
	++it;
	list.Erase(it);

	std::string result;
	for (auto rit = list.rbegin(); rit != list.rend(); ++rit) {
		result += *rit;
	}

	EXPECT_EQ(result, "dlrowolleh");
}


GTEST_API_ int main (int argc, char **argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}