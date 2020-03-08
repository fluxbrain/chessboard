#ifndef NODE_H
#define NODE_H

#include <math.h>
#include <float.h>
#include <string>
#include <list>

// forward-deklaration
class Edge;

class Node
{
public:

	friend bool operator<(Node const& lNode, Node const& rNode)
	{
		return  lNode.m_dist2Start > rNode.m_dist2Start;
	}

	Node();

	Node(std::string id) : m_id(id)
	{
		s_numInstances++;
	}

	virtual ~Node()
	{
	}

	std::string getID() const
	{
		return m_id;
	}

	std::list<Edge*>& getOutEdges()
	{
		return m_outgoingEdges;
	}
	std::list<Edge*>& getInEdges()
	{
		return m_incomingEdges;
	}

	void setDist(double dist);
	void setPrev(Edge* prev);

	double getDist() const;
	Edge* getPrev() const;


private:

	std::string m_id;

	std::list<Edge*> m_outgoingEdges;
	std::list<Edge*> m_incomingEdges;

	static int s_numInstances;
	double m_dist2Start = DBL_MAX;
	Edge* m_prev = NULL;

};

#endif