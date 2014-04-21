/*
 * Utils.hpp
 *
 *  Created on: Apr 15, 2014
 *      Author: karant
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
namespace karanUtils
{
#define getcx getchar_unlocked
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
class baseNode;
class baseEdge;
class baseNode
{
public:
	unsigned int data; /*heapKey Or Dijkstra distance*/
	int indexInHeap;
	unsigned int Id;
	bool explored;
	baseNode(int data,int Id)
	{
		this->data = data;
		indexInHeap = -1;
		this->Id = Id;
		explored = false;
	}
	baseNode(int Id)
	{
		this->data = 10000000;
		indexInHeap = -1;
		this->Id = Id;
		explored = false;
	}
	baseNode();
};
class baseEdge
{
public:
	int weight;
	baseEdge();
	baseEdge(int weight)
	{
		this->weight = weight;
	}
};
template <typename keyType, typename valueType>
class heapMin
{
	std::vector<valueType *> heap;
	int size;
	keyType (*getData) (valueType);
public:
	heapMin()
{
		size = 0;
		getData = NULL;
}
	heapMin(keyType (*funcP) (valueType))
	{
		size = 0;
		getData = funcP;
	}
	void insert(valueType *);
	valueType* extractMin();
	void deleteNode(valueType *);
	void decompile();
	int getSize()
	{return size;}
	void freeHeap();
	bool check(valueType *);
};

