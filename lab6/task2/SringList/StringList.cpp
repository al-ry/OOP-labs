#include "StringList.h"
#include "stdexcept"


CStringList::CStringList(CStringList& list)
{
	CStringList listCopy;
	for (const auto& elem : list)
	{
		listCopy.AppendBack(elem);
	}
	m_size = listCopy.GetSize();
	std::swap(m_firstNode, listCopy.m_firstNode);
	std::swap(m_lastNode, listCopy.m_lastNode);
}

CStringList::CStringList(CStringList&& list) noexcept
	: m_size(list.m_size)
	, m_firstNode(std::move(list.m_firstNode))
	, m_lastNode(list.m_lastNode)
{
	list.m_size = 0u;
	list.m_firstNode = nullptr;
	list.m_lastNode = nullptr;
}

CStringList::~CStringList()
{
	Clear();
}

CStringList CStringList::operator=(CStringList& other)
{
	if (&other != this)
	{
		CStringList copyOfList(other);
		this->m_size = copyOfList.GetSize();
		this->m_firstNode = std::move(copyOfList.m_firstNode);
		this->m_lastNode = copyOfList.m_lastNode;
	}
	return *this;
}

CStringList CStringList::operator=(CStringList&& other) noexcept
{
	if (&other != this)
	{
		this->m_size = other.GetSize();
		this->m_firstNode = std::move(other.m_firstNode);
		this->m_lastNode = other.m_lastNode;
		other.m_size = 0u;
		other.m_firstNode = nullptr;
		other.m_lastNode = nullptr;
	}
	return *this;
}

size_t CStringList::GetSize() const
{
	return m_size;
}

void CStringList::AppendBack(const std::string& data)
{
	auto newNode = std::make_unique<Node>(data, m_lastNode, nullptr);
	Node* newLastNode = newNode.get();
	if (m_lastNode)
	{
		m_lastNode->next = std::move(newNode);
	}
	else
	{
		m_firstNode = move(newNode);
	}
	m_lastNode = newLastNode;
	++m_size;
}
void CStringList::AppendFront(const std::string& data)
{
	auto newNode = std::make_unique<Node>(data, nullptr, std::move(m_firstNode));
	Node* newFrontNode = newNode.get();
	if (newNode->next)
	{
		newNode->next->prev = std::move(newFrontNode);
	}
	else
	{
		m_lastNode = std::move(newFrontNode);
	}
	m_firstNode = std::move(newNode);
	++m_size;
}

void CStringList::Clear()
{
	while (m_lastNode)
	{
		m_lastNode->next = nullptr;
		m_lastNode = m_lastNode->prev;
	}
	m_firstNode = nullptr;
	m_size = 0;
}

bool CStringList::IsEmpty() const
{
	return (m_size == 0u);
}

std::string& CStringList::GetBackElement() const
{
	if (IsEmpty())
	{
		throw std::runtime_error("Can't get back element from empty list");
	}
	return m_lastNode->data;
}

std::string const& CStringList::GetBackElement()
{
	if (IsEmpty())
	{
		throw std::runtime_error("Can't get back element from empty list");
	}
	return m_lastNode->data;
}

std::string& CStringList::GetFrontElement() const
{
	if (IsEmpty())
	{
		throw std::runtime_error("Can't get front element from empty list");
	}
	return m_firstNode->data;
}

std::string const& CStringList::GetFrontElement()
{
	if (IsEmpty())
	{
		throw std::runtime_error("Can't get front element from empty list");
	}
	return m_firstNode->data;
}

CStringList::CIterator::CIterator(Node* node, bool isReversed = false)
	: m_node(node)
	, m_isReversed(isReversed)
{
}

std::string& CStringList::CIterator::operator*() const
{
	if (!m_node)
	{
		throw std::runtime_error("Cannot provide access to data");
	}
	return m_node->data;
}

CStringList::CIterator& CStringList::CIterator::operator++()
{
	if (!m_node)
	{
		throw std::runtime_error("Cannot provide access to iterator");
	}
	if (m_isReversed)
	{
		m_node = m_node->prev;
	}
	else
	{
		m_node = m_node->next.get();
	}
	return *this;
}

CStringList::CIterator& CStringList::CIterator::operator--()
{
	if (!m_node)
	{
		throw std::runtime_error("Cannot provide access to iterator");
	}
	if (m_isReversed)
	{
		m_node = m_node->next.get();
	}
	else
	{
		m_node = m_node->prev;
	}
	return *this;
}

bool CStringList::CIterator::operator==(const CIterator& it) const
{
	return (this->m_node == it.m_node);
}
bool CStringList::CIterator::operator!=(const CIterator& it) const
{
	return (this->m_node != it.m_node);
}

CStringList::CIterator CStringList::begin()
{
	return CIterator(m_firstNode.get());
}

CStringList::CIterator CStringList::end()
{
	return CIterator(m_lastNode->next.get());
}

const CStringList::CIterator CStringList::cbegin() const
{
	return CIterator(m_firstNode.get());
}

const CStringList::CIterator CStringList::cend() const
{
	return CIterator(m_lastNode->next.get());
}

CStringList::CIterator CStringList::rbegin()
{
	return CIterator(m_lastNode, true);
}

CStringList::CIterator CStringList::rend()
{
	return CIterator(m_firstNode->prev, true);
}

const CStringList::CIterator CStringList::crbegin() const
{
	return CIterator(m_lastNode, true);
}

const CStringList::CIterator CStringList::crend() const
{
	return CIterator(m_firstNode->prev, true);
}

void CStringList::Insert(const std::string& data, const CIterator& it)
{
	if (IsEmpty())
	{
		AppendFront(data);
		return;
	}
	if (!it.m_node)
	{
		throw std::runtime_error("Trying to erase element from null position");
	}
	if (it == m_firstNode.get())
	{
		AppendFront(data);
	}
	else if (it == m_lastNode)
	{
		AppendBack(data);
	}
	else
	{
		auto newNode = std::make_unique<Node>(data, it.m_node->prev, std::move(it.m_node->prev->next));
		it.m_node->prev = std::move(newNode.get());
		it.m_node->prev->prev->next = std::move(newNode);
		m_size++;
	}
}

void CStringList::Erase(const CIterator& it)
{
	if (IsEmpty())
	{
		throw std::runtime_error("Cannot be erased from empty list");
	}
	if (m_size == 1)
	{
		Clear();
		return;
	}
	if (!it.m_node)
	{
		throw std::runtime_error("Trying to erase element from null position");
	}
	if (it == m_firstNode.get()) 
	{
		it.m_node->next->prev = nullptr;
		m_firstNode = std::move(it.m_node->next);
	}
	else if (it == m_lastNode)
	{
		m_lastNode = m_lastNode->prev;
		m_lastNode->next = nullptr;
	}
	else
	{
		it.m_node->next->prev = std::move(it.m_node->prev);
		it.m_node->prev->next = std::move(it.m_node->next);
	}
	--m_size;
}
