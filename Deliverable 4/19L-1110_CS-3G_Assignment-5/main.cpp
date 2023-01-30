//Muhammad Arslan Tariq
//19L-1110
//CS-3G

#include <iostream>
#include "SearchEngine.h"

using namespace std;

void Menu()
{
	cout<<"Press 1- Search Query\n";
	cout<<"Press 2- Add Another Text File\n";
	cout<<"Press 3- Print\n";
	cout<<"Press 4- Clear All Record\n";
	cout<<"Press 0- To Exit\n";
	cout<<"Your Choice: ";
}

int main()
{

	char str[100];
	Search_Engine eng;
	List<Term_Info>::Iterator it;
	int choice=-1;
	ifstream infile;
	int totalDocs;
	char** docs;

	//reading all file names from file called FilesName.txt
	infile.open("FilesName.txt");
	if (infile)
	{
		infile>>totalDocs;
		docs=new char*[totalDocs];
		for (int i=0;i<totalDocs;i++)
		{
			infile>>str;
			docs[i]=new char[30];
			StrCopy(docs[i], str);			
		}
	}

	//Creating Index
	eng.CreateIndex(docs, totalDocs);

	//printing index
	eng.GetIndex().PrintTable();

	//User Interface Menus
	while (choice!=0)
	{
		Menu();		
		if (cin)
			cin>>choice;
		cin.clear();
		if (choice==1)
		{
			cout<<"Enter your Query: ";
			cin.ignore(1,'\n');
			cin.getline(str,100,'\n');
			eng.SearchDocuments(str);
		}
		else if (choice==2)
		{
			cout<<"Enter File Name with extension: ";
			cin>>str;
			eng.AddDocToIndex(str);
			eng.GetIndex().PrintTable();
		}
		else if (choice==3)
			eng.GetIndex().PrintTable();
		else if (choice==4)
			eng.ClearAllRecord();
		
	}

	//deleting memory allocation
	for (int i=0;i<totalDocs;i++)
		delete []docs[i];
	delete[] docs;
	
	return 0;
}