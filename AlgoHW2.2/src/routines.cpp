/*
 * routines.cpp
 *
 *  Created on: 15-Dec-2013
 *      Author: hp
 */
#include <include/routines.h>


int computeHamming(int first,int second,int noOfBits)
{
	int retVal = 0;
	int xOr = (first^second);
	for(int i=0;i<noOfBits;i++)
	{
		retVal += (xOr & 0x01);
		xOr = xOr >> 1;
	}
	return retVal;
}


