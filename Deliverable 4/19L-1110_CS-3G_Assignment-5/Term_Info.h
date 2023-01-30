//Muhammad Arslan Tariq
//19L-1110
//CS-3G

#pragma once
#include <iostream>
#include "globalFunctions.h"
#include "List.h"
#include "Doc_Info.h"
using namespace std;

class Term_Info
{
protected:
	char* keyTerm;
	List<Doc_Info> docs;
public:
	Term_Info()
	{
		keyTerm=nullptr;
	}
	Term_Info(Term_Info &rhs)
	{
		this->keyTerm=GetString(rhs.keyTerm);
		this->docs=rhs.docs;
	}
	~Term_Info()
	{
		if (keyTerm!=nullptr)
			delete []keyTerm;
	}

	//Getters and Setters
	void SetKeyTerm(char* term)
	{
		keyTerm=GetString(term);
	}
	char* GetKeyTerm()		{return keyTerm;}
	Term_Info& GetTerm()	{return *this;}
	List<Doc_Info>& GetDocList()	{return docs;}

	//SearchDoc() searches the given name doc in the list of docs and return thier address if find or return null Doc_Info obj if not find
	Doc_Info& SearchDoc(char* name)
	{
		List<Doc_Info>::Iterator itr=docs.Begin();
		for (;itr!=docs.End();++itr)
		{
			if (!strcmp(itr.curr->data.GetDocID(),name))
				return *itr;
		}
		return *itr;
	}

	//UpdateDocsInfo call the SearchDoc() to find if the list contain doc if it finds then increses their frequency
	//of if not found doc (with the given name) then adds it
	void UpdateDocsInfo(char* name, int frequency=1)
	{
		//if ptr->GetDocTerm() != nullptr means passing Doc exist in query documnet list
		Doc_Info* ptr=&(SearchDoc(name));
		if (ptr->GetDocID()==nullptr)
		{
			Doc_Info tempElement;
			tempElement.SetDocID(name);
			tempElement.SetFrequency(frequency);
			docs.InsertAtEnd(tempElement);
		}
		else 
		{
			ptr->SetFrequency(ptr->GetFrequency()+frequency);
		}
	}

	friend ostream& operator<<(ostream &out, Term_Info& obj)
	{
		out<<obj.keyTerm<<"  ";
		//obj.docs.Print();
		//out<<endl;
		return out;
	}
	Term_Info& operator=(Term_Info& rhs)
	{
		this->keyTerm=GetString(rhs.keyTerm);
		this->docs=rhs.docs;
		return *this;
	}

	friend class Search_Engine;
	friend class HashTable;

};
