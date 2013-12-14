//============================================================================
// Name        : Clustering.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <lex.yy.c>
#include <include/objectModel.h>
#include <algorithm>
using namespace std;
vector<node*> *Graph;
int main() {

	FILE* file; //

	file = fopen("clustering1.txt", "r");

	if (!file) {
		cout << "file not found" << endl;
		exit(-1);
	}
	yyin = file;
	yylex();
	int noOfNodes = atoi(yytext);
	int tempNodeStartVal,tempNodeEndVal,tempWeight;
	edge* tempEdge;
	node *tempNodeStart,*tempNodeEnd;
	heapMin heap;
	Graph=new vector<node*>(noOfNodes);
	int noOfEdges = ((noOfNodes)*(noOfNodes-1))/2;
	for(int i = 0; i<noOfEdges;i++)
	{
		yylex();
		tempNodeStartVal = atoi(yytext);
		yylex();
		tempNodeEndVal = atoi(yytext);
		yylex();
		tempWeight = atoi(yytext);
		tempEdge = new edge();
		tempNodeStart = (NULL == (*Graph)[tempNodeStartVal-1]) ? new node(tempNodeStartVal) : (*Graph)[tempNodeStartVal-1];
		tempNodeEnd = (NULL == (*Graph)[tempNodeEndVal-1]) ? new node(tempNodeEndVal) : (*Graph)[tempNodeEndVal-1];
		tempEdge->first = tempNodeStart;
		tempEdge->second = tempNodeEnd;
		tempEdge->weight = tempWeight;
		(*Graph)[tempNodeStartVal-1] = ((*Graph)[tempNodeStartVal-1] == NULL ) ? tempNodeStart :(*Graph)[tempNodeStartVal-1];
		(*Graph)[tempNodeEndVal-1] = ((*Graph)[tempNodeEndVal-1] == NULL ) ? tempNodeEnd :(*Graph)[tempNodeEndVal-1];
		heap.insert(tempEdge);
	}

	int noOfClusters = noOfNodes;
	int requiredClusters = 4;
	UnionFind UF(Graph);
	while(noOfClusters != requiredClusters)
	{
		tempEdge = heap.extractMin();
		tempNodeStartVal = tempEdge->first->Id;
		tempNodeEndVal = tempEdge->second->Id;
		int Firstleader = UF.Find(tempNodeStartVal);
		int Secondleader =UF.Find(tempNodeEndVal);
		if(Firstleader != Secondleader)
		{
			UF.Union(Firstleader,Secondleader);
			noOfClusters --;
		}
		delete tempEdge;
	}
	int maxSpacing;
	while(1)
	{
		tempEdge=heap.extractMin();
		tempNodeStartVal = tempEdge->first->Id;
		tempNodeEndVal = tempEdge->second->Id;
		if(UF.Find(tempNodeStartVal) != UF.Find(tempNodeEndVal))
		{
			maxSpacing = tempEdge->weight;
			delete tempEdge;
			break;
		}
		delete tempEdge;
	}
	cout<<maxSpacing<<endl;
	for(int i = 0;i<noOfNodes ;i++)
		delete ((*Graph)[i]);
	heap.freeHeap();
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
