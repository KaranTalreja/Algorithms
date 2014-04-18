#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include "Utils.hpp"
using namespace std;
using namespace karanUtils;
#define noOfNodes 200
class node;
class edge;
typedef vector<node*> graph;
typedef vector<edge*> path;
class node: public baseNode {

public:
	int indexInHeap;
	int weight;
    edge* visitedBy;
	vector<edge*> edges;
	node(int data,int Id) : baseNode(data,Id)
	{
		indexInHeap = -1;
		weight = 10000000;
		visitedBy = NULL;
	}
	node();
};
class edge : public baseEdge
{
public:
	node* first;
	node* second;
	edge();
	edge(node* first,node* second, unsigned int weight) : baseEdge(weight)
	{
		this->first = first;
		this->second = second;
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
	// ADDING A DUMMY NODE TO RUN BELLMAN FORD

	node* dummyNode = new node(10000000,noOfNodes);
	for(int i = 0;i<noOfNodes;i++)
		dummyNode->edges.push_back(new edge(dummyNode,(*Graph)[i],0));

	node* Source = dummyNode;
	Source -> data = 0;
	Graph->push_back(Source);



	//BELLMAN FORD ALGROTITHM FOR N+1 NODES


	vector<int> newValue(noOfNodes+1);
	for(int i=0;i<=noOfNodes;i++)
		newValue[i] = (*Graph)[i]->data;
	for(int k=0;k<=noOfNodes;k++)
	{
		for(int i=0;i<=noOfNodes;i++)
		{
			for(unsigned int j=0;j<(*Graph)[i]->edges.size();j++)
			{
				if((newValue[(*Graph)[i]->edges[j]->second->Id] > (*Graph)[i]->data + (*Graph)[i]->edges[j]->weight))
					newValue[(*Graph)[i]->edges[j]->second->Id] = (*Graph)[i]->data + (*Graph)[i]->edges[j]->weight;
			}
		}
		for(int i=0;i<=noOfNodes;i++)
			(*Graph)[i]->data = newValue[i];
	}


	//REMOVE THE DUMMY NODE

	Graph->pop_back();

	for(int i=0;i<noOfNodes;i++)
	{
		(*Graph)[i]->weight = (*Graph)[i]->data;
		(*Graph)[i]->data = 10000000;
	}


	//ALL EDGES WEIGHT UPDATED TO MAKE THEM POSITIVE


	for(int i=0;i<noOfNodes;i++)
	{
		for(unsigned int j=0;j<(*Graph)[i]->edges.size();j++)
		{
			(*Graph)[i]->edges[j]->weight = (*Graph)[i]->edges[j]->weight + (*Graph)[i]->edges[j]->first->weight - (*Graph)[i]->edges[j]->second->weight;
		}
	}

	//DIJKSTRA ALGORITHM RUN N-TIMES TO COMPUTE SHORTEST PATH FOR ALL PAIRS


	vector<vector<int> > Cache(noOfNodes,vector<int>(noOfNodes));
	for(int j=0;j<noOfNodes;j++)
	{

	    Dijkstra<node,edge>(Graph,j,-1);
		int NoOfNodes = (*Graph).size();
		for(int i =0;i<NoOfNodes;i++)
			Cache[j][(*Graph)[i]->Id] = (*Graph)[i]->data;
	    resetGraph<node>(Graph);
	}

	//REMOVING THE BIAS FROM PATHS TO GET ORIGINAL VALUES

	for(int i=0;i<noOfNodes;i++)
	{
		int sourceWeight = (*Graph)[i]->weight;
		for(int j=0;j<noOfNodes;j++)
		{
			Cache[i][j] = Cache[i][j] - sourceWeight + (*Graph)[j]->weight;
		}
	}
	//OUTPUT
	int arr[10] = {7,37,59,82,99,115,133,165,188,197};

	for(int k=0;k<10;k++)
		cout<<Cache[0][arr[k]-1]<<",";
	cout<<endl;
	return 0;
}

