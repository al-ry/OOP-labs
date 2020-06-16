#pragma once
#include <memory>
#include <optional>

template <typename T>
class Node
{
public:
	Node(const std::optional<T>& data, Node<T>* prev, std::unique_ptr<Node<T>>&& next)
		: data(data)
		, prev(prev)
		, next(std::move(next))
	{
	}
	std::optional<T> data;
	Node<T>* prev;
	std::unique_ptr<Node<T>> next;
};