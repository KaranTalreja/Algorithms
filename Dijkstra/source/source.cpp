#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
using namespace std;
#define getcx getchar_unlocked
#define noOfNodes 200
inline void inp( int &n );//fast input function
inline int getInt(char **str);
inline void inpLine(char* str);
class node;
class heapMin;
class edge;
class heapMin
{
	std::vector<node*> heap;
	int size;
public:
	heapMin()
{
		size = 0;
}
	void insert(node*);
	node* extractMin();
	void deleteNode(node*);
	void decompile();
	int getSize()
	{return size;}
	void freeHeap();
	bool check(node*);
};
class node {

public:
	unsigned int data;
	unsigned int Id;
	int indexInHeap;
	bool explored;
	vector<edge*> edges;
	node(int data,int Id)
	{
		this->data = data;
		this->Id = Id;
		indexInHeap = -1;
		explored = false;
	}
	node();
};
class edge
{
public:
	node* first;
	node* second;
	unsigned int   weight;
	edge();
	edge(node* first,node* second, unsigned int weight)
	{
		this->first = first;
		this->second = second;
		this->weight = weight;
	}

};
int main()
{
	vector<node*> *Graph;
	Graph = new vector<node*>(noOfNodes);
	node* tempNodeStart,*tempNodeEnd;
	edge* tempEdge,*tempEdge2;
	int tempNodeStartVal,tempNodeEndVal,weight;
	char line[1000],*temp;
	temp = line;
	for(int i=0;i<noOfNodes;i++)
	{
		temp = line;
		inpLine(temp);
		tempNodeStartVal = getInt(&temp);
		tempNodeStart = (NULL == (*Graph)[tempNodeStartVal-1]) ? new node(10000000,tempNodeStartVal-1) : (*Graph)[tempNodeStartVal-1];
		while((strlen(temp)-2))
		{
			tempNodeEndVal =getInt(&temp);
			weight = getInt(&temp);
			tempNodeEnd = (NULL == (*Graph)[tempNodeEndVal-1]) ? new node(10000000,tempNodeEndVal-1) : (*Graph)[tempNodeEndVal-1];
			tempEdge = new edge(tempNodeStart,tempNodeEnd,weight);
			tempEdge2 = new edge(tempNodeEnd,tempNodeStart,weight);
			tempNodeStart->edges.push_back(tempEdge);
			tempNodeEnd->edges.push_back(tempEdge2);
			(*Graph)[tempNodeEndVal-1] = tempNodeEnd;
		}
		(*Graph)[tempNodeStartVal-1] = tempNodeStart;
	}
	heapMin heap;
	node * Source = NULL;
	(*Graph)[0]->data = 0;
	heap.insert((*Graph)[0]);
	vector<edge*>::iterator iter;
	for(int i=0;i<noOfNodes;i++)
	{
		if(heap.getSize() > 0)
		{
			Source = heap.extractMin();
			heap.deleteNode(Source);
		}
		if(NULL != Source)
		{
			Source->explored = true;
			iter = Source->edges.begin();
			for(;iter!=Source->edges.end();++iter)
			{
				tempEdge = (*iter);
				tempNodeEnd = tempEdge->second;
				if((tempNodeEnd->explored == false))
				{
					if((Source->data + tempEdge->weight < tempNodeEnd->data))
					{
						if(tempNodeEnd -> indexInHeap >= 0)
							heap.deleteNode(tempNodeEnd);
						tempNodeEnd->data = Source->data + tempEdge->weight;
						heap.insert(tempNodeEnd);
					}
				}
			}
			Source = NULL;
		}
		else
			cout<<"Graph Not Connected"<<endl;
	}


	int arr[10] = {7,37,59,82,99,115,133,165,188,197};

	for(int k=0;k<10;k++)
		cout<<(*Graph)[arr[k]-1]->data<<',';
	cout<<endl;


	return 0;
}
inline int getInt(char **str)
{
	char ch = **str;int sign=1;
	int n=0;
	while( ch < '0' || ch > '9' ){if(ch=='-')sign=-1; ch=*(++(*str));}
	while(  ch >= '0' && ch <= '9' )
	{n = (n<<3)+(n<<1) + ch-'0'; ch = *(++(*str));}
	return (n*sign);
}
inline void inp( int &n )//fast input function
{
	n=0;
	register int ch=getcx();int sign=1;
	while( ch < '0' || ch > '9' ){if(ch=='-')sign=-1; ch=getcx();}

	while(  ch >= '0' && ch <= '9' )
		n = (n<<3)+(n<<1) + ch-'0', ch=getcx();
	n=n*sign;
}
inline void inpLine(char *str)
{
	register char c = 0;
	register int i = 0;
	while (c < 33)
		c = getcx();
	while (c != '\n') {
		str[i] = c;
		c = getcx();
		i = i + 1;
	}
	str[i] = '\0';
}

