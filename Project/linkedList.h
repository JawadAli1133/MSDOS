#pragma once
#include<iostream>
using namespace std;

template <typename T>
class Node {
public:
	T data;
	Node<T>* next;
	Node<T>* prev;
	Node(T val) {
		data = val;
		next = nullptr;
		prev = nullptr;
	}
};
template <typename T>
class dLinkedList {
public:
	Node<T>* head;
	Node<T>* tail;
public:
	dLinkedList()
	{
		head = nullptr;
		tail = nullptr;
	}

	class fiterator {
	public:
		Node<T>* fiter;
	public:
		fiterator(Node<T>* n)
		{
			fiter = n;
		}

		Node<T>* operator ++(int)
		{
			return fiter = fiter->next;
		}

		bool operator==(Node<T>* n)
		{
			return fiter == n;
		}

		bool operator!=(Node<T>* n)
		{
			return fiter != n;
		}

		T operator*()
		{
			return fiter->data;
		}

	};

	class riterator {
	public:
		Node<T>* riter;
	public:
		riterator(Node<T>* n)
		{
			riter = n;
		}

		Node<T>* operator ++(int)
		{
			return riter = riter->prev;
		}

		bool operator==(Node<T>* n)
		{
			return riter == n;
		}

		bool operator!=(Node<T>* n)
		{
			return riter != n;
		}

		T operator*()
		{
			return riter->data;
		}
	};

	class giterator {
	public:
		Node<T>* giter;
	public:
		giterator(Node<T>* n)
		{
			giter = n;
		}

		Node<T>* operator ++(int)
		{
			return giter = giter->next;
		}

		Node<T>* operator --(int)
		{
			return giter = giter->prev;
		}

		bool operator==(Node<T>* n)
		{
			return giter == n;
		}

		bool operator!=(Node<T>* n)
		{
			return giter != n;
		}

		T operator*()
		{
			return giter->data;
		}
	};
	Node<T>* fbegin()
	{
		return head;
	}

	Node<T>* fend()
	{
		return tail->next;
	}

	Node<T>* rbegin()
	{
		return tail;
	}

	Node<T>* rend()
	{
		return head->prev;
	}

	Node<T>* begin()
	{
		return head;
	}

	Node<T>* end()
	{
		return tail;
	}
	bool isEmpty()
	{
		return head == nullptr;
	}

	void InsertAtHead(T value)
	{
		Node<T>* newNode = new Node<T>(value);
		if (isEmpty())
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			newNode->next = head;
			head->prev = newNode;
			newNode->prev = nullptr;
			head = newNode;
		}
	}

	void InsertAtTail(T val)
	{
		Node<T>* newNode = new Node<T>(val);
		if (isEmpty())
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			tail->next = newNode;
			newNode->next = nullptr;
			newNode->prev = tail;
			tail = newNode;
		}
	}

	void Print()
	{
		Node<T>* temp = head;
		while (temp != nullptr)
		{
			cout << temp->data << "<----->";
			temp = temp->next;
		}
		cout << "NULL" << endl;
	}


	void InsertAfter(T key, T value)
	{
		Node<T>* temp = head;
		while (temp->data != key)
		{
			temp = temp->next;
		}
		Node<T>* newNode = new Node<T>(value);
		newNode->next = temp->next;
		newNode->prev = temp;
		temp->next->prev = newNode;
		temp->next = newNode;
	}

	void InsertBefore(T key, T value)
	{
		int count = 0;
		Node<T>* temp = head;
		while (temp->data != key)
		{
			temp = temp->next;
			count++;
		}
		if (count == 0)
		{
			InsertAtHead(value);
		}
		else
		{
			Node<T>* newNode = new Node<T>(value);
			newNode->next = temp;
			newNode->prev = temp->prev;
			temp->prev->next = newNode;
		}
	}

	void RemoveFromFront()
	{
		if (!isEmpty())
		{
			if (head->next != nullptr)
			{
				head->next->prev = nullptr;
				head = head->next;
			}
			else
			{
				head = nullptr;
			}

		}
	}

	void RemoveFromTail()
	{
		if (!isEmpty())
		{
			tail->prev->next = nullptr;
			tail = tail->prev;
		}
	}

	void RemoveAt(T value)
	{
		int count = 0;
		Node<T>* temp = head;
		while (temp->data != value)
		{
			temp = temp->next;
			count++;
		}
		if (count == 0)
		{
			RemoveFromFront();
		}
		else if (temp == tail)
		{
			RemoveFromTail();
		}
		else
		{
			temp->next->prev = temp->prev;
			temp->prev->next = temp->next;
			delete temp;
		}
	}

	void Splice(dLinkedList<T> L, T value)
	{
		Node<T>* temp = head;
		while (temp->data != value)
		{
			temp = temp->next;
		}
		if (temp == tail)
		{
			temp->next = L.head;
			L.head->prev = temp;
		}
		else
		{
			L.head->prev = temp;
			temp->next->prev = L.tail;
			L.tail->next = temp->next;
			temp->next = L.head;
		}

	}

	int getSize()
	{
		int size = 0;
		Node<T>* temp = head;
		while (temp != nullptr)
		{
			size++;
			temp = temp->next;
		}
		return size;
	}

	T operator [](int index)
	{
		if (index >= 0 && index < getSize())
		{
			Node<T>* temp = head;
			for (int i = 0;i < index;i++)
			{
				temp = temp->next;
			}
			return temp->data;
		}
		return nullptr;
	}
};