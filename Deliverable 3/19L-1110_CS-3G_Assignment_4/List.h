//Muhammad Arslan Tariq
//19L-1110
//CS-3G

#pragma once
#include <iostream>
#include "Doc_Info.h"
#include "Term_Info.h"
using namespace std;
template <class T>
class List;
template <class T>
class Node
{
public:
	T data;
	Node* next;
	Node* previous;
	Node<T>& operator=(Node<T>& right)
	{
		if (this!=&right)
		{
			this=&right;
		}
		return *this;
	}
	friend class List<T>;
};
template <class T>
class List
{
private:
	Node<T>* head;
	Node<T>* tail;
	int size;
public:
	class Iterator
	{
	private:
		Node<T>* curr;
	public:
		Iterator(Node<T>* n=nullptr)
		{
			curr=n;
		}
		Iterator(Iterator const &right)
		{
			curr=right.curr;
		}
		Iterator & operator++() 
		{
			curr = curr->next;
			return *this;
		}
		Iterator & operator--() 
		{
			curr = curr->previous;
			return *this;
		}
		T& operator*()
		{
			return curr->data;
		}
		bool operator ==(const Iterator &obj)
		{
			return (curr==obj.curr);
		}
		bool operator!=(const Iterator& rhs)const 
		{
			if (curr != rhs.curr)
			return true;
			else return false;
		}
		Iterator* Begin()
		{
			Iterator *itr=(head->next);
			return itr;
		}
		Iterator* End()
		{
			Iterator *itr=(tail);
			return itr;
		}
		friend class Term_Info;
		friend class Search_Engine;
	};
	List()
	{
		head=new Node<T>;
		tail=new Node<T>;
		head->next=tail;
		tail->previous=head;
		head->previous=nullptr;
		tail->next=nullptr;
		size=0;
	}
	List(List const &right)
	{
		Node* temp=right->head;
		size=right.size;
		while(temp->next!=tail)
		{
			InsertAtEnd(temp->data);
			temp=temp->next;
		}
		
		
	}
	~List()
	{
		while (head->next!=tail)
			DeleteAtEnd();
	}
	void InsertAtStart(T element)
	{
		Node<T>* newNode=new Node<T>;
		newNode->data=element;
		newNode->next=head->next;
		newNode->previous=head;
		newNode->next->previous=newNode;
		head->next=newNode;
		size++;
	}
	void InsertAtEnd(T element)
	{
		Node<T>* newNode=new Node<T>;
		newNode->data=element;
		newNode->next=tail;
		newNode->previous=tail->previous;
		tail->previous=newNode;
		newNode->previous->next=newNode;
		size++;
	}
	void DeleteAtstart()
	{
		if (head->next!=tail)
		{
			Node<T>* temp=head->next;
			head->next=temp->next;
			head->next->previous=head;
			delete temp;
			size--;
		}
		else 
			cout<<"List is already Empty!\n";
	}
	void DeleteAtEnd()
	{
		if (head->next!=tail)
		{
			Node<T>* temp=tail->previous;
			tail->previous=temp->previous;
			tail->previous->next=tail;
			delete temp;
			size--;
		}
		else 
			cout<<"List is already Empty!\n";
	}
	void Reverse()
	{
		if (head->next!=tail)
		{
			Node<T>* temp1=head;
			Node<T>* temp2=head->next;
			while(temp1!=tail)
			{
				temp2=temp1->previous;
				temp1->previous=temp1->next;
				temp1->next=temp2;
				temp1=temp1->previous;
			}
			temp2=temp1->previous;
			temp1->previous=temp1->next;
			temp1->next=temp2;
			temp1=head;
			head=tail;
			tail=temp1;
		}
		else
			cout<<"List is already Empty!\n";		
	}
	void Print()
	{
		for (Node<T>* temp=head->next; temp->next!=nullptr;temp=temp->next)
			cout<<temp->data;
		cout<<endl;
	}
	void RemoveAllDuplicates()
	{
		if (head->next!=tail && head->next->next!=tail)
		{
			Node<T>* temp1=head->next;
			Node<T>* temp2;
			Node<T>* duplicate;
			Node<T>* temp3;
			bool found=false;
			for (;temp1!=tail;temp1=temp1->next)
			{
				temp2=temp1->next;
				for (; temp2!=tail;)
				{
					found=false;
					if (temp1->data==temp2->data)
					{
						found=true;
						temp2->next->previous=temp2->previous;
						temp2->previous->next=temp2->next;
						duplicate=temp2;
						temp3=temp2->next;
						delete duplicate;
						size--;
					}
					if (found==true)
						temp2=temp3;
					else 
						temp2=temp2->next;
				}
			}
		}
	}
	int GetSize()		{return size;}
	bool InsertBefore(T const v1, T const v2)
	{
		bool foundv2=false;
		Node<T>* temp=head->next;
		while(temp!=tail)
		{
			if (temp->data==v2)
			{
				foundv2=true;
				break;
			}
			temp=temp->next;
		}
		if (foundv2==true)
		{
			Node<T>* newNode=new Node<T>;
			newNode->data=v1;
			newNode->next=temp;
			newNode->previous=temp->previous;
			temp->previous->next=newNode;
			temp->previous=newNode;
			return true;
			size++;
		}
		return false;
	}
	Node<T>* Begin()
	{
		return head->next;
	}
	Node<T>* End()
	{
		return tail;
	}
	List& operator=(List& right)
	{
		Node<T>* temp=right.Begin();
		while(temp!=right.End())
		{
			InsertAtEnd(temp->data);
			temp=temp->next;
		}
		return *this;
	}

	friend class Term_Info;
	friend class Search_Engine;
};