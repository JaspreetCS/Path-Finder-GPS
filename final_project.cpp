#include <iostream>
#include <fstream>
#include <cassert>
#include <ctime>
#include <iomanip>

using namespace std;

class CMPT135_String
{
private:
	char *buffer;
public:
	CMPT135_String(); //The buffer is initialized to nullptr value
	CMPT135_String(const char *); //A null terminated char array
	CMPT135_String(const CMPT135_String &); //Deep copy constructor
	~CMPT135_String();  //Delete any heap memory and assign buffer nullptr value
	CMPT135_String& operator = (const CMPT135_String &); //Deep copy assignment
	int length() const; //Return the number of printable characters
	bool empty() const;  //Return true if length is 0. Otherwise return false
	char& operator [] (const int &) const;  //Assert index and then return the char at the index
	CMPT135_String operator + (const char &) const; //See assignment 1
	CMPT135_String& operator += (const char &); //See assignment 1
	bool operator == (const CMPT135_String &) const; //See assignment 1
	bool operator != (const CMPT135_String &) const; //See assignment 1
	friend istream& operator >> (istream &, CMPT135_String &); //Implemented for you
	friend ostream& operator << (ostream &, const CMPT135_String &); //Implemented for you
};

CMPT135_String::CMPT135_String()
{
	buffer = nullptr;
}

CMPT135_String::CMPT135_String(const char* cStr)
{
	int i = 0,size = 0;
		while(cStr[i]!='\0')
		{
			size++;
			i++;
		}
		i = 0;
		char *temp= new char[size + 1];
		while(cStr[i]!='\0')
		{
			temp[i] = cStr[i];
			i++;
		}
		temp[i] = '\0';
		buffer = temp;
}

CMPT135_String::CMPT135_String(const CMPT135_String &s)
{
	int length = s.length();
	buffer = new char[length+1];
	for (int i = 0; i < length; i++)
	{
		buffer[i] = s[i];
	}
	buffer[length] = '\0';
}

CMPT135_String::~CMPT135_String()
{
	if (buffer != nullptr)
	{
		delete[] buffer;
		buffer = nullptr;
	}
}

CMPT135_String& CMPT135_String::operator=(const CMPT135_String &s)
{
	if (buffer != nullptr)
		delete[] buffer;
	buffer = new char[s.length()+1];
	for (int i =0; i< s.length();i++)
	{
		buffer[i] = s[i];
	}
	buffer[s.length()] = '\0';
	return *this;
}

int CMPT135_String::length() const
{
	if (buffer == nullptr)
		return 0;
	else
	{
		int len = 0;
		while (buffer[len] != '\0')
			len++;
		return len;
	}
}

bool CMPT135_String::empty() const
{
    if(this->length() == 0)
        return true;
    else
        return false;
        
}

char& CMPT135_String::operator[](const int &index) const
{
	if (index >= 0 && index < this->length())
		return buffer[index];
}

CMPT135_String CMPT135_String::operator + (const char &c) const
{
	int index = 0;
	char *temp = new char[this->length()+1];
	while(index < this->length())
	{
		temp[index] = this->buffer[index];
		index++;
	}
	temp[index] = c;
	temp[index + 1] = '\0';
    return temp;
}

CMPT135_String& CMPT135_String::operator += (const char &c)
{
	*this = *this + c;
	return *this;
}

bool CMPT135_String::operator == (const CMPT135_String &s) const
{
	int length = this->length();
	if (length != s.length())
		return false;
	else
	{
		for (int i = 0; i < length; i++)
		{
			if (buffer[i] != s[i])
				return false;
		}
		return true;
	}
}

bool CMPT135_String::operator != (const CMPT135_String &s) const
{
	if (*this == s)
		return false;
	return true;
}

