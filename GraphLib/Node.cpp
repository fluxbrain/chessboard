#include "Node.h"
#include <sstream>
#include <iomanip>
#include <cctype>

using namespace std;

// static initialization
int Node::s_numInstances = 0;

Node::Node()
{
	s_numInstances++;
	stringstream s;
	s << "Node_" << setw(4) << setfill('0') << s_numInstances;
	m_id = s.str();
}

void Node::setDist(double dist)
{
	m_dist2Start = dist;
}

void Node::setPrev(Edge* prev)
{
	m_prev = prev;
}

double Node::getDist() const
{
	return m_dist2Start;
}

Edge* Node::getPrev() const
{
	return m_prev;
}

