#pragma once
#include <memory>

template<typename T>
struct TNode;

template<typename T>
using TSharedPtr = std::shared_ptr<TNode<T>>;

template<typename T>
using TWeakPtr = std::weak_ptr<TNode<T>>;

template<typename T>
struct TNode
{
	T _data;
	TSharedPtr<T> _next;
	TWeakPtr<T> _last; 
};
 
template<typename T>
class TList
{
public:
	TList()
	{
		_list = std::make_shared<TNode<T>>();
		pHead = _list;
		pTail = _list;
		_length = 0;
	}

	TSharedPtr<T> push(T data)
	{
		TSharedPtr<T> node = std::make_shared<TNode<T>>();
		node->_data = data;

		pTail->_next = node;
		node->_last = pTail;
		pTail = pTail->_next;
		return node;
	}

private:
	TSharedPtr<T> _list;
	int _length;
	TNode<T>* pHead;
	TNode<T>* pTail;
};



