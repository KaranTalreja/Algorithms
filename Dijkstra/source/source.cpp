#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <string.h>
// Forward declaration of class boost::serialization::access
namespace boost {
namespace serialization {
class access;
}
}
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
	unsigned int data;
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
	node()
	{
		data = -1;
		Id = -1;
		indexInHeap = -1;
		explored = false;
	}

	  // Allow serialization to access non-public data members.
	  friend class boost::serialization::access;

	  template<typename Archive>
	  void serialize(Archive& ar, const unsigned version) {
	    ar & data & Id & indexInHeap & explored & edges;  // Simply serialize the data members of Obj
}
};
class edge
{
public:
	node* first;
	node* second;
	unsigned int   weight;
	edge()
	{
		first = NULL;
		second = NULL;
		weight = 1000000;
	};
	edge(node* first,node* second, unsigned int weight)
	{
		this->first = first;
		this->second = second;
		this->weight = weight;
	}

	  // Allow serialization to access non-public data members.
	  friend class boost::serialization::access;

	  template<typename Archive>
	  void serialize(Archive& ar, const unsigned version) {
	    ar & first & second & weight ;  // Simply serialize the data members of Obj
}
};
int main()
{
	vector<node*> *Graph;
/*	Graph = new vector<node*>(noOfNodes);
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
*/
	const char* fileName = "saved.txt";
    std::ifstream ifs(fileName);
    boost::archive::binary_iarchive ari(ifs);
 //   std::ofstream ofs(fileName);
 //   boost::archive::binary_oarchive arO(ofs);
    // Write data
    ari & Graph;

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
