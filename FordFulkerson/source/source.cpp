#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include "Utils.hpp"
using namespace std;
using namespace karanUtils;
class node;
class edge;
typedef vector<node*> graph;
typedef vector<edge*> path;
class node : public baseNode
{
public:
	edge* visitedBy;
	vector<edge*> edges;
	int residualCapacity;
	node(int data,int Id): baseNode(data,Id)
	{
		visitedBy = NULL;
		residualCapacity = 0;
	}
	node(int Id):baseNode(Id)
	{
		visitedBy = NULL;
		residualCapacity = 0;
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
	inp(noOfNodes);
	inp(noOfEdges);
	graph *Graph = new graph(noOfNodes);
	readEdgesForGraph<node, edge>(Graph, noOfNodes, noOfEdges, false/*isDirectedGraph*/);
	//	decompileGraph<node,edge>(Graph);
	graph *residualGraph = new graph(noOfNodes);
	initResidualGraph<node, edge> (Graph, residualGraph);
	initResidualGraphNodeCapacity<node, edge>(residualGraph);
	path *shortestAugmentingPath =  new path;
	(*residualGraph)[0]->residualCapacity = 1100000000;
	(*residualGraph)[noOfNodes - 1]->residualCapacity = 1100000000;
	while(Dijkstra<node,edge>(residualGraph,0,noOfNodes-1))
	{
		constructShortestPathFromGraph <node, edge>(residualGraph, shortestAugmentingPath, 0, noOfNodes -1);
//		decompilePath<edge>(shortestAugmentingPath);
		size_t lengthOfPath = shortestAugmentingPath->size();
		size_t criticalAugmentingFlow =  1100000000;
		for(size_t i =0;i< lengthOfPath;i++)
		{
			if( i < lengthOfPath -1 )
			{
				if((*shortestAugmentingPath)[i]->second->residualCapacity < criticalAugmentingFlow)
					criticalAugmentingFlow = (*shortestAugmentingPath)[i]->second->residualCapacity;
			}
			if((*shortestAugmentingPath)[i]->residualCapacity < criticalAugmentingFlow)
				criticalAugmentingFlow = (*shortestAugmentingPath)[i]->residualCapacity;
		}
		maxFlow += criticalAugmentingFlow;
//		cout<<criticalAugmentingFlow<<endl;
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
			if( i < lengthOfPath -1 )
			{
				if(tempEdge->second->residualCapacity == criticalAugmentingFlow)
				{
					size_t noOfNodes = (*residualGraph).size();
					for(size_t i = 0 ; i< noOfNodes ; i++)
					{
						vector<edge*> tempEdges = (*residualGraph)[i]->edges;
						size_t noOfEdges = tempEdges.size();
						for(size_t j = 0 ; j< noOfEdges ; j++)
						{
							edge* tempEdgeToBeChecked = tempEdges[j];
							if(tempEdgeToBeChecked->second == tempEdge->second)
							{
								tempEdgeToBeChecked->deleteEdge();
								delete tempEdgeToBeChecked;
							}
						}
					}
				}
					tempEdge->second->residualCapacity -= criticalAugmentingFlow;
			}
		}
//		decompileGraph<node, edge>(residualGraph);
		resetGraph<node>(residualGraph);
		shortestAugmentingPath->clear();
	}
	printf("%d\n", maxFlow);
	deleteGraph<node>(Graph);
	deleteGraph<node>(residualGraph);
	return 0;
}

