#pragma once

#include <string>
#include <memory>

class CStringList
{
	friend class CIterator;
	struct Node
	{
		Node(std::string data, Node* prev, std::unique_ptr<Node>&& next)
			: data(std::move(data))
			, prev(prev)
			, next(std::move(next))
		{
		}
		std::string data;
		Node* prev;
		std::unique_ptr<Node> next;
	};
public:
	class CIterator
	{
		friend class CStringList;
		CIterator(Node* node, bool isReversed);

	public:
		CIterator() = default;
		std::string& operator*() const;
		CIterator& operator++();
		CIterator& operator--();

		bool operator!=(const CIterator& it) const;
		bool operator==(const CIterator& it) const;

	private:
		Node* m_node = nullptr;
		bool m_isReversed = false;
	};
	CStringList() = default;
	CStringList(CStringList& list);
	CStringList(CStringList&& list) noexcept;
	~CStringList();

	CStringList operator=(CStringList& other);
	CStringList operator=(CStringList&& other) noexcept;

	CIterator begin();
	CIterator end();

	const CIterator cbegin()const;
	const CIterator cend() const;

	CIterator rbegin();
	CIterator rend();

	const CIterator crbegin() const;
	const CIterator crend() const;

	void Insert(const std::string& data, const CIterator& it);
	void Erase(const CIterator& it);

	size_t GetSize() const;
	void AppendBack(const std::string& data);
	void AppendFront(const std::string& data);

	void Clear();
	bool IsEmpty() const;

	std::string& GetBackElement() const;
	std::string const& GetBackElement();
	std::string& GetFrontElement() const;
	std::string const& GetFrontElement();

private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node* m_lastNode = nullptr;
};
