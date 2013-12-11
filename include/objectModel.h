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
class heapMin;
class edge;
class node;
class node {

public:
	node* leader;
	int rank;
	node()
	{
		rank=0;
		leader=this;
	}
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
int getSize()
{return size;}
};


#endif /* OBJECTMODEL_H_ */
