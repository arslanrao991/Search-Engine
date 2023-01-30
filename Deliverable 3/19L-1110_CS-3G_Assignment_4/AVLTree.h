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

	//constructors and destructor
	AVLTree<k>()
	{
		root=nullptr;
	}
	AVLTree(const AVLTree& rhs)
	{
		root=nullptr;
		CopyTree(rhs.root);
	}
	~AVLTree()
	{
		ANode *temp=root;
		DelAVLTree(temp);
	}

	ANode* Insert(k  data, ANode *temp)
	{
		//inserting new value
		if (temp == nullptr)
		{
			ANode* newNode = new ANode;
			newNode->data=data;
			return newNode;
		}

		//reaching to the desired node
		if (temp->data > data)
			temp->leftChild = Insert(data, temp->leftChild);
		else if (temp->data < data )
			temp->rightChild = Insert(data, temp->rightChild);
		else 
			return temp;

		//updating height of node
		temp->height = MaxNum(Height(temp->leftChild), Height(temp->rightChild))+1;

		//get balance factor to maintain AVL Tree
		int balance = GetBalanceFactor(temp);

		//Rotation if required to maintain AVL Tree
		if (balance > 1 && data < temp->leftChild->data)
			return RightRotate(temp);
		else if (balance < -1 && data > temp->rightChild->data)
			return LeftRotate(temp);

		if (balance > 1 && data > temp->leftChild->data)  
		{  
			temp->leftChild = LeftRotate(temp->leftChild);  
			return RightRotate(temp);  
		} 
		if (balance < -1 && data < temp->rightChild->data)
		{
			temp->rightChild = RightRotate(temp->rightChild);
			return LeftRotate(temp);
		}

		//return node after updation
		return temp;

	}
	void Insert(k  data)
	{
		root = Insert(data, root);
	}

	//search node of a data and return it
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
	

	//print data in ascending order
	void PrintInOrder(ANode *temp) const
	{
		if (temp!=nullptr)
		{
			PrintInOrder(temp->leftChild);
			cout<<temp->height<<" ";
			cout<<temp->data;
			PrintInOrder(temp->rightChild);
		}
	}
	void PrintInOrder() const
	{
		ANode *temp=root;
		PrintInOrder(temp);
	}
	
	//return no of nodes in a Tree
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

	//return height of a node
	int Height(ANode *temp)
	{
		if (temp==nullptr)
			return -1;
		return temp->height;
	}

	//return balancing factor of a node
	int GetBalanceFactor(ANode* node)
	{
		if (node==nullptr)
			return 0;
		return (Height(node->leftChild)-Height(node->rightChild));
	}

	//delete AVL Tree nodes
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
	
	//Right rotation of node
	ANode* RightRotate(ANode *temp)
	{
		ANode *temp2=temp->leftChild;
		ANode* temp3=temp2->rightChild;

		temp2->rightChild=temp;
		temp->leftChild=temp3;

		temp->height= MaxNum (Height(temp->leftChild), Height(temp->rightChild))+1;
		temp2->height= MaxNum (Height(temp2->leftChild), Height(temp2->rightChild))+1;

		return temp2;

	}
	//Left rotation of node
	ANode* LeftRotate(ANode *temp)
	{
		ANode *temp2=temp->rightChild;
		ANode* temp3=temp2->leftChild;

		temp2->leftChild=temp;
		temp->rightChild=temp3;

		temp->height= MaxNum (Height(temp->leftChild), Height(temp->rightChild))+1;
		temp2->height= MaxNum (Height(temp2->leftChild), Height(temp2->rightChild))+1;

		return temp2;
	}

	//Copy AVL Tree
	void CopyTree(ANode* tempNode)
	{
		if (tempNode != nullptr)
		{
			Insert(tempNode->data);
			CopyTree(tempNode->leftChild);
			CopyTree(tempNode->rightChild);
		}
	}


void print2DUtil(ANode *root, int space = 5)
{
    const int COUNT = 10;
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->rightChild, space);

    // Print current node after space
    // count
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << "h:"<<root->height<<" " <<" "<< root->data;

    // Process left child
    print2DUtil(root->leftChild, space);
}
};
