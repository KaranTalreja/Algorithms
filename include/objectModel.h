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
class data
{
	int value;
	int weight;
public:
	data(int value,int weight)
	{
		this->value = value;
		this->weight=weight;
	}
	data();
};
#endif /* OBJECTMODEL_H_ */
