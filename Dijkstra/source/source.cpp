#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include "Utils.hpp"
using namespace karanUtils;
using namespace std;
#define noOfNodes 200

class node;
class edge;
typedef vector<node*> graph;
typedef vector<edge*> path;
class node {

public:
	unsigned int data;
	unsigned int Id;
	int indexInHeap;
	bool explored;
    edge *visitedBy;
	vector<edge*> edges;
	node(int data,int Id)
	{
		this->data = data;
		this->Id = Id;
		indexInHeap = -1;
		explored = false;
	    visitedBy = NULL;
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
	graph *Graph;
	Graph = new graph(noOfNodes);
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

	Dijkstra<node,edge>(Graph,0,-1);

	int arr[10] = {7,37,59,82,99,115,133,165,188,197};

	for(int k=0;k<10;k++)
		cout<<(*Graph)[arr[k]-1]->data<<',';
	cout<<endl;


	return 0;
}
