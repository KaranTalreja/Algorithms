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
//template <typename nodeType>
//using graph = vector<nodeType*>;


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
void Dijkstra (graph<nodeType> *Graph)
{
    heapMin<unsigned int, nodeType> heap;
    nodeType* Source = NULL;
    edgeType* tempEdge = NULL;
    nodeType* tempNodeEnd = NULL;
    (*Graph)[0]->data = 0;
    heap.insert((*Graph)[0]);
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
}

}
#endif /* UTILS_HPP_ */