istream& operator >> (istream &in, CMPT135_String &s)
{
	//This function reads from keyboard or file characters until either a TAB, EOL, or EOF is reached
	//The function ignores any leading or trailing spaces.

	//Define some useful constant values
	#define SPACE ' '
	#define TAB '\t'
	#define	EOL	'\n'

	//Delete the old value of s
	s.~CMPT135_String();

	//Skip leading spaces, tabs, and empty lines
	char ch;
	while (!in.eof())
	{
		in.get(ch);
		if (ch == SPACE || ch == TAB || ch == EOL)
			continue;
		break;
	}

	//Append the value in ch to s
	if (ch != SPACE && ch != TAB && ch != EOL)
		s += ch;

	//Read characters into s until a TAB or EOL or EOF is reached
	while (!in.eof())
	{
		in.get(ch);
		if (ch == TAB || ch == EOL || in.eof())
			break;
		else
			s += ch;
	}

	//Remove any trailing spaces
	int trailingSpacesCount = 0;
	for (int i = s.length()-1; i >= 0; i--)
	{
		if (s[i] != SPACE)
			break;
		trailingSpacesCount++;
	}
	CMPT135_String temp;
	for (int i = 0; i < s.length()-trailingSpacesCount; i++)
		temp += s[i];
	s = temp;

	return in;
}

