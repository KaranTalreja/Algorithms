//============================================================================
// Name        : Clustering.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <lex.yy.c>
#include <include/objectModel.h>
#include <tr1/unordered_map>
#include <include/routines.h>
#include <algorithm>
#include <math.h>
using namespace std;
int main() {

	FILE* file; //

	file = fopen("knapsack1.txt", "r");

	if (!file) {
		cout << "file not found" << endl;
		exit(-1);
	}
	yyin = file;
	yylex();
	int knapSackWeight = atoi(yytext);
	yylex();
	int noOfObjects = atoi(yytext);
	vector<data*> Objects(noOfObjects);
	vector<vector<int> > Cache (noOfObjects + 1, knapSackWeight + 1);
	data* tempData;
	int tempWeight,tempValue;
	for(int i=0;i<noOfObjects;i++)
	{
		yylex();
		tempValue = atoi(yytext);
		yylex();
		tempWeight = atoi(yytext);
		tempData = new data(tempValue,tempWeight);
		Objects[i] = tempData;
	}

	int case1Value=0,case2Value=0;
	for(int i=0 ;i<=noOfObjects;i++)
	{
		for(int j = 0;j<=knapSackWeight ;j++)
		{
			//Case 1: i Node does not belong to the knapsack
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
	}
	//cout<<Cache.size()<<" "<<Cache[0].size()<<endl;
	cout<<Cache[noOfObjects][knapSackWeight]<<endl;
	return 0;
}
//	while(temp = yylex())
//	{
//		switch(temp)
//		{
//		case(NUMBER):
//	{
//			cout<<atoi(yytext)<<" "<<endl;
//			break;
//	}
//		case(WORD):
//		case(BRACKET):
//	{
//			printf("%s \n",yytext);
//			break;
//	}
//		case(DIRECTORY):
//	{
//			printf("%s \n",yytext);
//			break;
//	}
//		case(EOL):
//	{
//			cout<<"EOL"<<endl;
//			break;
//	}
//		case(ALPHANUM):
//	{
//			printf("A__>%s \n",yytext);
//			break;
//	}
//		}
//	}
