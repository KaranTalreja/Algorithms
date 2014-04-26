#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <tr1/unordered_set>
#include "Utils.hpp"
using namespace std;
using namespace karanUtils;
class node;
class edge;
typedef vector<node*> graph;
typedef vector<edge*> path;
typedef tr1::unordered_set<int> hashInt;
class node : public baseNode
{
public:
	edge* visitedBy;
	vector<edge*> edges;
	node(int data,int Id): baseNode(data,Id)
	{
		visitedBy = NULL;
	}
	node(int Id):baseNode(Id)
	{
		visitedBy = NULL;
	}
	node();
};
class edge : public baseEdge
{
public:
	node* first;
	node* second;
	int residualCapacity;
	edge();
	edge(node* first,node* second, unsigned int weight) : baseEdge(weight)
	{
		this->first = first;
		this->second = second;
		this->residualCapacity = weight;
	}
	edge(node* first,node* second, unsigned int weight, unsigned int residualCapacity) : baseEdge(weight)
	{
		this->first = first;
		this->second = second;
		this->residualCapacity = residualCapacity;
	}
	void deleteEdge()
	{
		vector<edge*> *edges = &(this->first->edges);
		vector<edge*> :: iterator itr;
		for(itr = edges->begin(); itr!= edges->end(); ++itr)
		{
			if((*itr) == this)
			{
				edges->erase(itr);
				break;
			}
		}
	}
	edge* getReversedEdge()
	{
		edge* retVal = NULL;
		vector<edge*> *edges = &(this->second->edges);
		vector<edge*> :: iterator itr;
		for(itr = edges->begin(); itr!= edges->end(); ++itr)
		{
			if(((*itr)->first == this->second) && ((*itr)->second == this->first))
			{
				retVal = *itr;
				break;
			}
		}
		return retVal;
	}
};
int main()
{
	int noOfNodes, noOfEdges;
	unsigned int maxFlow = 0;
	hashInt hash;
	inp(noOfNodes);
	inp(noOfEdges);
	graph *Graph = new graph(noOfNodes);
	readEdgesForGraph<node, edge>(Graph, noOfNodes, noOfEdges, false/*isDirectedGraph*/);
	graph *residualGraph;
	bool isVertexCapacity = true;
	if(isVertexCapacity == true)
	    residualGraph = new graph(noOfNodes * 2);
	else
	    residualGraph = new graph(noOfNodes);
	initResidualGraph<node, edge> (Graph, residualGraph,isVertexCapacity);
	path *shortestAugmentingPath =  new path;
	while(Dijkstra<node,edge>(residualGraph,0,noOfNodes-1))
	{
		constructShortestPathFromGraph <node, edge>(residualGraph, shortestAugmentingPath, 0, noOfNodes -1);
		size_t lengthOfPath = shortestAugmentingPath->size();
		size_t criticalAugmentingFlow =  1100000000;
		for(size_t i =0;i< lengthOfPath;i++)
		{
			if((*shortestAugmentingPath)[i]->residualCapacity < criticalAugmentingFlow)
				criticalAugmentingFlow = (*shortestAugmentingPath)[i]->residualCapacity;
		}
		maxFlow += criticalAugmentingFlow;
		if(criticalAugmentingFlow > 0)
		{
		cout<<criticalAugmentingFlow<<" : ";
		decompilePath<edge>(shortestAugmentingPath,noOfNodes ,isVertexCapacity);
        for(size_t i =0;i< lengthOfPath-1;i++)
        {
            if(hash.find((*shortestAugmentingPath)[i]->second->Id) != hash.end())
            {
                cout<<"FAILIURE : "<<(*shortestAugmentingPath)[i]->second->Id<<endl;
                decompilePath<edge>(shortestAugmentingPath,noOfNodes ,isVertexCapacity);
//                return 0;
            }
            else
                hash.insert((*shortestAugmentingPath)[i]->second->Id);
        }
		}
		for(size_t i =0;i< lengthOfPath;i++)
		{
			edge* tempEdge = (*shortestAugmentingPath)[i];
			edge* reverseEdge = tempEdge->getReversedEdge();
			if(NULL == reverseEdge)
			{
				reverseEdge = new edge(tempEdge->second, tempEdge->first, 1, criticalAugmentingFlow);
				reverseEdge->first->edges.push_back(reverseEdge);
			}
			else
				reverseEdge->residualCapacity += criticalAugmentingFlow;
			if(tempEdge->residualCapacity == criticalAugmentingFlow)
			{
				tempEdge->deleteEdge();
				delete tempEdge;
			}
			else
				tempEdge->residualCapacity -= criticalAugmentingFlow;
		}
		resetGraph<node>(residualGraph);
		shortestAugmentingPath->clear();
	}
	printf("%d\n", maxFlow);
	deleteGraph<node>(Graph);
	deleteGraph<node>(residualGraph);
	return 0;
}

