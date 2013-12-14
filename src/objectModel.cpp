/*
 * objectModel.cpp
 *
 *  Created on: 11-Dec-2013
 *      Author: hp
 */
#include <include/objectModel.h>
using namespace std;
void heapMin::insert(edge* Edge)
{
	int parent,child;
	edge* tempEdge;
	heap.push_back(Edge);
	size++;
	child = size;
	parent = (child)/2;
	while((parent >=1) && (heap[parent-1]->weight > heap[child-1]->weight))
	{
		tempEdge = heap[child-1];
		heap[child-1] = heap[parent-1];
		heap[parent-1] = tempEdge;
		child = parent;
		parent = parent/2;
	}
}

edge* heapMin::extractMin(void)
{
	edge* retVal = heap[0],*tempEdge;
	tempEdge = heap[0];
	heap[0] = heap[size-1];
	heap[size-1] = tempEdge;
	vector<edge*> :: iterator itr = heap.begin();
	itr = itr + size -1;
	heap.erase(itr);
	size--;
	int parent = 1;
	int child = parent;
	while(2*parent < size)
	{
		child = (heap[(2*parent)-1]->weight <= heap[(2*parent)]->weight) ? 2*parent : 2*parent + 1;
		if(heap[child-1]->weight < heap[parent-1]->weight)
		{
			tempEdge = heap[child -1];
			heap[child - 1] = heap[parent - 1];
			heap[parent - 1] = tempEdge;
			parent = child;
		}
		else
			break;
	}
	return retVal;
}
void heapMin::decompile()
{
	for(vector<edge*>::iterator itr = heap.begin();itr!=heap.end();itr++)
	{
		cout<<(*itr)->weight<<" ";
	}
	cout<<endl;

}

void UnionFind::Union(int first,int second)
{
	if((*Graph)[first]->rank > (*Graph)[second]->rank)
		(*Graph)[second]->leader = (*Graph)[first];
	else if((*Graph)[first]->rank == (*Graph)[second]->rank)
	{
		(*Graph)[second]->leader = (*Graph)[first];
		(*Graph)[first]->rank++;
	}
	else
		(*Graph)[first]->leader = (*Graph)[second];
}

int UnionFind::Find(int child)
{
	node* startNode = (*Graph)[child];
	vector<node*> listOfNodesToUpdate;
	while(startNode->leader != startNode)
	{
		listOfNodesToUpdate.push_back(startNode);
		startNode = startNode->leader;
	}
	node* leader = startNode->leader;
	for(int i = 0; i < listOfNodesToUpdate.size();i++)
		listOfNodesToUpdate[i]->leader = leader;
	return startNode->Id;
}
