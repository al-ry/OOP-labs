#include "StringList.h"

CStringList::CStringList()
{
	m_firstNode = std::make_unique<Node>("", nullptr, nullptr);
	m_firstNode->next = std::make_unique<Node>("", m_firstNode.get(), nullptr);
	m_lastNode = m_firstNode->next.get();
}

CStringList::CStringList(CStringList& list)
	: CStringList()
{
	for (const auto& elem : list)
	{
		AppendBack(elem);
	}
}

CStringList::CStringList(CStringList&& list)
{
	Clear();
	std::swap(m_firstNode, list.m_firstNode);
	std::swap(m_lastNode, list.m_lastNode);
	std::swap(m_size, list.m_size);
}

CStringList::~CStringList()
{
	Clear();
}

CStringList CStringList::operator=(CStringList& other)
{
	if (&other != this)
	{
		Clear();
		CStringList copyOfList(other);
		std::swap(m_firstNode, copyOfList.m_firstNode);
		std::swap(m_lastNode, copyOfList.m_lastNode);
		std::swap(m_size, copyOfList.m_size);
	}
	return *this;
}

CStringList CStringList::operator=(CStringList&& other)
{
	if (&other != this)
	{
		Clear(); 
		std::swap(m_firstNode, other.m_firstNode);
		std::swap(m_lastNode, other.m_lastNode);
		std::swap(m_size, other.m_size); 
	}
	return *this;
}

size_t CStringList::GetSize() const
{
	return m_size;
}

void CStringList::AppendBack(const std::string& data)
{
	Insert(data, end());
}
void CStringList::AppendFront(const std::string& data)
{

	Insert(data, begin());
}

void CStringList::Clear()
{
	while (!IsEmpty())
	{
		Erase(begin());
	}
}

bool CStringList::IsEmpty() const
{
	return (m_size == 0u);
}

std::string& CStringList::GetBackElement()
{
	if (IsEmpty())
	{
		throw std::runtime_error("Can't get back element from empty list");
	}
	return m_lastNode->prev->data;
}

std::string const& CStringList::GetBackElement() const
{
	if (IsEmpty())
	{
		throw std::runtime_error("Can't get back element from empty list");
	}
	return m_lastNode->prev->data;
}

std::string& CStringList::GetFrontElement()
{
	if (IsEmpty())
	{
		throw std::runtime_error("Can't get front element from empty list");
	}
	return m_firstNode->next->data;
}

std::string const& CStringList::GetFrontElement() const
{
	if (IsEmpty())
	{
		throw std::runtime_error("Can't get front element from empty list");
	}
	return m_firstNode->next->data;
}

CStringList::iterator CStringList::begin()
{
	return iterator(m_firstNode->next.get());
}

CStringList::iterator CStringList::end()
{
	return iterator(m_lastNode);
}

CStringList::const_iterator CStringList::begin() const
{
	return const_iterator(m_firstNode->next.get());
}

CStringList::const_iterator CStringList::end() const
{
	return const_iterator(m_lastNode);
}

CStringList::const_iterator CStringList::cbegin() const
{
	return const_iterator(m_firstNode->next.get());
}

CStringList::const_iterator CStringList::cend() const
{
	return const_iterator(m_lastNode);
}

std::reverse_iterator<CStringList::iterator> CStringList::rbegin()
{
	return std::reverse_iterator<iterator>(end());
}

std::reverse_iterator<CStringList::iterator> CStringList::rend()
{
	return std::reverse_iterator<iterator>(begin());
}

std::reverse_iterator<CStringList::const_iterator> CStringList::crbegin() const
{
	return std::reverse_iterator<const_iterator>(cend());
}

std::reverse_iterator<CStringList::const_iterator> CStringList::crend() const
{
	return std::reverse_iterator<const_iterator>(cbegin());
}

void CStringList::Insert(const std::string& data, const iterator& it)
{
	auto newNode = std::make_unique<Node>(data, it.m_node->prev, std::move(it.m_node->prev->next));
	it.m_node->prev = newNode.get();
	newNode->prev->next = std::move(newNode);
	m_size++;
}

void CStringList::Erase(const iterator& it)
{
	if (IsEmpty())
	{
		throw std::runtime_error("Cannot be erased from empty list");
	}
	if (it == end())
	{
		throw std::out_of_range("Cannot be erased from end() position");
	}
	it.m_node->next->prev = it.m_node->prev;
	it.m_node->prev->next = std::move(it.m_node->next);
	--m_size;
}