void heapMin::insert(node* Edge)
{
	int parent,child;
	node* tempEdge;
	heap.push_back(Edge);
	Edge->indexInHeap = size;
	size++;
	child = size;
	parent = (child)/2;
	while((parent >=1) && (heap[parent-1]->data > heap[child-1]->data))
	{
		tempEdge = heap[child-1];
		heap[child-1] = heap[parent-1];
		heap[child-1]->indexInHeap = child - 1;
		heap[parent-1] = tempEdge;
		heap[parent-1]->indexInHeap = parent - 1;
		child = parent;
		parent = parent/2;
	}

}

node* heapMin::extractMin(void)
{
	if(!heap.empty())
		return heap[0];
	else
		return NULL;
}
void heapMin::deleteNode(node* del)
{
	node* tempEdge;
	int temp = del->indexInHeap + 1;
	int parent = del->indexInHeap + 1;
	tempEdge = heap[del->indexInHeap];
	heap[del->indexInHeap] = heap[size-1];
	heap[del->indexInHeap]->indexInHeap = del->indexInHeap;
	heap[size-1] = tempEdge;
	heap[size-1]->indexInHeap = size-1;
	vector<node*> :: iterator itr = heap.begin();
	itr = itr + size -1;
	size--;
	int child = temp;
	parent = (child)/2;
	while((parent >=1) && (heap[parent-1]->data > heap[child-1]->data))
	{
		tempEdge = heap[child-1];
		heap[child-1] = heap[parent-1];
		heap[child-1]->indexInHeap = child - 1;
		heap[parent-1] = tempEdge;
		heap[parent-1]->indexInHeap = parent - 1;
		child = parent;
		parent = parent/2;
	}
	child = temp;
	parent = temp;
	while(2*parent <= size)
	{
		if(2*parent != size)
		{
			child = (heap[(2*parent)-1]->data <= heap[(2*parent)]->data) ? 2*parent : 2*parent + 1;
			if(heap[child-1]->data < heap[parent-1]->data)
			{
				tempEdge = heap[child -1];
				heap[child - 1] = heap[parent - 1];
				heap[child-1]->indexInHeap = child-1;
				heap[parent - 1] = tempEdge;
				heap[parent-1]->indexInHeap = parent-1;
				parent = child;
			}
			else
				break;
		}
		else
		{
			child = 2*parent;
			if(heap[child-1]->data < heap[parent-1]->data)
			{
				tempEdge = heap[child -1];
				heap[child - 1] = heap[parent - 1];
				heap[child-1]->indexInHeap = child-1;
				heap[parent - 1] = tempEdge;
				heap[parent-1]->indexInHeap = parent-1;
				parent = child;
			}
			else
				break;
		}
	}

	(*itr)->indexInHeap = -1;
	heap.erase(itr);
}
void heapMin::decompile()
{
	for(vector<node*>::iterator itr = heap.begin();itr!=heap.end();itr++)
	{
		cout<<(*itr)->data<<" ";
	}
	cout<<endl;
	for(vector<node*>::iterator itr = heap.begin();itr!=heap.end();itr++)
	{
		cout<<(*itr)->indexInHeap<<" ";
	}
	cout<<endl;

}
bool heapMin::check(node* checkNode)
{
	bool leftTree = false,rightTree = false;
	int Id = checkNode->indexInHeap+1;
	unsigned int childLeft = Id*2;
	unsigned int childRight = Id*2 + 1;
	if(childLeft - 1 < heap.size())
		leftTree = check(heap[childLeft - 1]);
	else
	{
		if(heap[checkNode->indexInHeap]->data >= heap[(checkNode->indexInHeap-1)/2]->data)
			return true;
		else
			return false;
	}
	if(childRight - 1 < heap.size())
		rightTree = check(heap[childRight -1]);
	else
	{
		if(heap[checkNode->indexInHeap]->data >= heap[(checkNode->indexInHeap-1)/2]->data)
			return true;
		else
			return false;
	}
	if(leftTree == true && rightTree == true)
		return true;
	else
	{
		//cout<<"HEAP BREAKDOWN"<<endl;
		return false;
	}
}