ostream& operator << (ostream &out, const CMPT135_String &s)
{
	for (int i = 0; i < s.length(); i++)
		out << s[i];
	return out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class SmarterArray
{
private:
	T *A;
	int size;

public:
	//Constructors
	SmarterArray(); //Implemented for you
	SmarterArray(const T*, const int&); //Deep copy of the argument
	SmarterArray(const SmarterArray<T>&); //Deep copy of the argument

	//Assignment operator
	SmarterArray<T>& operator = (const SmarterArray<T>&); //Memory clean up and deep copy of the argument

	//Destructor
	~SmarterArray(); //Memory clean up

	//Getters, Setters, operators and other functions
	int getSize() const; //Return the number of elements in the container
	T& operator[](const int&) const; //Assert index and then return the element at the given index
	int find(const T&) const; //Return the index of the first element that is == to the argument. 
								//Return -1 if not found.
	void append(const T&);  //Store the argument value after the last element
	void insert(const int &, const T&); //Assert the integer argument index >= 0 && index <= size and then
										//Insert the T type argument into the calling object at the index.
										//If the integer argument is equal to size, then perform append
	bool remove(const int&); //If the index is valid, then remove the element at the index argument
							//from the calling object and return true. Otherwise return false. 
							//You don't need to assert the index argument.
	bool operator == (const SmarterArray<T>&) const; //return true if sizes are equal and 
														//elements at same indexes are equal
	
	template <class T1>
	friend ostream& operator << (ostream&, const SmarterArray<T1>&); //Implemented for you
};

template <class T>
SmarterArray<T>::SmarterArray()
{
	this->A = nullptr;
	this->size = 0;
}

template <class T>
SmarterArray<T>::SmarterArray(const T*A,const int &size)
{
	this->size=size;
	if(this->getSize()>0)
	{
		this->A =new T[this->getSize()];
		for(int i=0;i <this->getSize();i++)
			this->A[i] = A[i];
	}
}

template<class T>
SmarterArray<T>::SmarterArray(const SmarterArray<T> &L)
{
	this->size = L.getSize();
	if(this->getSize()>0)
	{
		this->A = new T[this->getSize()];
		for(int i = 0; i<this->getSize(); i++)
		    this->A[i] = L[i];
	}
}

template<class T>
SmarterArray<T>& SmarterArray<T> :: operator = (const SmarterArray<T> &L)
{
	if(this == &L)
		return *this;
	this->~SmarterArray();
	this->size = L.getSize();
	if(this->getSize()>0)
	{
		this->A = new T[this->getSize()];
		for(int i = 0; i < this->getSize(); i++)
			this->A[i] = L[i];
	}
	return *this;
}

template<class T>
SmarterArray<T>::~SmarterArray()
{
	if(this->getSize()>0)
	{
		delete[]this->A;
		this->size = 0;
		A = nullptr;
	}
}

template<class T>
int SmarterArray<T>::getSize()const
{
	return this->size;
}

template<class T>
T& SmarterArray<T>::operator[](const int&index)const
{
	assert(index>=0 && index <this->getSize());
	return this->A[index];
}

template <class T>
int SmarterArray<T>::find(const T&e) const
{
	for(int i=0;i<this->getSize();i++)
		if(this->A[i]==e)
			return i; 
	return -1;
}

template <class T>
void SmarterArray<T>::append(const T &e)
{
	T *temp = new T[this->getSize() +1];
	for(int i = 0; i<this->getSize(); i++)
		temp[i] = this->A[i];
	temp[this->getSize()] = e;
	if(this->getSize() > 0)
		delete[] this->A;
	this->A = temp;
	this->size += 1;
}

template <class T>
void SmarterArray<T>::insert(const int &index, const T&e)
{
    assert(index >= 0 && index <=this->getSize());
	if(index == size)
		this->append(e);
	else
	{
		T* temp = new T[this->getSize()+1];
		for(int i = 0; i < index; i++)
			temp[i] = this->A[i];
		temp[index] = e;
		for(int i = index + 1; i <this->getSize()+1; i++)
			temp[i] = A[i-1];
		 if(this->getSize()>0)
			 delete[]this->A;
		this->A = temp;
		this->size++;
	}
}

template<class T>
bool SmarterArray<T>::remove(const int &index)
{
	if(index<0 || index>=this->getSize())
		return false;
	else
	{
		 T *temp = new T[this->getSize()-1];
		 for(int i=0; i<index; i++)
			 temp[i] = this->A[i];
		 for(int i = index+1; i<this->getSize(); i++)
			 temp[i-1] = this->A[i];
		 if(this->getSize()>0)
			 delete[]this->A;
		 this->A = temp;
		 this->size -= 1;
		 return true;
	}
}

template<class T>
bool SmarterArray<T>::operator == (const SmarterArray<T>&e) const 
{
	if(this->size!=e.size)
		return false;
	else
	{
		for(int i=0;i<this->size;i++)
		{
			if((*this)[i]!=e[i])
				return false;
		}
		return true;
	}	
}

template <class T>
ostream& operator << (ostream& out, const SmarterArray<T>& L)
{
	if (L.getSize() == 0)
		out << "[Empty List]";
	else
	{
		for (int i = 0; i < L.getSize()-1; i++)
			out << L[i] << endl;
		out << L[L.getSize()-1] << endl;
	}
	return out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Edge
{
	int desVertexIndex; //the index (in the graph) of the destination vertex of this edge
	double cost; //cost of an edge
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Vertex
{
private:
	CMPT135_String name; //name of the vertex
	SmarterArray<Edge> E; //edges emanating from this vertex. All the elements of E have the same origin 
//vertex which is the this object. But they have different destination vertices which are given by the 
//desVertexIndex member variable of each element

public:
	Vertex(); //Assign name = "N/A" and initialize E to an empty container
	Vertex(const CMPT135_String &); //Assign name = the argument and initialize E to an empty container
	CMPT135_String getName() const; //Return the name
	SmarterArray<Edge> getEdgeSet() const; //Return E
	int getEdgeSetSize() const; //Return the size of E
	Edge getEdge(const int &) const; //Assert an edge whose destination vertex index is equal to the 
										//argument exists in E and then return it
	double getEdgeCost(const int &desVertexIndex) const; //Assert an edge whose destination vertex index 
										//is equal to the argument exists in E and then return its cost
	void appendEdge(const int &desVertexIndex, const double &cost); //Assert there is no existing edge 
				//whose destination vertex index and cost are equal to the argument values and then
				//append a new element whose destination vertex index and cost are initialized with the
				//argument values to E
	friend ostream& operator << (ostream &, const Vertex &); //Implemented for you
};


Vertex::Vertex()
{
    name = "N/A";
    SmarterArray<Edge> newE;
	E = newE;
}

Vertex::Vertex(const CMPT135_String &v)
{
    name = v;
    SmarterArray<Edge> newE;
	E = newE;
}

CMPT135_String Vertex::getName() const
{
    return name;
}

SmarterArray<Edge> Vertex::getEdgeSet() const
{
    return E;
}

int Vertex::getEdgeSetSize() const
{
    return E.getSize();
}

Edge Vertex::getEdge(const int &index) const
{
    int edgeIndex = -1;
    for(int i=0; i<this->getEdgeSetSize(); i++)
    {
        if(E[i].desVertexIndex==index)
        {
            edgeIndex = i;
            break;
        }
    }
    assert(edgeIndex>=0 && edgeIndex<this->getEdgeSetSize());
    return E[edgeIndex];
}

double Vertex::getEdgeCost(const int &desVertexIndex) const
{
    int edgeIndex = -1;
    for(int i=0; i<this->getEdgeSetSize(); i++)
    {
        if(E[i].desVertexIndex ==desVertexIndex)
        {
            edgeIndex = i;
            break;
        }
    }
    assert(edgeIndex>=0 && edgeIndex<this->getEdgeSetSize());
    return E[edgeIndex].cost;
}

void Vertex::appendEdge(const int &desVertexIndex, const double &cost)
{
    int check = 1;
    for(int i=0; i<this->getEdgeSetSize(); i++)
    {
        if(E[i].desVertexIndex==desVertexIndex && E[i].cost==cost) 
        {
            check=0;
            break;
        }
    }
    assert(check != 0);
    Edge temp;
    temp.desVertexIndex = desVertexIndex;
    temp.cost = cost;
    this->E.append(temp);
}

ostream& operator << (ostream &out, const Vertex &vertex)
{
	out << "Name = " << vertex.name << endl;
	out << "Edge Set" << endl;
	for (int i = 0; i < vertex.E.getSize(); i++)
		out << "\t to ---> " << vertex.E[i].desVertexIndex << ", cost = " << vertex.E[i].cost << endl;
	return out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Graph
{
private:
	SmarterArray<Vertex> V;
public:
	Graph();//Construct empty graph
	Graph(const char *); //Construct a graph from a text file whose path is given by the argument
        //The text file input will consist in every line a pair of cities and the cost to go from one to 
        //the other. The pair of cities and their cost will be separated by one or more SPACE or TAB 
        //characters. It doesn't matter how many spaces or tabs are present. BUT THERE HAS TO BE AT LEAST
        //ONE TAB CHARACTER between the pairs of cities and AT LEAST ONE TAB between the second city and 
        //the cost. This is because the CMPT135_String class uses TAB as a deliminator (separator). This 
        //means city names can be made up of one or more words separated by spaces. An example of one line
        //of text in the input text file is:
        //        New Westminster             Port Coquitlam        4.5
        //In this example, there has to be at least one TAB char between "New Westminster" and "Port 
        //Coquitlam" and at least one TAB character between "Port Coquitlam" and 4. Of course there can be 
        //more than one TAB characters. The number of TABs can be equal or different. There are can be 
        //zero or more spaces as much as you like without causing any problem. Moreover there can be as 
        //many empty lines as one likes at the end of the file. However there MUST NOT BE any empty line 
        //before the last line consisting of city pair and cost.
        /*
        Thus this function should perform the following tasks
			1.	Construct a non-default file input streaming object using the argument file name
			2.	Assert the file is opened successfully
			3.	While EOF is not reached
			a.	Read city name (CMPT135_String data type). This is the departure city.
			b.	If departure city is empty CMPT135_String object, then break.
			c.	Read city name (CMPT135_String data type). This is the destination city.
			d.	Read the cost
			e.	Append a new vertex whose name is the departure city and whose edge set is empty. You must use the appendVertex member function to append appropriately.
			f.	Append a new vertex whose name is the destination city and whose edge set is empty. You must use the appendVertex member function to append appropriately.
			g.	Append a new edge from the departure city to the destination city with a cost read in part (d) above.
			h.	Append a new edge from the destination city to the departure city with a cost read in part (d) above.
			4.	Close the input file stream object and you are done.
        */
	SmarterArray<Vertex> getVertexSet() const; //Return V
	int getVertexSetSize() const; //Return the number of elements of V
	Vertex getVertex(const int &) const; //Assert the index argument and then return the element at index
	int getVertexIndex(const CMPT135_String &) const; //Return the index of an element whose name matches														//the argument. If no such element is found, return -1
													//Assertion is not required
	int getVertexIndex(const Vertex &) const; //Return the index of the element whose name matches the
											//name of the vertex argument. If no such element is found, 
											//return -1. Assertion is not required
	CMPT135_String getRandomVertexName() const; //Pick a vertex at random and return its name
	void appendVertex(const Vertex &); //Append the argument only if no such vertex already exists
									    //If same name vertex already exists then do nothing (just return)
										//Assertion is not required
	void appendVertex(const CMPT135_String &); //Append a new vertex with the given name and empty E
	void appendEdge(const CMPT135_String &dep, const CMPT135_String &des, const double &cost); //Assert 
//two vertices whose names match the arguments exist. Then append an edge to the vertex whose name matches
//the dep argument. The destination vertex index of the edge must be set to the index of the vertex whose 
//name matches des and its cost must be set to the cost argument
	friend ostream& operator << (ostream &, const Graph &); //Implemented for you
};

//Constructor
Graph::Graph()
{
    SmarterArray<Vertex> newV;
	V = newV;
}

Graph::Graph(const char *g)
{
    ifstream fin(g);
    assert(!fin.fail());
    while(!fin.eof())
    {
		CMPT135_String departure, destination;
		double cost;
		fin >> departure;
		if(departure.empty()==true)
		{
			break;
		}
		fin >> destination;
		fin >> cost;
		this->appendVertex(departure);
		this->appendVertex(destination);
		this->appendEdge(departure, destination, cost);
		this->appendEdge(destination, departure, cost);
    }
	fin.close();
}

SmarterArray<Vertex> Graph::getVertexSet() const
{
	return V;
}

int Graph::getVertexSetSize() const
{
	return V.getSize();
}

Vertex Graph::getVertex(const int &index) const
{
	assert(index>=0 && index<this->getVertexSetSize());
	return V[index];
}

int Graph::getVertexIndex(const CMPT135_String &s) const
{
	for(int i=0; i<this->getVertexSetSize(); i++)
	{
		if(V[i].getName() == s)
		{
			return i;
		}
	}
	return -1;
}

int Graph::getVertexIndex(const Vertex &v) const
{
	for(int i=0; i < V.getSize(); i++)
	{
		if(V[i].getName() == v.getName())
		{
			return i;
		}
	}
	return -1;
}

CMPT135_String Graph::getRandomVertexName() const
{
	int index = rand() % V.getSize();
	return V[index].getName();
}

void Graph::appendVertex(const Vertex &v)
{
	int index = this->getVertexIndex(v);
	if(index != -1)
		return;
	V.append(v);
}

void Graph::appendVertex(const CMPT135_String &s)
{
	int index = this->getVertexIndex(s);
	if (index != -1)
		return;
	Vertex temp = Vertex(s);
	this->appendVertex(temp);
	return;
}

void Graph::appendEdge(const CMPT135_String &dep, const CMPT135_String &des, const double &cost)
{
	int dep_index = this->getVertexIndex(dep);
	int des_index = this->getVertexIndex(des);
	assert(dep_index>=0 && dep_index<this->getVertexSetSize());
	assert(des_index>=0 && des_index<this->getVertexSetSize());
	V[dep_index].appendEdge(des_index, cost);
}

ostream& operator << (ostream &out, const Graph &g)
{
	const int CITY_NAME_WIDTH = 25;
	out << endl;
	out << "The graph has " << g.getVertexSetSize() << " vertices." << endl;
	out << "These vertices are" << endl;
	for (int i = 0; i < g.getVertexSetSize(); i++)
	{
		Vertex v = g.V[i];
		out << "Vertex at index " << i << " = " << v.getName() << endl;
	}
	out << endl;
	out << "Each vertex together with its edge set looks like as follows" << endl;
	for (int i = 0; i < g.getVertexSetSize(); i++)
	{
		Vertex v = g.V[i];
		out << v << endl;
	}
	out << endl;
	out << "The graph connectivities are as follows..." << endl;
	out.setf(ios::fixed | ios::left);	//Left aligned fixed decimal places formatting
	for (int i = 0; i < g.getVertexSetSize(); i++)
	{
		Vertex depVertex = g.getVertex(i);
		SmarterArray<Edge> E = depVertex.getEdgeSet();
		for (int j = 0; j < E.getSize(); j++)
		{
			int desVertexIndex = E[j].desVertexIndex;
			Vertex desVertex = g.getVertex(desVertexIndex);
			out << depVertex.getName() << setw(CITY_NAME_WIDTH - depVertex.getName().length()) << " ";
			out << desVertex.getName() << setw(CITY_NAME_WIDTH - desVertex.getName().length()) << " ";
			out << setprecision(2) << E[j].cost << endl;
		}
	}
	out.unsetf(ios::fixed | ios::left);	//Removing formatting
	cout.precision(0);					//Resetting the decimal places to default
	return out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Path
{
private:
	SmarterArray<CMPT135_String> P; //The names of the vertices along the path

public:
	Path(); //Construct an empty path

	int length() const; //Return the number of vertices in the path (the number of elements of p)
	int find(const CMPT135_String &) const; //Return the index of element of p whose name matches the 
											//argument. If no element satisfies the condition, then return -1
	double computePathCost(const Graph &) const; //Compute the sum of the costs of edges along this path 
											//given the underlying graph argument
	CMPT135_String& operator [] (const int &) const; //Assert index is valid and then return the 
											//element of p at the given index
	void append(const CMPT135_String &); //Append the argument to the calling object
	void insert(const int &index, const CMPT135_String &); //Assert the condition index >= 0 && 
											//index <= the length and then insert the CMPT135_String argument 
											//at the specified index
	void remove(const int &); //Assert the index argument and then remove the element at the specified index
	friend ostream& operator << (ostream &, const Path &); //Implemented for you.
};

Path::Path()
{
	SmarterArray<CMPT135_String> newP;
	P = newP;
}

int Path::length() const
{
	return P.getSize();
}

int Path::find(const CMPT135_String &s) const
{
	int index = P.find(s);
	return index;
}

double Path::computePathCost(const Graph &g) const
{
	double path_cost = 0.0;
	for(int i=0; i<this->length()-1; i++)
	{
		int depIndex = g.getVertexIndex(P[i]);
		int desIndex = g.getVertexIndex(P[i+1]);
		path_cost += g.getVertex(depIndex).getEdgeCost(desIndex);
	}
	return path_cost;
}

CMPT135_String& Path::operator [] (const int &index) const
{
	assert(index>=0 && index <this->length());
	return P[index];
}

void Path::append(const CMPT135_String &s)
{
	P.append(s);
	return;
}

void Path::insert(const int &index, const CMPT135_String &s)
{
	P.insert(index, s);
	return;
}

void Path::remove(const int &index)
{
	assert(index>=0 && index<this->length());
	P.remove(index);
}

ostream& operator << (ostream &out, const Path &p)
{
	out << "[";
	if (p.length() > 0)
	{
		for (int i = 0; i < p.length()-1; i++)
			out << p[i] << " -> ";
		out << p[p.length()-1];
	}
	out << "]";
	return out;
}

Path computeMinCostPath(Graph &g, CMPT135_String &departure, CMPT135_String &destination, Path &currentPath = Path())
{
	assert(g.getVertexSetSize()>0);
	int depVertexIndex = g.getVertexIndex(departure);
	int desVertexIndex = g.getVertexIndex(destination);
	assert(depVertexIndex>=0 && depVertexIndex<g.getVertexSetSize());
	assert(desVertexIndex>=0 && desVertexIndex<g.getVertexSetSize());

	if(desVertexIndex==depVertexIndex)
	{
		Path minCostPath = currentPath;
		minCostPath.append(destination);
		cout << "Path Found: " << minCostPath << " with cost " << minCostPath.computePathCost(g) << endl;
		return minCostPath;
	}
	else if (currentPath.find(destination) != -1)
	{
		Path minCostPath = currentPath;
		return minCostPath;
	}
	else
	{
		Vertex depvertex = g.getVertex(depVertexIndex);
		SmarterArray<Edge> E = depvertex.getEdgeSet();
		Path minCostPath = Path();
		currentPath.append(departure);
		for(int i=0; i<E.getSize(); i++)
		{
			CMPT135_String nextVertexName;
			nextVertexName = g.getVertex(E[i].desVertexIndex).getName();
			if(currentPath.find(nextVertexName) != -1)
			{
				continue;
			}
			Path candidatePath = computeMinCostPath(g, nextVertexName, destination, currentPath);
			if(candidatePath.length()==0)
			{
				continue;
			}
			if(candidatePath[candidatePath.length()-1] != destination)
			{
				continue;
			}
			if(minCostPath.length() == 0)
			{
				minCostPath = candidatePath;
				continue;
			}
			if(candidatePath.computePathCost(g) < minCostPath.computePathCost(g))
			{
				minCostPath = candidatePath;
				continue;
			}
		}
		currentPath.remove(currentPath.length()-1);
		return minCostPath;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	srand(time(0));
	Graph g("Connectivity Map.txt");
	cout << "Graph constructed successfully." << endl;
	cout << g << endl;
	CMPT135_String departure = g.getRandomVertexName();
	CMPT135_String destination = g.getRandomVertexName();
	cout << "Computing shortest path from " << departure << " to " << destination << endl;
	Path minCostPath = computeMinCostPath(g, departure, destination);
	cout << endl;
	cout << "Departure: " << departure << endl;
	cout << "Destination: " << destination << endl;
	if (minCostPath.length() == 0)
		cout << "No path found." << endl;
	else
		cout << "The minimum cost path is: " << minCostPath << " with cost = " << minCostPath.computePathCost(g) << endl;
	
	system("Pause");
	return 0;
}

