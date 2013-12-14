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
	int cases,temp;
	FILE* file; //

	file = fopen("Example", "r");

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
		tempNodeStart = (NULL == (*Graph)[tempNodeStartVal-1]) ? new node(tempNodeStartVal-1) : (*Graph)[tempNodeStartVal-1];
		tempNodeEnd = (NULL == (*Graph)[tempNodeEndVal-1]) ? new node(tempNodeEndVal-1) : (*Graph)[tempNodeEndVal-1];
		tempEdge->first = tempNodeStart;
		tempEdge->second = tempNodeEnd;
		tempEdge->weight = tempWeight;
		(*Graph)[tempNodeStartVal-1] = ((*Graph)[tempNodeStartVal-1] == NULL ) ? tempNodeStart :(*Graph)[tempNodeStartVal-1];
		(*Graph)[tempNodeEndVal-1] = ((*Graph)[tempNodeEndVal-1] == NULL ) ? tempNodeEnd :(*Graph)[tempNodeEndVal-1];
		heap.insert(tempEdge);
	}

	int noOfClusters = noOfNodes;
	int requiredClusters = 2;
	UnionFind UF(Graph);
	while(noOfClusters != requiredClusters)
	{
		tempEdge = heap.extractMin();
		tempNodeStartVal = tempEdge->first->Id;
		tempNodeEndVal = tempEdge->second->Id;
		int Firstleader = UF.Find(tempNodeStartVal);
		int Secondleader =UF.Find(tempNodeEndVal);
//		cout<<"Leader of "<<tempNodeStartVal+1<<" is "<<Firstleader+1<<endl;
//		cout<<"Leader of "<<tempNodeEndVal+1<<" is "<<Secondleader+1<<endl;
		if(Firstleader != Secondleader)
		{
			UF.Union(tempNodeStartVal,tempNodeEndVal);
//			cout<<"Union :" << tempNodeStartVal+1 <<" and "<<tempNodeEndVal+1<<endl;
//			int Firstleader = UF.Find(tempNodeStartVal);
//			int Secondleader =UF.Find(tempNodeEndVal);
//			cout<<"Now Leader of "<<tempNodeStartVal+1<<" is "<<Firstleader+1<<endl;
//			cout<<"Now Leader of "<<tempNodeEndVal+1<<" is "<<Secondleader+1<<endl;
			noOfClusters --;
		}
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
			break;
		}
	}
	cout<<maxSpacing<<endl;



//	int size = heap.getSize();
//	for(int i = 0;i<size;i++)
//		cout<<heap.extractMin()->weight<<endl;
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