template <typename keyType, typename valueType>
void heapMin<keyType, valueType>::insert(valueType* Edge)
{
	int parent,child;
	valueType* tempEdge;
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

template <typename keyType, typename valueType>
valueType* heapMin<keyType, valueType>::extractMin(void)
{
	if(!heap.empty())
		return heap[0];
	else
		return NULL;
}
template <typename keyType, typename valueType>
void heapMin<keyType, valueType>::deleteNode(valueType* del)
{
	valueType* tempEdge;
	int temp = del->indexInHeap + 1;
	int parent = del->indexInHeap + 1;
	tempEdge = heap[del->indexInHeap];
	heap[del->indexInHeap] = heap[size-1];
	heap[del->indexInHeap]->indexInHeap = del->indexInHeap;
	heap[size-1] = tempEdge;
	heap[size-1]->indexInHeap = size-1;
	typename vector<valueType* > :: iterator itr;
	itr = heap.begin();
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
	valueType* tempNode;
	tempNode = *itr;
	tempNode->indexInHeap = -1;
	heap.erase(itr);
}
template <typename keyType, typename valueType>
void heapMin<keyType, valueType>::decompile()
{
	valueType* tempNode;
	for(typename vector<valueType* >::iterator itr = heap.begin();itr!=heap.end();itr++)
	{
		tempNode = *itr;
		cout<<tempNode->data<<" ";
	}
	cout<<endl;
	for(typename vector<valueType* >::iterator itr = heap.begin();itr!=heap.end();itr++)
	{
		tempNode = *itr;
		cout<<tempNode->indexInHeap<<" ";
	}
	cout<<endl;

}
template <typename keyType, typename valueType>
bool heapMin<keyType, valueType>::check(valueType* checkNode)
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

template<typename nodeType,typename edgeType>
bool Dijkstra (vector<nodeType*> *Graph, size_t indexOfSourceNode, size_t indexOfDestinationNode)
{
	heapMin<unsigned int, nodeType> heap;
	nodeType* Source = NULL;
	edgeType* tempEdge = NULL;
	nodeType* tempNodeEnd = NULL;
	(*Graph)[indexOfSourceNode]->data = 0;
	heap.insert((*Graph)[indexOfSourceNode]);
	typename vector<edgeType*>::iterator iter;
	int noOfNodes = Graph->size();
	for(int i=0;i<noOfNodes;i++)
	{
		if(heap.getSize() > 0)
		{
			Source = heap.extractMin();
			heap.deleteNode(Source);
		}
		if(NULL != Source)
		{
			if((indexOfDestinationNode != -1) && ((*Graph)[indexOfDestinationNode] == Source))
				return true;
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
						tempNodeEnd->visitedBy = tempEdge;
						heap.insert(tempNodeEnd);
					}
				}
			}
			Source = NULL;
		}
		else
			return false;
	}
	return true;
}
template<typename nodeType, typename edgeType>
edgeType* getDuplicateEdge(nodeType* startNode, nodeType* endNode)
{
	size_t noOfEdges = startNode->edges.size();
	edgeType* tempEdge;
	for(size_t i =0 ;i< noOfEdges;i++)
	{
		tempEdge = startNode->edges[i];
		if(tempEdge->first == startNode && tempEdge->second == endNode)
			return tempEdge;
	}
	return NULL;
}
template <typename nodeType, typename edgeType>
void readEdgesForGraph (vector<nodeType*> *Graph, int noOfNodes, int noOfEdges, bool isDirectedGraph , bool printGraph = false)
{
	edgeType *tempEdge,*tempEdge2;
	nodeType *tempNodeStart,*tempNodeEnd;
	int tempNodeStartVal,tempNodeEndVal,tempWeight;
	if(printGraph == true) printf("%d %d\n", noOfNodes, noOfEdges);
	for(int i = 0; i<noOfEdges;i++)
	{
		inp(tempNodeStartVal);inp(tempNodeEndVal);inp(tempWeight);
		if(tempNodeStartVal == tempNodeEndVal) continue; //Duplicate edges
		if(printGraph == true) printf("%d %d %d\n", tempNodeStartVal, tempNodeEndVal, tempWeight);
		tempNodeStart = (NULL == (*Graph)[tempNodeStartVal-1]) ? new nodeType(tempNodeStartVal) : (*Graph)[tempNodeStartVal-1];
		tempNodeEnd = (NULL == (*Graph)[tempNodeEndVal-1]) ? new nodeType(tempNodeEndVal) : (*Graph)[tempNodeEndVal-1];
		tempEdge = getDuplicateEdge<nodeType, edgeType>(tempNodeStart, tempNodeEnd);
		if(NULL != tempEdge)
		{
			tempEdge->weight += tempWeight;
			tempEdge->residualCapacity = tempEdge->weight;
		}
		else
		{
			tempEdge = new edgeType(tempNodeStart,tempNodeEnd,tempWeight);
			tempNodeStart->edges.push_back(tempEdge);
		}
		if(false == isDirectedGraph)
		{
			tempEdge2 = getDuplicateEdge<nodeType, edgeType>(tempNodeEnd, tempNodeStart);
			if(NULL != tempEdge2)
			{
				tempEdge2->weight += tempWeight;
				tempEdge2->residualCapacity = tempEdge2->weight;
			}
			else
			{
				tempEdge2 = new edgeType(tempNodeEnd,tempNodeStart,tempWeight);
				tempNodeEnd->edges.push_back(tempEdge2);
			}
		}
		(*Graph)[tempNodeStartVal-1] = tempNodeStart;
		(*Graph)[tempNodeEndVal-1] = tempNodeEnd;
	}
}

template<typename nodeType, typename edgeType>
void constructShortestPathFromGraph(vector<nodeType*> *Graph,vector<edgeType*> *Path, int indexOfSourceNode, int indexOfDestinationNode)
{
	nodeType *source = (*Graph)[indexOfSourceNode];
	nodeType *destination = (*Graph)[indexOfDestinationNode];
	nodeType *tempNode = destination;
	typename vector<edgeType*>::iterator itr = Path->begin();
	while(tempNode->visitedBy->first != source)
	{
		itr = Path->begin();
		Path->insert(itr,tempNode->visitedBy);
		tempNode = tempNode->visitedBy->first;
	}
	itr = Path->begin();
	Path->insert(itr,tempNode->visitedBy);
}

