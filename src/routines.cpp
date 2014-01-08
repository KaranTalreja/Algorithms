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

int getCachedValue(int i,int j)
{
	int case1Value=0,case2Value=0;
	if(i >= 1)
	{
		case1Value = Cache[ i-1 ][j];
		//Case 2: i Node belongs to the knapsack
		if(j-Objects[i-1]->getWeight() >= 0)
			case2Value = Cache[ i-1 ][j-Objects[i-1]->getWeight()] + Objects[i-1]->getValue();
		else
			case2Value = 0;
	}
	else
	{
		case1Value = 0;
		case2Value = 0;
	}
	Cache[i][j] = (case1Value > case2Value) ? (case1Value) : (case2Value);
}


