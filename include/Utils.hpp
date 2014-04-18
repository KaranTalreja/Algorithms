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
template <typename nodeType>
using graph =  vector<nodeType*>;
template <typename nodeType>
using path = vector<nodeType*>;


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
void Dijkstra (graph<nodeType> *Graph, size_t indexOfSourceNode, size_t indexOfDestinationNode)
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
        if((indexOfDestinationNode != -1) && ((*Graph)[indexOfDestinationNode]->explored == true))
            break;
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
                        tempNodeEnd->visitedBy = Source;
                        heap.insert(tempNodeEnd);
                    }
                }
            }
            Source = NULL;
        }
        else
            break;
    }
}
template <typename nodeType, typename edgeType>
void readEdgesForGraph (graph<nodeType> *Graph, int noOfNodes, int noOfEdges, bool isDirectedGraph, bool printGraph = false)
{
    edgeType *tempEdge,*tempEdge2;
    nodeType *tempNodeStart,*tempNodeEnd;
    int tempNodeStartVal,tempNodeEndVal,tempWeight;
    if(printGraph == true) printf("%d %d\n", noOfNodes, noOfEdges);
    for(int i = 0; i<noOfEdges;i++)
    {
        inp(tempNodeStartVal);inp(tempNodeEndVal);inp(tempWeight);
        if(printGraph == true) printf("%d %d %d\n", tempNodeStartVal, tempNodeEndVal, tempWeight);
        tempNodeStart = (NULL == (*Graph)[tempNodeStartVal-1]) ? new nodeType(tempNodeStartVal) : (*Graph)[tempNodeStartVal-1];
        tempNodeEnd = (NULL == (*Graph)[tempNodeEndVal-1]) ? new nodeType(tempNodeEndVal) : (*Graph)[tempNodeEndVal-1];
        tempEdge = new edgeType(tempNodeStart,tempNodeEnd,tempWeight);
        tempNodeStart->edges.push_back(tempEdge);
        if(false == isDirectedGraph)
        {
            tempEdge2 = new edgeType(tempNodeEnd,tempNodeStart,tempWeight);
            tempNodeEnd->edges.push_back(tempEdge2);
        }
        (*Graph)[tempNodeStartVal-1] = tempNodeStart;
        (*Graph)[tempNodeEndVal-1] = tempNodeEnd;
    }
}

template<typename nodeType>
void constructShortestPathFromGraph(graph<nodeType> *Graph, path<nodeType> *Path, int indexOfSourceNode, int indexOfDestinationNode)
{
    nodeType *source = (*Graph)[indexOfSourceNode];
    nodeType *destination = (*Graph)[indexOfDestinationNode];
    nodeType *tempNode = destination;
    typename path<nodeType>::iterator itr = Path->begin();
    Path->insert(itr,tempNode);
    while(tempNode != source)
    {
        itr = Path->begin();
        Path->insert(itr,tempNode->visitedBy);
        tempNode = tempNode->visitedBy;
    }
}

template<typename nodeType, typename edgeType>
void initResidualGraph(graph<nodeType> *Graph, graph<nodeType> *residualGraph)
{
    size_t noOfNodes = Graph->size();
    for(size_t i = 0; i < noOfNodes;i++)
    {
        (*residualGraph)[i] = new nodeType ((*Graph)[i]);
        vector<edgeType*> tempEdges = (*Graph)[i]->edges;
        size_t tempNoOfEdges = tempEdges.size();
        edgeType *tempEdge;
        for(size_t j = 0; j < tempNoOfEdges ;j++)
        {
            tempEdge = new edgeType(tempEdges[j]);
            tempEdge->weight = 1;
            tempEdge->residualCapacity = tempEdges[j]->residualCapacity;
            (*residualGraph)[i]->edges.push_back(tempEdge);
        }
    }
}

template<typename nodeType, typename edgeType>
void decompileGraph(graph<nodeType> *Graph)
{
    edgeType *tempEdge;
    size_t noOfNodes = Graph->size();
    size_t noOfEdges;
    vector<edgeType*> tempEdges;
    for(size_t i = 0; i < noOfNodes; i++)
    {
        printf("Node: %d\n", (*Graph)[i]->Id);
        tempEdges = (*Graph)[i]->edges;
        noOfEdges = tempEdges.size();
        for(size_t j =0; j < noOfEdges; j++)
        {
            tempEdge = tempEdges[j];
            printf("%d -> %d : %d,%d\n",tempEdge->first->Id, tempEdge->second->Id, tempEdge->weight, tempEdge->residualCapacity);
        }
    }
}

}
#endif /* UTILS_HPP_ */
