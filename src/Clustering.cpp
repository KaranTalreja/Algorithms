//============================================================================
// Name        : Clustering.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <lex.yy.c>
#include <vector>
#include <algorithm>
using namespace std;
class edge;
class node;
class node {

public:
	vector<edge*> edges;
	bool explored;
	node()
	{
		explored = false;
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
int main() {
	int cases,temp;
	FILE* file; //

	file = fopen("clustering1.txt", "r");

	if (!file) {
		cout << "file not found" << endl;
		exit(-1);
	}
	yyin = file;
	yylex();
	int noOfNodes = atoi(yytext);

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
