#pragma once
#include <memory>
#include <iostream>

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
	TWeakPtr<T> _pre;

	~TNode()
	{
		std::cout << "析构函数调用\n";
	}
};

template<typename T>
class TList
{
public:
	TList()
	{
		_list = std::make_shared<TNode<T>>();
		pTail = _list;
		_length = 0;
	}

	TSharedPtr<T> push(T data)
	{
		TSharedPtr<T> node = std::make_shared<TNode<T>>();
		node->_data = data;
		pTail->_next = node;
		node->_pre = pTail;
		pTail = pTail->_next;
		pTail->_next = nullptr;
		_length++;
		return node;
	}

	TSharedPtr<T> insert(int index, T data)
	{
		if (index < 0 || index > _length)
		{
			return nullptr;
		}
		else if (index == _length)
		{
			return push(data);
		}

		TSharedPtr<T> node = std::make_shared<TNode<T>>();
		node->_data = data;

		TSharedPtr<T> pNode = _list;
		for (int i = 0; i < index; i++)
		{
			pNode = pNode->_next;
		}

		node->_next = pNode->_next;
		pNode->_next = node;
		node->_pre = pNode;
		node->_next->_pre = node;
		_length++;

		return node;
	}

	int find(T data)
	{
		TSharedPtr<T> pNode = _list;
		for (int i=0; i<_length; i++)
		{
			pNode = pNode->_next;
			if (data == pNode->_data)
			{
				return i;
			}
		}
		return -1;
	}

	void remove(int index)
	{
		 if (index < 0 || index >_length -1)
		 {
			 return;
		 }

		 if (index == _length-1)
		 {
			 pTail->_pre.lock()->_next = nullptr;
			 pTail = pTail->_pre.lock();
		 }
		 else
		 {
			 TSharedPtr<T> pNode = _list->_next;
			 while (index > 0)
			 {
				 pNode = pNode->_next;
				 index--;
			 }
			 pNode->_pre.lock()->_next = pNode->_next;
			 pNode->_next->_pre = pNode->_pre;
		 }
		 _length--;
	}

	void popAll()
	{
		TSharedPtr<T> pNode = _list;
		while (_length > 0)
		{
			pNode = pNode->_next;
			std::cout << pNode->_data << std::endl;
			_length--;
		}
	}

private:
	TSharedPtr<T> _list;
	int _length;
	TSharedPtr<T> pTail;
};



