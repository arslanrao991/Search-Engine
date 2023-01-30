//Muhammad Arslan Tariq
//19L-1110
//CS-3G

#include <iostream>
#include "SearchEngine.h"

using namespace std;


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
	
	//Printing Index
	eng.GetIndex().PrintInOrder();
	cout<<"Total Terms: "<<eng.GetIndex().NoOfNodes()<<endl;


	//User Interface Menus
	while (choice!=0)
	{
		cout<<"Press 1- Search Query\n";
		//cout<<"Press 2- Add Another Text File\n";
		cout<<"Press 3- Clear All Record\n";
		cout<<"Press 0- To Exit\n";
		cout<<"Your Choice: ";
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
		/*else if (choice==2)
		{
			cout<<"Enter File Name with extension: ";
			cin>>str;
			eng.AddDocToIndex(str);
			for (it=eng.GetIndex().Begin();it != eng.GetIndex().End();++it)
				cout<<*it;
		}*/
		else if (choice==3)
			eng.ClearAllRecord();
	}

	for (int i=0;i<totalDocs;i++)
		delete []docs[i];
	delete[] docs;
	system("pause");
	return 0;
}