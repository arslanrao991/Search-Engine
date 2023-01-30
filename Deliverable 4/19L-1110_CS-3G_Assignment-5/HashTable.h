#pragma once

#include "Term_Info.h"
using namespace std;

class HashTable
{
private:
	List<Term_Info>* table;
	int maxSize;
	int tableSize;

	int hashing(char* term)
	{
		int index = (term[0] - 32);
		int size = strlen(term);

		for (int i=1; i < size ;i++)
			index = index + term[i];

		if (size % 2 == 0)
			return ((index+'0') % maxSize);
		
		return ((index+'1') % maxSize);
	}

public:
	//constructors and destructor
	HashTable()
	{
		table = new List<Term_Info>[13];
		maxSize = 13;
		tableSize = 0;
	}
	HashTable(int c)
	{
		table = new List<Term_Info>[c];
		maxSize = c;
		tableSize = 0;
	}
	HashTable(HashTable &rObj)
	{
		maxSize = 0;
		*this = rObj;
	}
	~HashTable()
	{
		delete []table;
		table = nullptr;
		maxSize = 0;
		tableSize = 0;
	}

	//required functions
	void GrowTable()
	{
		List<Term_Info>::Iterator itr;
		HashTable newTable(maxSize*2);

		for (int i=0;i<maxSize;i++)
		{
			itr = table[i].Begin();
			for (;itr != table[i].End();++itr)
				newTable.InsertTerm(*itr);
		}

		*this = newTable;
	}
	void InsertTerm(Term_Info term)
	{		
		if (tableSize+1 >= maxSize*2)
			GrowTable();
		tableSize++;
		int index = hashing(term.GetKeyTerm());
		table[index].InsertAtStart(term);
	}
	Term_Info& SearchTerm(char* term)
	{

		List<Term_Info>::Iterator itr = table[hashing(term)].Begin();
		itr.curr;
		for (;itr!=table[hashing(term)].End();++itr)
			if (!strcmp(itr.curr ->data.GetKeyTerm(), term))
				return *itr;

		return *itr;
	}
	void PrintTable()
	{
		for (int i=0; i<maxSize;i++)
		{
			cout<<i<<"\t";
			table[i].Print();
		}
		cout<<"Total Elements: "<<tableSize<<endl;
	}

	//operator overloading 
	HashTable& operator= (HashTable& rObj)
	{
		//deleting previous contents
		if (maxSize!=0)
			delete []table;

		//assigning R.H.S objs contents to L.H.S objs
		this->table = new List<Term_Info>[rObj.maxSize];
		this->maxSize = rObj.maxSize;
		this->tableSize = rObj.tableSize;
		for (int i=0;i<maxSize;i++)
		{
			table[i]=rObj.table[i];
		}

		return *this;
	}
};