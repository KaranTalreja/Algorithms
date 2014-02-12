#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
using namespace std;
#define getcx getchar_unlocked
#define noOfNodes 200
inline void inp( int &n );//fast input function
inline int getInt(char **str);
inline void inpLine(char* str);
class node;
class edge;
class node {

public:
	int data;
	unsigned int Id;
	int indexInHeap;
	bool explored;
	vector<edge*> edges;
	node(int data,int Id)
	{
		this->data = data;
		this->Id = Id;
		indexInHeap = -1;
		explored = false;
	}
	node();
};
class edge
{
public:
	node* first;
	node* second;
	int   weight;
	edge();
	edge(node* first,node* second, unsigned int weight)
	{
		this->first = first;
		this->second = second;
		this->weight = weight;
	}

};
int main()
{
	vector<node*> *Graph;
	Graph = new vector<node*>(noOfNodes);
	node* tempNodeStart,*tempNodeEnd;
	edge* tempEdge,*tempEdge2;
	int tempNodeStartVal,tempNodeEndVal,weight;
	char line[1000],*temp;
	temp = line;
	for(int i=0;i<noOfNodes;i++)
	{
		temp = line;
		inpLine(temp);
		tempNodeStartVal = getInt(&temp);
		tempNodeStart = (NULL == (*Graph)[tempNodeStartVal-1]) ? new node(10000000,tempNodeStartVal-1) : (*Graph)[tempNodeStartVal-1];
		while((strlen(temp)-2))
		{
			tempNodeEndVal =getInt(&temp);
			weight = getInt(&temp);
			tempNodeEnd = (NULL == (*Graph)[tempNodeEndVal-1]) ? new node(10000000,tempNodeEndVal-1) : (*Graph)[tempNodeEndVal-1];
			tempEdge = new edge(tempNodeStart,tempNodeEnd,weight);
			tempEdge2 = new edge(tempNodeEnd,tempNodeStart,weight);
			tempNodeStart->edges.push_back(tempEdge);
			tempNodeEnd->edges.push_back(tempEdge2);
			(*Graph)[tempNodeEndVal-1] = tempNodeEnd;
		}
		(*Graph)[tempNodeStartVal-1] = tempNodeStart;
	}
	vector<vector<int> > Cache(noOfNodes,vector<int>(noOfNodes));
	vector<vector<int> > prevCache(noOfNodes,vector<int>(noOfNodes));
	for(int i=0;i<noOfNodes;i++)
	{
		for(int j=0;j<noOfNodes;j++)
		{
			if(i != j)
				prevCache[i][j] = 10000000;
		}
		for(unsigned int j=0;j<(*Graph)[i]->edges.size();j++)
		{
			int sourceId = i,DestinationId = (*Graph)[i]->edges[j]->second->Id;
			if(prevCache[sourceId][DestinationId] > (*Graph)[i]->edges[j]->weight)
				prevCache[sourceId][DestinationId] = (*Graph)[i]->edges[j]->weight;
		}
	}
	for(int k=0;k<noOfNodes;k++)
	{
		for(int i=0;i<noOfNodes;i++)
		{
			for(int j=0;j<noOfNodes;j++)
			{
				int case1Value,case2Value,finalVal;
				case1Value = prevCache[i][j];
				case2Value = prevCache[i][k] + prevCache[k][j];
				finalVal = case1Value < case2Value ? case1Value : case2Value;
				Cache[i][j] = finalVal;
			}
		}
		for(int i=0;i<noOfNodes;i++)
		{
			for(int j=0;j<noOfNodes;j++)
			{
				prevCache[i][j] = Cache[i][j];
			}
		}
	}

	int arr[10] = {7,37,59,82,99,115,133,165,188,197};

	for(int k=0;k<10;k++)
		cout<<Cache[0][arr[k]-1]<<",";
	cout<<endl;
	return 0;
}
inline int getInt(char **str)
{
	char ch = **str;int sign=1;
	int n=0;
	while( ch < '0' || ch > '9' ){if(ch=='-')sign=-1; ch=*(++(*str));}
	while(  ch >= '0' && ch <= '9' )
	{n = (n<<3)+(n<<1) + ch-'0'; ch = *(++(*str));}
	return (n*sign);
}
inline void inp( int &n )//fast input function
{
	n=0;
	register int ch=getcx();int sign=1;
	while( ch < '0' || ch > '9' ){if(ch=='-')sign=-1; ch=getcx();}

	while(  ch >= '0' && ch <= '9' )
		n = (n<<3)+(n<<1) + ch-'0', ch=getcx();
	n=n*sign;
}
inline void inpLine(char *str)
{
	register char c = 0;
	register int i = 0;
	while (c < 33)
		c = getcx();
	while (c != '\n') {
		str[i] = c;
		c = getcx();
		i = i + 1;
	}
	str[i] = '\0';
}
