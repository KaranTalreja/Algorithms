/*
 * routines.h
 *
 *  Created on: 15-Dec-2013
 *      Author: hp
 */

#ifndef ROUTINES_H_
#define ROUTINES_H_
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <iostream>
#include <tr1/unordered_map>
#include <include/objectModel.h>
#include <include/parserDefines.h>

int getCurrentMemoryUsage();
long int getCachedValue(int i,int j,vector<data*>*,int);

#endif /* ROUTINES_H_ */