template<typename nodeType, typename edgeType>
void initResidualGraph(vector<nodeType*> *Graph, vector<nodeType*> *residualGraph)
{
	size_t noOfNodes = Graph->size();
	for(size_t i = 0; i < noOfNodes;i++)
		(*residualGraph)[i] = new nodeType (i + 1);
	for(size_t i = 0; i < noOfNodes;i++)
	{
		vector<edgeType*> tempEdges = (*Graph)[i]->edges;
		size_t tempNoOfEdges = tempEdges.size();
		edgeType *tempEdge;
		for(size_t j = 0; j < tempNoOfEdges ;j++)
		{
			if(tempEdges[j]->residualCapacity > 0)
			{
				tempEdge = new edgeType((*residualGraph)[tempEdges[j]->first->Id - 1],(*residualGraph)[tempEdges[j]->second->Id - 1],1,tempEdges[j]->residualCapacity);
				(*residualGraph)[i]->edges.push_back(tempEdge);
			}
		}
	}
}

template<typename nodeType, typename edgeType>
void initResidualGraphNodeCapacity(vector<nodeType*> *residualGraph, bool sumOfEdges = true)
{
	size_t noOfNodes = residualGraph->size();
	for(size_t i = 0; i < noOfNodes;i++)
	{
		vector<edgeType*> tempEdges = (*residualGraph)[i]->edges;
		size_t tempNoOfEdges = tempEdges.size();
		edgeType *tempEdge;
		if(true == sumOfEdges)
		{
			for(size_t j = 0; j < tempNoOfEdges ;j++)
			{
				if(tempEdges[j]->residualCapacity > 0)
					tempEdges[j]->second->residualCapacity += tempEdges[j]->residualCapacity;
			}
		}
		else
			(*residualGraph)[i]->residualCapacity = 1;
	}
}

template<typename nodeType, typename edgeType>
void decompileGraph(vector<nodeType*> *Graph)
{
	edgeType *tempEdge;
	size_t noOfNodes = Graph->size();
	size_t noOfEdges;
	vector<edgeType*> tempEdges;
	for(size_t i = 0; i < noOfNodes; i++)
	{
		printf("Node: %d %d %d\n", (*Graph)[i]->Id, (*Graph)[i]->data, (*Graph)[i]->residualCapacity);
		tempEdges = (*Graph)[i]->edges;
		noOfEdges = tempEdges.size();
		for(size_t j =0; j < noOfEdges; j++)
		{
			tempEdge = tempEdges[j];
			printf("%d -> %d : %d,%d\n",tempEdge->first->Id, tempEdge->second->Id, tempEdge->weight, tempEdge->residualCapacity);
		}
	}
	printf("\n");
}

template<typename edgeType>
void decompilePath(vector<edgeType*> *Path)
{
	size_t lengthOfPath = Path->size();
	printf("%d -> ",(*Path)[0]->first->Id);
	for(size_t i =0;i< lengthOfPath;i++)
		printf("%d -> ",(*Path)[i]->second->Id);
	printf("\n");
}

template<typename nodeType>
void resetGraph(vector<nodeType*> *Graph)
{
	int NoOfNodes = (*Graph).size();
	for(int i =0;i<NoOfNodes;i++)
	{
		((*Graph)[i])->explored = false;
		((*Graph)[i])->data = 10000000;
		((*Graph)[i])->visitedBy = NULL;
		((*Graph)[i])->indexInHeap = -1;
	}
}

template <typename nodeType>
void deleteGraph (vector<nodeType*> *Graph)
{
	int NoOfNodes = (*Graph).size();
	for(int i =0;i<NoOfNodes;i++)
	{
		int size = ((*Graph)[i])->edges.size();
		for (int j=0;j<size;j++)
			delete ((*Graph)[i])->edges[j];
		delete ((*Graph)[i]);
	}
	delete Graph;
}
}
#endif /* UTILS_HPP_ */
