/*
 * objectModel.h
 *
 *  Created on: 11-Dec-2013
 *      Author: hp
 */

#ifndef OBJECTMODEL_H_
#define OBJECTMODEL_H_
#include <vector>
#include<stdio.h>
#include <iostream>
#include <tr1/unordered_set>
using namespace std;
class heapMin;
class UnionFind;
class edge;
class node;
class node {

public:
	node* leader;
	int rank;
	int Id;
	tr1::unordered_set<node*> followers;
	node(int Id)
	{
		this->Id = Id;
		rank=0;
		leader=this;
		followers.insert(tr1::unordered_set<node*>::value_type(this));
	}
	node();
};
class edge
{
public:
	node* first,*second;
	int weight;
	edge()
	{
		first = NULL;
		second = NULL;
		weight = 0;
	}
};
class heapMin
{
std::vector<edge*> heap;
int size;
public:
heapMin()
{
	size = 0;
}
void insert(edge*);
edge* extractMin();
void decompile();
int getSize()
{return size;}
void freeHeap();
};

class UnionFind
{
	std::vector<node*> *Graph;
public:
	UnionFind(std::vector<node*> *Clusters)
	{
		Graph = Clusters;
	}
	UnionFind();
	void Union(int first,int second);
	int Find(int child);
	int decompile(bool toPrint = false);
};


#endif /* OBJECTMODEL_H_ */
