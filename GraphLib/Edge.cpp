#include "Edge.h"


//---------------------------------------------------------------------------------------------------------------------

Edge::Edge(Node& rSrc, Node& rDst) : m_rSrc(rSrc), m_rDst(rDst)
{
	// f�gt die Edge (this) in m_outgoingEdges des Source-Node ein.
	rSrc.getOutEdges().push_back(this);

	// f�gt die Edge (this) in m_incomingEdges des Destination-Node ein.
	rDst.getInEdges().push_back(this);
}


//---------------------------------------------------------------------------------------------------------------------

Edge::Edge(const Edge& rOther) : m_rSrc(rOther.m_rSrc), m_rDst(rOther.m_rDst)
{
	// macht das Selbe wie 'Edge(Node& rSrc, Node& rDst)'
}


//---------------------------------------------------------------------------------------------------------------------

Edge::~Edge()
{
	// - entfernt die Edge (this) aus m_outgoingEdges im Source-Node
	this->m_rSrc.getOutEdges().remove(this);
	// - entfernt die Edge (this) aus m_incomingEdges im Destination-Node
	this->m_rDst.getInEdges().remove(this);
}


//---------------------------------------------------------------------------------------------------------------------

bool Edge::isConnectedTo(const Node& rNode) const
{
	// - gibt true zur�ck, wenn rNode entweder m_rSrc und m_rDst ist.
	// Hinweis: Adressen vergleichen, um zu gucken, ob es wirklich das selbe Objekt ist!
	if (&rNode == &(this->m_rDst) || &rNode == &(this->m_rSrc))
	{
		return true;
	}
	return false;
}


//---------------------------------------------------------------------------------------------------------------------

std::string Edge::toString() const
{
	std::string result;
	result = m_rSrc.getID() + " -> " + m_rDst.getID();
	return result;
}


//---------------------------------------------------------------------------------------------------------------------
