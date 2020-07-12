#pragma once

#include <string>
#include <memory>
#include "stdexcept"

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
	template <bool IsConst>
	class CIterator
	{
		friend class CStringList;
		friend class CIterator<true>;
		CIterator(Node* node)
			: m_node(node)
		{
		}
	public:
		using MyType = CIterator<IsConst>;
		using value_type = std::conditional_t<IsConst, const std::string, std::string>;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;
		CIterator() = default;

		operator CIterator<false>()
		{
			return CIterator<false>(m_node);
		}
		bool operator==(const MyType& other) const
		{
			return this->m_node == other.m_node;
		}

		bool operator!=(const MyType& other) const
		{
			return this->m_node != other.m_node;
		}
		reference& operator*() const
		{
			if (!m_node->next || !m_node->prev)
			{
				throw std::runtime_error("Cannot get data from iterator");
			}
			return m_node->data;
		}
		pointer operator->() const
		{
			if (!m_node->next || !m_node->prev)
			{
				throw std::logic_error("can not take pointer of end or rend iterator");
			}
			return &m_node->data;
		}
		MyType& operator++()
		{
			if (!m_node->next)
			{
				throw std::out_of_range("Trying increment iterator to out of range");
			}
			m_node = m_node->next.get();
			return *this;
		}
		MyType& operator--()
		{
			if (!m_node->prev->prev)
			{
				throw std::out_of_range("Trying decrement iterator to out of range");
			}
			m_node = m_node->prev;
			return *this;
		}

		MyType operator--(int)
		{
			if (!m_node->prev->prev)
			{
				throw std::out_of_range("Trying decrement iterator to out of range");
			}
			auto copy = *this;
			--*this;
			return copy;
		}

		MyType operator++(int)
		{
			if (!m_node->next)
			{
				throw std::out_of_range("Trying increment iterator to out of range");
			}
			auto copy = *this;
			++*this;
			return copy;
		}
	private:
		Node* m_node = nullptr;	
	};
	CStringList();
	CStringList(CStringList& list);
	CStringList(CStringList&& list);
	~CStringList();

	CStringList operator=(CStringList& other);
	CStringList operator=(CStringList&& other) noexcept;

	using iterator = CIterator<false>;
	using const_iterator = CIterator<true>;

	iterator begin();
	iterator end();

	const_iterator begin() const;
	const_iterator end() const;

	const_iterator cbegin() const;
	const_iterator cend() const;

	std::reverse_iterator<iterator> rbegin();
	std::reverse_iterator<iterator> rend();

	std::reverse_iterator<const_iterator> crbegin() const;
	std::reverse_iterator<const_iterator> crend() const;

	void Insert(const std::string& data, const iterator& it);
	void Erase(const iterator& it);

	size_t GetSize() const;
	void AppendBack(const std::string& data);
	void AppendFront(const std::string& data);

	void Clear();
	bool IsEmpty() const;

	std::string& GetBackElement();
	std::string const& GetBackElement() const;
	std::string& GetFrontElement();
	std::string const& GetFrontElement() const;

private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node* m_lastNode = nullptr;
};
