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




