/*
 * routines.cpp
 *
 *  Created on: 15-Dec-2013
 *      Author: hp
 */
#include <include/routines.h>
extern FILE* yyin;
extern int yylex (void);
extern char* yytext;
using namespace std;
int getCurrentMemoryUsage()
{
	FILE* file;
	int temp,retVal;
	int pid = getpid();
	char* command,*command2;
	command = (char*)malloc(64);
	command2 = (char*)malloc(64);
	sprintf(command,"/proc/%d/status",pid);
	sprintf(command2,"cat /proc/%d/status",pid);
	file=fopen(command,"r");
	if (!file) {
		cout << "file not found" << endl;
		exit(-1);
	}
	yyin = file;
	while(temp = yylex())
		{
			switch(temp)
			{

			case(VM):
		{
				temp = yylex();
				if(temp == NUMBER)
					retVal = atoi(yytext);
				break;
		}
			}
		}
	return retVal;
}

long int getCachedValue(int i,int j,vector<data*> *tempObjects,int noOfObjects)
{
	static long long k=0;
	static tr1::unordered_map<long int,long int> hash;
	static tr1::unordered_map<long int,long int *> Cache;
	tr1::unordered_map<long int,long int>::iterator itr;
	tr1::unordered_map<long int,long int*>:: iterator itr_value;
	k++;
	long int Idx = (long int)j*noOfObjects + i;

	itr = hash.find(Idx);

	if(itr!=hash.end())
		return itr->second;

	vector<data*> Objects = *tempObjects;
	long int case1Value=0,case2Value=0;
	if(i >= 1)
	{
		case1Value = getCachedValue(i-1 ,j,tempObjects,noOfObjects);
		//Case 2: i Node belongs to the knapsack
		if(j-Objects[i-1]->getWeight() >= 0)
			case2Value = getCachedValue( i-1 ,j-Objects[i-1]->getWeight(),tempObjects,noOfObjects) + Objects[i-1]->getValue();
		else
			case2Value = 0;
	}
	else
	{
		case1Value = 0;
		case2Value = 0;
	}
	long int result = case1Value > case2Value ? case1Value : case2Value;
	itr_value = Cache.find(result);
	if(itr_value == Cache.end())
	{
		hash.insert(make_pair<long int,long int>(Idx,result));
		long int *tempPtr = new long int;
		*tempPtr = result;
		Cache.insert(make_pair<long int,long int*>(result,tempPtr));
	}
	else
	{
		result =  *(itr_value->second);
	}
	if(i == noOfObjects)
		cout<<"Total Iterations:"<<k<<endl<<"Total elements: "<<hash.size()<<endl;
	return result;
}


