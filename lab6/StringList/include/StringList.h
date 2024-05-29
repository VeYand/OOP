#ifndef STRINGLIST_STRINGLIST_H
#define STRINGLIST_STRINGLIST_H

#include <memory>

#include <memory>
#include <string>
#include <utility>

struct Node
{
	std::string data;
	std::shared_ptr<Node> prev;
	std::shared_ptr<Node> next;

	explicit Node(std::string str);
};

class ListIterator
{
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = std::string;
	using difference_type = std::ptrdiff_t;
	using pointer = std::string*;
	using reference = std::string&;

	explicit ListIterator(const std::shared_ptr<Node>& node, bool reverse = false);

	std::shared_ptr<Node> GetNode() const;

	reference operator*() const;
	pointer operator->() const;

	ListIterator& operator++();
	ListIterator operator++(int);

	ListIterator& operator--();
	ListIterator operator--(int);

	bool operator==(const ListIterator& other) const;
	bool operator!=(const ListIterator& other) const;

private:
	std::shared_ptr<Node> m_node;
	bool m_reverse;
};

class StringList
{
public:
	StringList();
	StringList(const StringList& other);
	StringList(StringList&& other) noexcept;
	~StringList();

	StringList& operator=(const StringList& other);
	StringList& operator=(StringList&& other) noexcept;

	void PushBack(const std::string& str);
	void PushFront(const std::string& str);

	[[nodiscard]] size_t Size() const;
	[[nodiscard]] bool IsEmpty() const;
	void Clear();

	using ConstIterator = ListIterator;
	using ConstReverseIterator = ListIterator;

	ListIterator begin();
	ListIterator end();
	[[nodiscard]] ConstIterator begin() const;
	[[nodiscard]] ConstIterator end() const;

	ListIterator rbegin();
	ListIterator rend();
	[[nodiscard]] ConstReverseIterator rbegin() const;
	[[nodiscard]] ConstReverseIterator rend() const;

	void Insert(ListIterator pos, const std::string& str);
	void Erase(ListIterator pos);

private:
	std::shared_ptr<Node> m_begin;
	std::shared_ptr<Node> m_end;
	size_t m_size;
};

#endif // STRINGLIST_STRINGLIST_H
