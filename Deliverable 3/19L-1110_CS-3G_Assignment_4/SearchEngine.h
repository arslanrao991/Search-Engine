//Muhammad Arslan Tariq
//19L-1110
//CS-3G

#pragma once
#include <iostream>
#include <fstream>
#include "Term_Info.h"
#include "AVLTree.h"
using namespace std;

class Search_Engine
{
private:
	AVLTree<Term_Info>* index;
public:
	//constructors and destructor
	Search_Engine()
	{
		index=new AVLTree<Term_Info>;
	}
	Search_Engine(Search_Engine & rhs)
	{
		index=rhs.index;
	}
	~Search_Engine()
	{
		delete index;
	}

	AVLTree<Term_Info>::ANode* SearchTerm(AVLTree<Term_Info>::ANode& name)
	{
		AVLTree<Term_Info>::ANode* ptr = index->Search(name.data);
		return ptr;
	}
	AVLTree<Term_Info>& GetIndex()	{return *index;}

	//UpdateIndexInfo call the SearchTerm() to find if the list contain keyterm and if it finds then calls the UpadteDocsInfo(fileName)
	//of if not found keyterm then adds it in the list
	void UpdateIndexInfo(char* name, char* docName)
	{
		//if ptr->GetKeyTerm() != nullptr means passing query(passing in SearchTerm()) exist in index
		AVLTree<Term_Info>::ANode temp;
		temp.data.SetKeyTerm(name);
		AVLTree<Term_Info>::ANode *ptr = SearchTerm(temp);
		if (ptr != nullptr && ptr->data.GetKeyTerm() != nullptr)
		{
			ptr->data.UpdateDocsInfo(docName);
		}
		else
		{
			Term_Info tempElement;
			tempElement.SetKeyTerm(name);
			tempElement.UpdateDocsInfo(docName);
			index->Insert(tempElement); 

		}
	}

	//AddDocIndex() insert the words of given file name into the array Index in such a way that
	//each unique term exists only one in the index.
	void AddDocToIndex(char* fileName)
	{
		
		ifstream document;
		document.open(fileName);
		char word[20];
		if (document)
		{
			cout<<"*****Reading "<<fileName<<" Done *****"<<endl;
			while (!document.eof())
			{
				document>>word;
				ConvertStrIntoSmallLetter(word);
				UpdateIndexInfo(word, fileName);
			}
			document.close();
		}
	}

	//CreateIndex() take arr of docs name and for each doc call the AddDocToIndex()
	void CreateIndex(char** docs, int n)
	{
		for (int i=0;i<n;i++)
		{
			AddDocToIndex(docs[i]);
		}
	}

	//SearchDocumnets()Tokenize the given query words with space and search in which docs they have occurred 
	//SearchDocument() also create parallel array of type(int) which store no of occurence of keyterms
	void SearchDocuments(char* queryWords)
	{
		Term_Info* searchQueryList=new Term_Info;	//Maintain a list of unique docs containing query words	
		searchQueryList->SetKeyTerm(queryWords);	//set keyterm to the seach queryWords

		int queryOccurence[100]={0};				//parallel arr that stores No.of occurence of queries in documnets
		int queryOccurenceIndex=0;

		AVLTree<Term_Info>::ANode* ptr;								//temporary ptr to store address of Search keyterm in index
		char word[20];
		int index=0;
		List<Doc_Info>::Iterator itr;
		List<Doc_Info>::Iterator itr2; 
		int i, j;
		AVLTree<Term_Info>::ANode tempTerm;

		//Search queries until the queries ends
		while (queryWords[index]!='\0')
		{
			//Tokenize the words seprated by white space and store one query in word(char[]) obj at one time
			for (i=0; queryWords[index]!=' ' && queryWords[index]!='\0';i++)
				word[i]=queryWords[index++];
			if (queryWords[index]!='\0')
				index++;
			word[i]='\0';
			//filter sensitive case letters
			ConvertStrIntoSmallLetter(word);

			//if ptr->GetKeyTerm() != nullptr means passing query(passing in SearchTerm()) exist in index
			tempTerm.data.SetKeyTerm(word);
			ptr=SearchTerm(tempTerm);
			if (ptr != nullptr)
			{
				if (ptr->data.GetKeyTerm()!=nullptr)
				{
					for (itr=ptr->data.GetDocList().Begin();itr!=ptr->data.GetDocList().End();++itr)
					{
						//Update the list of docs of search query if list has already the doc then 
						//it increases the frequency(called collective frequency in that case)
						searchQueryList->UpdateDocsInfo(itr.curr->data.GetDocID(),itr.curr->data.GetFrequency());

						//iteratre the list and increament j(by 1) in every case until it find the required doc
						itr2=searchQueryList->GetDocList().Begin();
						for (j=0; itr2!=searchQueryList->GetDocList().End();++itr2)
						{
							if (!strcmp(itr.curr->data.GetDocID(),itr2.curr->data.GetDocID()))
								break;
							j++;
						}
						//increament the No. of occurence of query in document 
						queryOccurence[j]=queryOccurence[j]+1;
					}				
				}
			}
		}
		//passing the search querie's documnet list to rank it according to the ranking rules and get it 
		searchQueryList=Ranking(searchQueryList, queryOccurence);

		//printing the ranked documnet list
		cout<<"***Searched queries have found in these documents*** \n";
		itr2=searchQueryList->GetDocList().Begin();
		if (itr2 != searchQueryList->GetDocList().End())
		{
			for (; itr2!=searchQueryList->GetDocList().End();++itr2)
				cout<<*itr2;
			cout<<endl<<endl;
		}
		else
			cout<<"***No such query found***\n";

		//deleting the dynamic memory allocation
		delete searchQueryList;
	}

