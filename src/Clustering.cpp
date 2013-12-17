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
vector<node*> *Graph;
int main() {

	FILE* file; //

	file = fopen("clustering_big.txt", "r");

	if (!file) {
		cout << "file not found" << endl;
		exit(-1);
	}
	yyin = file;
	yylex();
	int noOfNodes = atoi(yytext);
	yylex();
	int noOfBits = atoi(yytext);
	node* tempNode;
	Graph=new vector<node*>(noOfNodes);
	int tempBit=0,tempNumber=0;
	tr1::unordered_multimap <int,node*> hash;
	for(int j =0;j<noOfNodes;j++)
	{
		tempNumber=0;
		for(int i =0;i<noOfBits;i++)
		{
			yylex();
			tempBit = atoi(yytext);
			tempNumber += ((tempBit == 1) ? 1 : 0);
			if(i<noOfBits-1) tempNumber = tempNumber << 1;
		}
		tempNode = (NULL == (*Graph)[j]) ? new node(j,tempNumber) : (*Graph)[j];
		(*Graph)[j] = tempNode;
		hash.insert(tr1::unordered_multimap<int,node*>::value_type((*Graph)[j]->Data,(*Graph)[j]));
	}
	//cout<< computeHamming((*Graph)[0]->Data,(*Graph)[1]->Data,noOfBits)<<endl;

	UnionFind UF(Graph);
	int retVal =0;
	int first;
	int tempFirst;
	int kk =0;
    tr1::unordered_multimap<int,node*>::iterator isPresent;

	for(int i=0;i<noOfNodes;i++)
	{
		first = (*Graph)[i]->Data;

		tr1::unordered_multimap<int,node*>::iterator firstNode,secondNode;
		if(hash.count(first) > 1)
		{
			vector<std::pair<int,node*> > listOfDuplicates;
			std::pair<tr1::unordered_multimap<int,node*>::iterator,tr1::unordered_multimap<int,node*>::iterator> p= hash.equal_range(first);
			firstNode=p.first;
			while((p.first)!=p.second)
			{
				secondNode= p.first;
				if(secondNode->first == firstNode->first)
					listOfDuplicates.push_back(*secondNode);
				++p.first;
			}
			for(vector<std::pair<int,node*> >::iterator itr=listOfDuplicates.begin();itr!=listOfDuplicates.end();itr++)
			{
				int Firstleader = UF.Find(firstNode->second->Id);
				int Secondleader=UF.Find(itr->second->Id);
				if(Firstleader != Secondleader)
				{
					UF.Union(Firstleader,Secondleader);
				}
			}
		}
		for(int j=0;j<noOfBits;j++)
		{
			tempFirst = first;
			tempFirst = (tempFirst ^ (int)pow(2,(double)j));
			int t = computeHamming(first,tempFirst,noOfBits);
			if(t != 1 && t != 2 )
				cout<<"Hamming "<<t<<" for "<<first<<" "<<tempFirst<<endl;
        	isPresent = hash.find(tempFirst);
        	if(isPresent != hash.end())
        	{
        		int Firstleader = UF.Find((*Graph)[i]->Id);
        		int Secondleader =UF.Find((*isPresent).second->Id);
        		if(Firstleader != Secondleader)
        		{
        			UF.Union(Firstleader,Secondleader);
        		}
        	}
		}
		for(int j=0;j<noOfBits;j++)
		{
			for(int k=j+1;k<noOfBits;k++)
			{
				tempFirst = first;
				tempFirst = (tempFirst ^ (int)pow(2,(double)j));
				tempFirst = (tempFirst ^ (int)pow(2,(double)k));
				int t = computeHamming(first,tempFirst,noOfBits);
				if(t != 1 && t != 2 )
					cout<<"Hamming "<<t<<" for "<<first<<" "<<tempFirst<<endl;
				isPresent = hash.find(tempFirst);
				if(isPresent != hash.end())
				{
					int Firstleader = UF.Find((*Graph)[i]->Id);
					int Secondleader =UF.Find((*isPresent).second->Id);
					if(Firstleader != Secondleader)
					{
						UF.Union(Firstleader,Secondleader);
					}
				}
			}
		}
	}
//	cout<<kk<<endl;
	//cout<<noOfClusters<<endl;
	cout<<"No of leaders " << UF.decompile() <<endl;
//	tr1::unordered_set<int>::iterator itr = UF.hash2->begin();
//	tr1::unordered_set<int>::iterator previtr = UF.hash2->begin();
//	tr1::unordered_set<int>::iterator itr2 = UF.hash2->begin();
//	for(;itr!=UF.hash2->end();itr++)
//	{
//		previtr = itr;
//		itr++;
//		for(itr2=itr;itr2!=UF.hash2->end();itr2++)
//		{
//			int first,tempFirst;
//			itr = previtr;
//			first = (*Graph)[(*itr)]->Data;
//			tempFirst = (*Graph)[(*itr2)]->Data;
//			int t = computeHamming(first,tempFirst,noOfBits);
//		//	if(t != 1 && t != 2 )
//				cout<<"Hamming "<<t<<" for "<<first<<" "<<tempFirst<<endl;
//		}
//
//	}

//	for(int i=0;i<noOfNodes;i++)
//	{
//		for(int j=i+1;j<noOfNodes;j++)
//		{
//			k++;
//			first = (*Graph)[i]->Data;
//			second =(*Graph)[j]->Data;
//			int xOr = (first^second);
//			if(computeHamming(first,second,noOfBits) <= 2)
//			{
//				int Firstleader = UF.Find((*Graph)[i+1]->Id);
//				int Secondleader =UF.Find((*Graph)[j+1]->Id);
//				if(Firstleader != Secondleader)
//				{
//					UF.Union(Firstleader+1,Secondleader+1);
//					noOfClusters++;
//				}
//			}
//		}
//	}
//	cout<<noOfClusters<<" "<<k<<endl;
	for(int i = 0;i<noOfNodes ;i++)
		delete ((*Graph)[i]);
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
//for(int i = 0; i<noOfEdges;i++)
//{
//	yylex();
//	tempNodeStartVal = atoi(yytext);
//	yylex();
//	tempNodeEndVal = atoi(yytext);
//	yylex();
//	tempWeight = atoi(yytext);
//	tempEdge = new edge();
//	tempNodeStart = (NULL == (*Graph)[tempNodeStartVal-1]) ? new node(tempNodeStartVal) : (*Graph)[tempNodeStartVal-1];
//	tempNodeEnd = (NULL == (*Graph)[tempNodeEndVal-1]) ? new node(tempNodeEndVal) : (*Graph)[tempNodeEndVal-1];
//	tempEdge->first = tempNodeStart;
//	tempEdge->second = tempNodeEnd;
//	tempEdge->weight = tempWeight;
//	(*Graph)[tempNodeStartVal-1] = ((*Graph)[tempNodeStartVal-1] == NULL ) ? tempNodeStart :(*Graph)[tempNodeStartVal-1];
//	(*Graph)[tempNodeEndVal-1] = ((*Graph)[tempNodeEndVal-1] == NULL ) ? tempNodeEnd :(*Graph)[tempNodeEndVal-1];
//	heap.insert(tempEdge);
//}
//
//int noOfClusters = noOfNodes;
//int requiredClusters = 4;
//UnionFind UF(Graph);
//while(noOfClusters != requiredClusters)
//{
//	tempEdge = heap.extractMin();
//	tempNodeStartVal = tempEdge->first->Id;
//	tempNodeEndVal = tempEdge->second->Id;
//	int Firstleader = UF.Find(tempNodeStartVal);
//	int Secondleader =UF.Find(tempNodeEndVal);
//	if(Firstleader != Secondleader)
//	{
//		UF.Union(Firstleader,Secondleader);
//		noOfClusters --;
//	}
//	delete tempEdge;
//}
//int maxSpacing;
//while(1)
//{
//	tempEdge=heap.extractMin();
//	tempNodeStartVal = tempEdge->first->Id;
//	tempNodeEndVal = tempEdge->second->Id;
//	if(UF.Find(tempNodeStartVal) != UF.Find(tempNodeEndVal))
//	{
//		maxSpacing = tempEdge->weight;
//		delete tempEdge;
//		break;
//	}
//	delete tempEdge;
//}
//cout<<maxSpacing<<endl;
//for(int i = 0;i<noOfNodes ;i++)
//	delete ((*Graph)[i]);
//heap.freeHeap();
//return 0;
