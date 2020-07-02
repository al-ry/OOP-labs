#include "Node.h"
#include <stdexcept>

template <typename T>
class CMyList
{
public:
	template <typename T, bool IsConst>
	class CIterator
	{
		friend class CIterator<T, true>;
		friend CMyList;
		CIterator(Node<T>* node)
			: m_node(node){};

	public:
		using MyType = CIterator<T, IsConst>;
		using value_type = std::conditional_t<IsConst, const T, T>;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;
		CIterator() = default;

		//for cbegin() and cend()
		operator CIterator<T, false>()
		{
			return CIterator<T, false>(m_node);
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
			return *m_node->data;
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
			MyType& copy = *this;
			--*this;
			return copy;
		}

		MyType operator++(int)
		{
			if (!m_node->next)
			{
				throw std::out_of_range("Trying increment iterator to out of range");
			}
			MyType& copy = *this;
			++*this;
			return copy;
		}
	private:
		Node<T>* m_node = nullptr;
	};

	CMyList(const CMyList& list);
	CMyList(CMyList&& list)noexcept;
	CMyList();
	~CMyList();

	CMyList<T> operator=(const CMyList<T>& list);
	CMyList<T> operator=(CMyList<T>&& list);
	bool IsEmpty() const;
	void AppendBack(const T& data);
	void AppendFront(const T& data);
	size_t GetSize() const;
	void Clear();

	using iterator = CIterator<T, false>;
	using const_iterator = CIterator<T, true>;

	void Insert(const T& data, const iterator& it);
	void Erase(const iterator& it);
	iterator begin()
	{
		return { m_firstNode->next.get() };
	}
	iterator end()
	{
		return { m_lastNode };
	}
	
	const_iterator begin() const
	{
		return { m_firstNode->next.get() };
	}
	const_iterator end() const
	{
		return { m_lastNode };
	}

	const_iterator cbegin() const
	{
		return { m_firstNode->next.get() };
	}

	const_iterator cend() const
	{
		return { m_lastNode };
	}

	std::reverse_iterator<iterator> rbegin()
	{
		return std::reverse_iterator<iterator>(end());
	}
	std::reverse_iterator<iterator> rend()
	{
		return std::reverse_iterator<iterator>(begin());
	}

	std::reverse_iterator<const_iterator> rbegin()const
	{
		return std::reverse_iterator<const_iterator>(end());
	}
	std::reverse_iterator<const_iterator> rend()const
	{
		return std::reverse_iterator<const_iterator>(begin());
	}

	std::reverse_iterator<const_iterator> crbegin() const
	{
		return std::reverse_iterator<const_iterator>(end());
	}
	std::reverse_iterator<const_iterator> crend() const
	{
		return std::reverse_iterator<const_iterator>(begin());
	}
private:
	size_t m_size = 0u;
	std::unique_ptr<Node<T>> m_firstNode = nullptr;
	Node<T>* m_lastNode = nullptr;
};

template <typename T>
inline CMyList<T>::CMyList(const CMyList& list)
	: CMyList()
{
	for (auto elem : list)
	{
		AppendBack(elem);
	}
}

template <typename T>
inline CMyList<T>::CMyList(CMyList&& list)noexcept
{
	std::swap(m_firstNode, list.m_firstNode);
	std::swap(m_lastNode, list.m_lastNode);
	std::swap(m_size, list.m_size);
	CMyList tmpList;
	list.m_firstNode = std::move(tmpList.m_firstNode);
	list.m_lastNode = tmpList.m_lastNode;
	list.m_size = 0;
}

template <typename T>
inline CMyList<T>::CMyList()
{
	m_firstNode = std::make_unique<Node<T>>(std::nullopt, nullptr, nullptr);
	m_firstNode->next = std::make_unique<Node<T>>(std::nullopt, m_firstNode.get(), nullptr);
	m_lastNode = m_firstNode->next.get();
}

template <typename T>
inline CMyList<T>::~CMyList()
{
	Clear();
	m_firstNode = nullptr;
	m_lastNode = nullptr;
}


template <typename T>
inline CMyList<T> CMyList<T>::operator=(CMyList<T>&& list)
{
	if (std::addressof(list) != this)
	{
		Clear();
		std::swap(m_firstNode, list.m_firstNode);
		std::swap(m_lastNode, list.m_lastNode);
		std::swap(m_size, list.m_size);
		CMyList tmpList;
		list.m_firstNode = std::move(tmpList.m_firstNode);
		list.m_lastNode = tmpList.m_lastNode;
		list.m_size = 0;
	}
	return *this;
}

template <typename T>
inline CMyList<T> CMyList<T>::operator=(const CMyList<T>& list)
{
	if (std::addressof(list) != this)
	{
		CMyList<T> tempList(list);
		std::swap(tempList, *this);
	}
	return *this;
}

template <typename T>
inline bool CMyList<T>::IsEmpty() const
{
	return m_size == 0u;
}

template <typename T>
inline void CMyList<T>::AppendBack(const T& data)
{
	Insert(data, end());
}

template <typename T>
inline void CMyList<T>::AppendFront(const T& data)
{
	Insert(data, begin());
}

template <typename T>
inline size_t CMyList<T>::GetSize() const
{
	return m_size;
}

template <typename T>
inline void CMyList<T>::Clear()
{
	while (!IsEmpty())
	{
		Erase(begin());
	}
}

template <typename T>
inline void CMyList<T>::Insert(const T& data, const iterator& it)
{
	auto newNode = std::make_unique<Node<T>>(std::make_optional(data), it.m_node->prev, std::move(it.m_node->prev->next));
	it.m_node->prev = newNode.get();
	newNode->prev->next = std::move(newNode);
	m_size++;
}

template <typename T>
inline void CMyList<T>::Erase(const iterator& it)
{
	if (IsEmpty())
	{
		throw std::runtime_error("Can`t be erased from empty list");
	}
	if (it == end())
	{
		throw std::runtime_error("Can't be erased from end() position");
	}
	it.m_node->next->prev = it.m_node->prev;
	it.m_node->prev->next = std::move(it.m_node->next);
	--m_size;
}


