#include <iostream>
#include <string>
#include <fstream>
using namespace std;

template <class T>
class Stack
{
private:
	class Node
	{
	public:
		T data;
		Node* nextNode;
		Node()
		{
			data=NULL;
			nextNode=nullptr;
		}
		Node (Node& rhs)
		{
			data=rhs.data;
			nextNode=rhs.nextNode;
		}
		Node& operator=(Node& rhs)
		{
			data=rhs.data;
			nextNode=rhs.nextNode;
		}
		~Node()
		{
			nextNode=nullptr;
		}
	};
	Node* head;
	Node* tail;
	int size;
public:
	Stack()
	{
		head = nullptr;
		tail = nullptr;
		size=0;
	}
	Stack(const Stack& obj)
	{
		Node* temp=obj.head;
		while (temp!=nullptr)
		{
			Push(temp->data);
			temp=temp->nextNode;
		}
		this->size=obj.size;
	}
	~Stack()
	{
		while (size != 0)
			Pop();
		size=0;
	}

	void Push(T value)
	{
		bool isFirstValue = false;
		if (head == nullptr && tail == nullptr)
			isFirstValue = true;
		Node* temp = head;
		head = new Node;
		head->data = value;
		head->nextNode = temp;
		if (isFirstValue == true)
			tail = head;
		size++;
	}
	void Pop()
	{
		if (head != nullptr && head != tail)
		{
			Node* temp = head;
			head = head->nextNode;
			delete temp;
			if (head == nullptr)
				tail = nullptr;
			size--;
		}
		else if (head == tail)
		{
			delete head;
			head = tail = nullptr;
			size--;
		}
		else
			cout << "Empty stack!\n";
	}
	T Top()	
	{
		if (head!=nullptr)
			return head->data;
		else 
		{
			cout<<"Empty Stack!\n";
			return NULL;
		}
	}
	int Size()	{return size;}
	bool IsEmpty()
	{
		return (size==0);
	}

	Node* Begin()
	{
		return head;
	}
	Node* End()
	{
		return tail;
	}
	void Print()
	{
		Node* tempPtr = head;
		if (head == nullptr && tail == nullptr)
			cout << "Empty Stack!\n";
		while (tempPtr != nullptr)
		{
			cout << *(tempPtr->data) << " ";
			tempPtr = tempPtr->nextNode;
		}
		cout << endl;
	}

};
class Stage
{
private:
	string stageName;
	int timeToComplete;
	int points;

public:
	Stage(string name="", int time=0, int pnts=0)
	{
		this->stageName=name;
		this->timeToComplete=time;
		this->points=pnts;
	}
	Stage(const Stage& rhs)
	{
		this->stageName=rhs.stageName;
		this->timeToComplete=rhs.timeToComplete;
		this->points=rhs.points;
	}
	~Stage()
	{
		this->stageName="";
		this->points=0;
		this->timeToComplete=0;
	}
	void SetName(string name)
	{
		this->stageName=name;
	}
	void SetTime(int time)
	{
		this->timeToComplete=time;
	}
	void SetPoints(int pnts)
	{
		this->points=pnts;
	}
	string GetName()	{return stageName;}
	int GetTime()	{return timeToComplete;}
	int GetPoints()	{return points;}

	Stage& operator=(Stage& rhs)
	{
		if (this != &rhs)
		{
			this->stageName=rhs.stageName;
			this->timeToComplete=rhs.timeToComplete;
			this->points=rhs.points;
		}
		return *this;
	}

};

//Global Functions for helping puspose
int GetTotalTime(Stage stages[], int size)
{
	int time=0;
	for (int i=0;i<size;i++)
		time+=stages[i].GetTime();
	return time;
}
int GetTotalPoints(Stage stages[], int size)
{
	int points=0;
	for (int i=0;i<size;i++)
		points+=stages[i].GetPoints();
	return points;
}
void Print(Stage stages[], int size)
{
	for (int i=0;i<size;i++)
		cout<<stages[i].GetName()<<"   ";
	cout<<"\t\n";
}