	//Ranking() rank the list according to the given ranking rules and return the ranked Document list
	Term_Info* Ranking(Term_Info * searchQueryList, int queryOccurence[])
	{
		Term_Info* rankedDocList=new Term_Info;		//new ranked list of Docs according to the ranking rules
		rankedDocList->SetKeyTerm(searchQueryList->GetKeyTerm());

		List<Doc_Info>::Iterator top;
		List<Doc_Info>::Iterator itr;
		int sizeOfQueryOccArr=0;
		int index=0;

		//As queryOccurence array is the parallel array of Doc list containing queries 
		//so we can find No. of docs from this list in sizeOfQueryOccArr
		for (;queryOccurence[sizeOfQueryOccArr]!=0;sizeOfQueryOccArr++);

		for (int i=0;i<sizeOfQueryOccArr;i++)
		{
			top=searchQueryList->GetDocList().Begin();
			itr=searchQueryList->GetDocList().Begin()->next;
			index=0;

			for (int j=1;j<sizeOfQueryOccArr;j++)
			{
				//if doc with greater No. of queries found then top(iterator) will be set to that Documnet
				if (queryOccurence[index]<queryOccurence[j])
				{
					top=itr;
					index=j;
				}
				else if (queryOccurence[index] == queryOccurence[j] && queryOccurence[index] != 0 && queryOccurence[j] != 0)
				{
					//If two documents have the same number of query terms then rank the document
					//higher that has higher collective term frequency or 
					if (itr.curr->data.GetFrequency() > top.curr->data.GetFrequency())
					{
						top=itr;
						index=j;
					}
					//If two documents have the same number of query terms and the same collective
					//term frequency then rank the document alphabetically by Doc ID
					else if (top.curr->data.GetFrequency() == itr.curr->data.GetFrequency())
					{
						if (!strcmp(GetSmallerStr(top.curr->data.GetDocID(), itr.curr->data.GetDocID()),itr.curr->data.GetDocID()))
						{
							top=itr;
							index=j;
						}
					}
				}
				//if during compare operation searched queryOccurence has 0 on its index then it means 
				//it is already ranked and stored in rankedDocList
				else if (queryOccurence[index] == 0 && queryOccurence[j] == 0)
				{
					top=top.curr->next;
					index++;
				}
				++itr;
			}
			//insert the top doc(according to ranking rules) into rankedDocList
			rankedDocList->docs.InsertAtEnd(top.curr->data);
			//set the parallel queryOccurence[RankingDoc]=0 so that it can't be check again
			queryOccurence[index]=0;
		}
		//deleting the previous searchDocList and return the new ranked list
		delete searchQueryList;
		return rankedDocList;
	}

	void ClearAllRecord()
	{
		delete index;
		index=new AVLTree<Term_Info>;
		cout<<"***Cleared All Record***\n";
	}

};