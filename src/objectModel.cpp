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
void heapMin::freeHeap()
{
	for(unsigned int i = 0;i<heap.size();i++)
		delete (heap[i]);
}
void UnionFind::Union(int first,int second)
{
	if((*Graph)[first-1]->rank > (*Graph)[second-1]->rank)
	{
		(*Graph)[second-1]->leader = (*Graph)[first-1];
		tr1::unordered_set<node*>::iterator itr = (*Graph)[second-1]->followers.begin();
		for(;itr!=(*Graph)[second-1]->followers.end();itr++)
		{
			(*Graph)[first-1]->followers.insert(tr1::unordered_set<node*>::value_type(*itr));
		}
		(*Graph)[first-1]->followers.insert(tr1::unordered_set<node*>::value_type((*Graph)[second-1]));
	}
	else if((*Graph)[first-1]->rank == (*Graph)[second-1]->rank)
	{
		(*Graph)[second-1]->leader = (*Graph)[first-1];
		tr1::unordered_set<node*>::iterator itr = (*Graph)[second-1]->followers.begin();
		for(;itr!=(*Graph)[second-1]->followers.end();itr++)
		{
			(*Graph)[first-1]->followers.insert(tr1::unordered_set<node*>::value_type(*itr));
		}
		(*Graph)[first-1]->followers.insert(tr1::unordered_set<node*>::value_type((*Graph)[second-1]));
		(*Graph)[first-1]->rank++;

	}
	else
	{
		(*Graph)[first-1]->leader = (*Graph)[second-1];
		tr1::unordered_set<node*>::iterator itr = (*Graph)[first-1]->followers.begin();
		for(;itr!=(*Graph)[first-1]->followers.end();itr++)
		{
			(*Graph)[second-1]->followers.insert(tr1::unordered_set<node*>::value_type(*itr));
		}
		(*Graph)[second-1]->followers.insert(tr1::unordered_set<node*>::value_type((*Graph)[first-1]));
	}
}

int UnionFind::Find(int child)
{
	node* startNode = (*Graph)[child-1];
	vector<node*> listOfNodesToUpdate;
	while(startNode->leader != startNode)
	{
		listOfNodesToUpdate.push_back(startNode);
		startNode = startNode->leader;
	}
	node* leader = startNode->leader;
	for(unsigned int i = 0; i < listOfNodesToUpdate.size();i++)
		listOfNodesToUpdate[i]->leader = leader;
	return startNode->Id;
}
int UnionFind::decompile(bool toPrint)
{
	int k=0;
    tr1::unordered_set<int> *hash2;
	hash2 = new tr1::unordered_set<int>;
	for (unsigned int i=0;i<(*Graph).size();i++)
	{
	hash2->insert(tr1::unordered_set<int>::value_type(this->Find((*Graph)[i]->Id)));
	}
	tr1::unordered_set<int>::iterator itr = hash2->begin();
	for(;itr!=hash2->end();itr++)
	{
		k++;
		if(toPrint == true)
		{
		cout<<"leader: "<<(*itr)<<" Followed by ";
		tr1::unordered_set<node*>::iterator iter = (*Graph)[*itr - 1]->followers.begin();
		for(;iter!=(*Graph)[*itr -1]->followers.end();iter++)
		{
			cout<<(*iter)->Id<<" ";
		}
		cout<<endl;
		}
	}
	delete hash2;
	return k;
}
