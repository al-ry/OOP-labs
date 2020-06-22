#include "StringList.h"
#include "stdexcept"


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
	m_firstNode = nullptr;
	m_lastNode = nullptr;
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

std::string& CStringList::GetBackElement() const
{
	if (IsEmpty())
	{
		throw std::runtime_error("Can't get back element from empty list");
	}
	return m_lastNode->next->data;
}

std::string const& CStringList::GetBackElement()
{
	if (IsEmpty())
	{
		throw std::runtime_error("Can't get back element from empty list");
	}
	return m_lastNode->prev->data;
}

std::string& CStringList::GetFrontElement() const
{
	if (IsEmpty())
	{
		throw std::runtime_error("Can't get front element from empty list");
	}
	return m_firstNode->next->data;
}

std::string const& CStringList::GetFrontElement()
{
	if (IsEmpty())
	{
		throw std::runtime_error("Can't get front element from empty list");
	}
	return m_firstNode->next->data;
}

CStringList::CIterator::CIterator(Node* node, bool isReversed = false)
	: m_node(node)
	, m_isReversed(isReversed)
{
}

std::string& CStringList::CIterator::operator*() const
{
	if (!m_node->next || !m_node->prev)
	{
		throw std::out_of_range("Cannot provide access to data");
	}
	return m_node->data;
}

CStringList::CIterator& CStringList::CIterator::operator++()
{
	if (m_isReversed)
	{
		if (!m_node->prev)
		{
			throw std::out_of_range("Cannot provide access to iterator");
		}
		m_node = m_node->prev;
	}
	else
	{
		if (!m_node->next)
		{
			throw std::out_of_range("Cannot provide access to iterator");
		}
		m_node = m_node->next.get();
	}
	return *this;
}

CStringList::CIterator& CStringList::CIterator::operator--()
{
	if (m_isReversed)
	{
		if (!m_node->next->next)	
		{
			throw std::out_of_range("Cannot provide access to iterator");
		}
		m_node = m_node->next.get();
	}
	else
	{
		if (!m_node->prev->prev)
		{
			throw std::out_of_range("Cannot provide access to iterator");
		}
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
	return CIterator(m_firstNode->next.get());
}

CStringList::CIterator CStringList::end()
{
	return CIterator(m_lastNode);
}

const CStringList::CIterator CStringList::cbegin() const
{
	return CIterator(m_firstNode->next.get());
}

const CStringList::CIterator CStringList::cend() const
{
	return CIterator(m_lastNode);
}

CStringList::CIterator CStringList::rbegin()
{
	return CIterator(m_lastNode->prev, true);
}

CStringList::CIterator CStringList::rend()
{
	return CIterator(m_firstNode.get(), true);
}

const CStringList::CIterator CStringList::crbegin() const
{
	return CIterator(m_lastNode->prev, true);
}

const CStringList::CIterator CStringList::crend() const
{
	return CIterator(m_firstNode.get(), true);
}

void CStringList::Insert(const std::string& data, const CIterator& it)
{
	if (it == rend())
	{
		AppendFront(data);
		return;
	}
	if (it == rbegin())
	{
		AppendBack(data);
		return;
	}
	auto newNode = std::make_unique<Node>(data, it.m_node->prev, std::move(it.m_node->prev->next));
	it.m_node->prev = newNode.get();
	newNode->prev->next = std::move(newNode);
	m_size++;
}

void CStringList::Erase(const CIterator& it)
{
	if (IsEmpty())
	{
		throw std::runtime_error("Cannot be erased from empty list");
	}
	if (it == rend() || it == end())
	{
		throw std::out_of_range("Cannot be erased from end() and rend() position");
	}
	it.m_node->next->prev = it.m_node->prev;
	it.m_node->prev->next = std::move(it.m_node->next);
	--m_size;
}
