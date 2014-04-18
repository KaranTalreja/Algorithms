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
class node
{
public:
    unsigned int data; /*heapKey*/
    unsigned int Id;
    node* visitedBy;
    int indexInHeap;
    bool explored;
    vector<edge*> edges;
    node(int data,int Id)
    {
        this->data = data;
        this->Id = Id;
        visitedBy = NULL;
        indexInHeap = -1;
        explored = false;
    }
    node(int Id)
    {
        this->data = -1;
        this->Id = Id;
        visitedBy = NULL;
        indexInHeap = -1;
        explored = false;
    }
    node();
    node(node* dummyNode)
    {
        this->data = dummyNode->data;
        this->Id = dummyNode->Id;
        visitedBy = dummyNode->visitedBy;
        indexInHeap = dummyNode->indexInHeap;
        explored = dummyNode->explored;
    }
};
class edge
{
public:
    node* first;
    node* second;
    unsigned int weight;
    unsigned int residualCapacity;
    edge();
    edge(node* first,node* second, unsigned int weight)
    {
        this->first = first;
        this->second = second;
        this->weight = weight;
        this->residualCapacity = weight;
    }
    edge(node* first,node* second, unsigned int weight, unsigned int residualCapacity)
    {
        this->first = first;
        this->second = second;
        this->weight = weight;
        this->residualCapacity = residualCapacity;
    }
    edge(edge* dummyEdge)
    {
        this->first = dummyEdge->first;
        this->second = dummyEdge->second;
        this->weight = dummyEdge->weight;
        this->residualCapacity = dummyEdge->residualCapacity;
    }
};
int main()
{
    int noOfNodes, noOfEdges;
    inp(noOfNodes);
    inp(noOfEdges);
    graph<node> *Graph = new graph<node>(noOfNodes);
    readEdgesForGraph<node, edge>(Graph, noOfNodes, noOfEdges, true/*isDirectedGraph*/);
    graph<node> *residualGraph = new graph<node>(noOfNodes);
    initResidualGraph<node, edge> (Graph, residualGraph);

    decompileGraph<node,edge>(Graph);
    printf("\n\n");
    decompileGraph<node,edge>(residualGraph);
    node *source = (*Graph)[0];
    node *sink = (*Graph)[noOfNodes - 1];
    Dijkstra<node,edge>(Graph,0,noOfNodes-1);
    path<node> *shortestAugmentingPath =  new path<node>;
    constructShortestPathFromGraph <node>(Graph, shortestAugmentingPath, 0, noOfNodes -1);
    size_t lengthOfPath = shortestAugmentingPath->size();
    for(size_t i =0;i< lengthOfPath;i++)
    {
        printf("%d-> ", ((*shortestAugmentingPath)[i])->Id);
    }
    //While Path exists
        //Construct residual Graph and find path
        //update residual graph and flows
    return 0;
}

