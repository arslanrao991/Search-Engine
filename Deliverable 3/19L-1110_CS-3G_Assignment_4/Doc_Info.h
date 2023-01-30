//Muhammad Arslan Tariq
//19L-1110
//CS-3G

#pragma once
#include <iostream>
#include "globalFunctions.h"
using namespace std;


class Doc_Info
{
protected:
	char* docID;	// name/docID
	int frequency;	//No. of query occurence in this document
public:
	Doc_Info()
	{
		docID=nullptr;
		frequency=0;
	}
	Doc_Info(Doc_Info const& rhs)
	{
		this->docID=GetString(rhs.docID);
		this->frequency=rhs.frequency;
	}
	~Doc_Info()
	{
		if (docID!=nullptr)
			delete []docID;
	}
	
	//Getters and Setters
	void SetDocID(char* str)
	{
		
		docID=GetString(str);
	}
	void SetFrequency(int frq)
	{
		frequency=frq;
	}
	char* GetDocID()		{return docID;}
	int GetFrequency()		{return frequency;}

	Doc_Info& operator=(Doc_Info const &rhs)
	{
		if (docID!=nullptr)
			delete []docID;
		docID=GetString(rhs.docID);
		frequency=rhs.frequency;
		return *this;
	}
	friend ostream& operator<<(ostream &out, Doc_Info& obj)
	{
		out<<obj.docID<<"  "<<obj.frequency<<" | ";
		return out;
	}

};