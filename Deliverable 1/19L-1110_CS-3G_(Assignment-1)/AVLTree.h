#include <iostream>
#include <stack>
using namespace std;

template< typename k>
class AVLTree
{	
public:
	class ANode
	{
	public:
		int height;
		k data;
		ANode *leftChild;
		ANode *rightChild;
		ANode()
		{
			leftChild = rightChild = nullptr;
			height=0;
		}
		ANode(ANode& rhs)
		{
			data = rhs.data;
			leftChild = rhs.leftChild;
			rightChild = rhs.rightChild;
		}
	};

	ANode *root;

	AVLTree<k>()
	{
		root=nullptr;
	}
	~AVLTree()
	{
		ANode *temp=root;
		DelAVLTree(temp);
	}

	void Insert(k  data, ANode *temp)
	{

		if (data == temp->data)
		{
			temp->data=data;
		}
		else if (data > temp->data)
		{
			if (temp->rightChild==nullptr)
			{
				temp->rightChild=new ANode;
				temp=temp->rightChild;
				temp->data=data;
				temp->rightChild=temp->leftChild=nullptr;
			}
			else
				Insert(data, temp->rightChild);
		}
		else if (data < temp->data)
		{
			if (temp->leftChild==nullptr)
			{
				temp->leftChild=new ANode;
				temp=temp->leftChild;
				temp->data=data;
				temp->rightChild=temp->leftChild=nullptr;
			}
			else
				Insert(data, temp->leftChild);
		}
	}
	void Insert(k  data)
	{
		ANode *temp=root;
		if (root!=nullptr)
			Insert(data, temp);
		else
		{
			root=new ANode;
			root->data=data;
			root->rightChild=root->leftChild=nullptr;
		}

	}


	void Delete(k const data)
	{
		ANode* deletionNode = Search(data);
		if (deletionNode == NULL)
			return;
		if (deletionNode->leftChild != nullptr && deletionNode->rightChild != nullptr)
		{
			ANode* minimumValueNode = FindMin(deletionNode);
			ANode* parentNodeOfMinValue = GetParent(minimumValueNode);
			if (parentNodeOfMinValue->rightChild == minimumValueNode)
				parentNodeOfMinValue->rightChild = nullptr;
			else 
				parentNodeOfMinValue->leftChild = nullptr;
			ANode temp;
			temp.data = deletionNode->data;
			deletionNode->data = minimumValueNode->data;
			minimumValueNode->data = temp.data;
			delete minimumValueNode;

		}
		else if (deletionNode->rightChild == nullptr && deletionNode->leftChild != nullptr)
		{
			if (deletionNode == root)
			{
				root = deletionNode->leftChild;
				delete deletionNode;
				return;
			}
			ANode *temp = GetParent(deletionNode);
			if (deletionNode->data > temp->data)
				temp->rightChild = deletionNode->leftChild;
			else 
				temp->leftChild = deletionNode->leftChild;
			delete deletionNode;
		}
		else if (deletionNode->leftChild == nullptr && deletionNode->rightChild != nullptr)
		{
			if (deletionNode == root)
			{
				root = deletionNode->rightChild;
				delete deletionNode;
				return;
			}
			ANode *temp = GetParent(deletionNode);
			if (deletionNode->data > temp->data)
				temp->rightChild = deletionNode->rightChild;
			else 
				temp->leftChild = deletionNode->rightChild;
			delete deletionNode;
		}
		else 
		{
			if (deletionNode == root)
			{
				delete deletionNode;
				root = nullptr;
				return;
			}
			ANode* temp = GetParent(deletionNode);
			if (temp->rightChild == deletionNode)
				temp->rightChild = nullptr;
			else
				temp->leftChild = nullptr;
			delete deletionNode;
		}
	}


	ANode* GetParent(ANode* child)
	{
		ANode* temp=root;
		while (temp->leftChild != child && temp->rightChild != child)
		{
			if (child->data > temp->data)
				temp = temp->rightChild;
			else 
				temp = temp->leftChild;
		}
		return temp;
	}


	ANode* FindMin(ANode* temp)
	{
		temp=temp->rightChild;
		if (temp!=nullptr)
		while (temp->leftChild != nullptr)
			temp=temp->leftChild;
		return temp;
	}


	ANode* Search(k data, ANode *temp)
	{
		if (temp == nullptr)
			return NULL;
		else if (temp->data == data)
			return temp;		
		else
		{
			if (data > temp->data)
				return Search(data, temp->rightChild);
			else
				return Search(data, temp->leftChild);
		}
	}
	ANode* Search(k data)
	{
		ANode *temp=root;
		return Search(data, temp);
	}
	

	void PrintInOrder(ANode *temp) const
	{
		if (temp!=nullptr)
		{
			PrintInOrder(temp->leftChild);
			cout<<temp->data;
			PrintInOrder(temp->rightChild);
		}
	}
	void PrintInOrder() const
	{
		ANode *temp=root;
		PrintInOrder(temp);
	}
	

	void NoOfNodes(ANode *temp, int &noOfNodes) const
	{
		if (temp!=nullptr)
		{
			NoOfNodes(temp->leftChild, noOfNodes);
			noOfNodes++;
			NoOfNodes(temp->rightChild, noOfNodes);
		}
	}
	int NoOfNodes() const
	{
		ANode *temp=root;
		int noOfNodes=0;
		NoOfNodes(temp, noOfNodes);
		return noOfNodes;
	}


	void HeightOfAVLTree(ANode *temp, int &height, int count=0) const
	{
		
		if (temp!=nullptr)
		{

			if (temp->leftChild!=nullptr)
			{
				HeightOfAVLTree(temp->leftChild, height, count+1);
			}
			if (temp->rightChild!=nullptr)
			{
				HeightOfAVLTree(temp->rightChild, height, count+1);
			}
		}
		if (count > height)
			height=count;	
	}
	int HeightOfAVLTree(ANode *temp=nullptr) const
	{
		if (temp==nullptr)
			temp=root;
		int height=0;
		HeightOfAVLTree(temp, height, 0);
		return height;
	}


	void DelAVLTree(ANode *temp)
	{
		if (temp!=nullptr)
		{
			if (temp->leftChild!=nullptr)
				DelAVLTree(temp->leftChild);
			if (temp->rightChild!=nullptr)
				DelAVLTree(temp->rightChild);
		}
		delete temp;
	}
	

	ANode* RightRotate(ANode *temp)
	{
		ANode *temp2=temp->rightChild;
		temp->rightChild=temp2->leftChild;
		temp2->leftChild=temp;
		temp=temp2;
		return temp;
	}
	ANode* LeftRotate(ANode *temp)
	{
		ANode *temp2=temp->leftChild;
		temp->leftChild=temp2->rightChild;
		temp2->rightChild=temp;
		temp=temp2;
		return temp;
	}
};