//Part-a
void MindThrashingA(Stage* stages, int noOfStages, int timePlayerCanSpend)
{
	//Declarations
	Stage* subset=new Stage[noOfStages];
	Stage* bestChoice=nullptr;
	Stack<int>* subsetStack=new Stack<int>;
	Stack<int>* setStack=new Stack<int>;
	int heighestPoints=0;
	int noOfStagesToBePlayed=0;
	int totalTime=0;
	int subsetIndex=0;
	int setIndex=0;
	int count=0;

	while (count!=pow(2,noOfStages)-1)
	{
		//if setIndex!=lastIndex it increments the setIndex and subsetIndex to make subsets
		if (setIndex!=noOfStages)
		{
			subset[subsetIndex]=stages[setIndex];
			subsetStack->Push(subsetIndex);
			setStack->Push(setIndex);
			subsetIndex++;
			setIndex++;
		}
		//if setIndex==lastIndex then it check the newly made subset that if subset is suitable for player to play
		else if (setIndex==noOfStages)
		{
			totalTime=GetTotalTime(subset, subsetIndex);
			if (totalTime<=timePlayerCanSpend)
			{
				//if this newly made subset has greater points than previosly made best choice then best choice is set to newly made subset
				if (GetTotalPoints(subset, subsetIndex)>heighestPoints)
				{
					if (bestChoice!=nullptr)
						delete []bestChoice;
					bestChoice=new Stage[subsetIndex];
					for (int i=0;i<subsetIndex;i++)
						bestChoice[i]=subset[i];
					noOfStagesToBePlayed=subsetIndex;
					heighestPoints=GetTotalPoints(subset, subsetIndex);
				}
			}
			count++;

			subsetIndex=subsetStack->Top();
			setIndex=setStack->Top()+1;
			subsetStack->Pop();
			setStack->Pop();
		} 
	}

	//printing best choice
	cout<<"Best Choice: ";
	Print(bestChoice, noOfStagesToBePlayed);
	//deleting dynamic allocation
	delete []subset;
	delete []bestChoice;
	delete subsetStack;
	delete setStack;
}

//Part-b
void MindThrashingB(Stage* stages, int size, Stage* subset, int subsetIndex, int setIndex, int timePlayerCanSpend, Stage* bestChoice, int &noOfStagesToBePlayed, int& heighestPoints)
{
	//if setIndex==lastIndex then it check the newly made subset that if subset is suitable for player to play
	 if (setIndex==size)
	 {
		 if (GetTotalTime(subset,subsetIndex)<=timePlayerCanSpend)
		 {
			 //if this newly made subset has greater points than previosly made best choice then best choice is set to newly made subset
			 if (GetTotalPoints(subset, subsetIndex)>heighestPoints)
			 {
				for (int i=0;i<subsetIndex;i++)
					bestChoice[i]=subset[i];
				noOfStagesToBePlayed=subsetIndex;
				heighestPoints=GetTotalPoints(subset, subsetIndex);
			 }
		 }
		 return;
	 }
	 
	 subset[subsetIndex]=stages[setIndex];
	 MindThrashingB(stages, size, subset, subsetIndex+1,setIndex+1, timePlayerCanSpend, bestChoice, noOfStagesToBePlayed,heighestPoints); 
	 MindThrashingB(stages, size, subset, subsetIndex, setIndex+1, timePlayerCanSpend, bestChoice, noOfStagesToBePlayed,heighestPoints);

 }

void MindThrashingB(Stage stages[], int size, int timePlayerCanSpend)
{
	Stage* subsets=new Stage[size];
	Stage* bestChoice=new Stage[size];
	int noOfStagesToBePlayed=0;
	int heighestPoints=0;
	MindThrashingB(stages, size, subsets, 0, 0, timePlayerCanSpend, bestChoice, noOfStagesToBePlayed, heighestPoints);

	//printing best choice
	cout<<"Best Choice: ";
	Print(bestChoice, noOfStagesToBePlayed);
	
	//deleting dynamic allocation
	delete[] bestChoice;
	delete []subsets;
}


//reading stages information from file
void GetGameStagesFromFile(string fileName, Stage* &stages, int& totalStages, int& timePlayerCanSpend)
{
	ifstream infile;
	string tempStr;
	int temp;
	infile.open(fileName);
	if (infile)
	{
		infile>>totalStages;
		stages=new Stage[totalStages];
		for (int i=0;i<totalStages;i++)
		{
			infile>>tempStr;
			stages[i].SetName(tempStr);
			infile>>temp;
			stages[i].SetPoints(temp);
			infile>>temp;
			stages[i].SetTime(temp);
		}
		infile>>timePlayerCanSpend;

	}

}

int main()
{
	Stage* stages=nullptr;
	int totalStages=0;
	int timePlayerCanSpend;
	string fileName="stages.txt";

	GetGameStagesFromFile(fileName, stages, totalStages,timePlayerCanSpend);

	MindThrashingA(stages,totalStages,timePlayerCanSpend);	//Part-a
	MindThrashingB(stages,totalStages, timePlayerCanSpend);	//Part-b
	

	system("pause");
	return 0;
}