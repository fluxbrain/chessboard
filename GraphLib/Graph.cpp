#include "Graph.h"
#include <fstream>
#include <algorithm>
#include <limits>
#include <iostream>
#include <queue>

using namespace std;

//---------------------------------------------------------------------------------------------------------------------

Node* Graph::findNode(const std::string& id)
{
	// - soll einen Node mit der gegebenen id in m_nodes suchen
	// - gibt den Pointer auf den Node zurück, wenn er gefunden wurde.
	// - gibt NULL zurück, falls kein Node mit der id gefunden wurde.

	for (std::list<Node*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
	{
		if ((*it)->getID().compare(id) == 0)
		{
			return (*it);
		}
	}
	return NULL;
}


//---------------------------------------------------------------------------------------------------------------------

Node& Graph::addNode(Node* pNewNode)
{
	// Überprüfen Sie, ob schon ein Node mit der gegeben id im Graph vorhanden ist!
	// Falls ja:
	//  - Exception werfen
	// Falls nein:
	//  - den neuen Node 'pNewNode' in m_nodes einfügen
	//  - Referenz auf den neuen Node zurück geben

	if (findNode(pNewNode->getID()) == NULL)
	{
		m_nodes.push_back(pNewNode);
		return *pNewNode;
	}
	else
	{
		string msg = "Node " + pNewNode->getID() + " existiert bereits!";
		throw invalid_argument(msg);
	}
}


//---------------------------------------------------------------------------------------------------------------------

Edge& Graph::addEdge(Edge* pNewEdge)
{
	// - die neue Edge 'pNewEdge' in m_edges einfügen
	// - Referenz auf die neue Edge zurück geben

	try
	{
		addNode(&(pNewEdge->getDstNode()));
	}
	catch (invalid_argument)
	{
	}

	try
	{
		addNode(&(pNewEdge->getSrcNode()));
	}
	catch (invalid_argument)
	{
	}

	m_edges.push_back(pNewEdge);
	return *pNewEdge;
}


//---------------------------------------------------------------------------------------------------------------------

Graph::~Graph()
{
	// - soll alle Edges im Graph löschen (delete)
	// - soll alle Nodes im Graph löschen (delete)

	for (list<Edge*>::iterator it = m_edges.begin(); it != m_edges.end(); it++)
	{
		delete (*it);
	}

	for (list<Node*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
	{
		delete (*it);
	}



}


//---------------------------------------------------------------------------------------------------------------------

void Graph::remove(Node& rNode)
{
	// - alle Edges, die mit rNode verbunden sind, müssen entfernt werden!
	// - finden sie den Pointer mit der Adresse von 'rNode' in m_nodes.
	// 		- der Pointer auf rNode soll aus m_nodes entfernt werden!
	// 		- der Pointer auf rNode muss mit 'delete' freigegeben werden!

	for (list<Edge*>::iterator it = (rNode.getOutEdges()).begin(); it != (rNode.getOutEdges()).end(); )
	{
		remove(**it++);
	}

	for (list<Edge*>::iterator it = (rNode.getInEdges()).begin(); it != (rNode.getInEdges()).end(); )
	{
		remove(**it++);
	}

	for (list<Node*>::iterator it = m_nodes.begin(); it != m_nodes.end(); )
	{
		if (*it == &rNode)
		{
			it = m_nodes.erase(it);
			delete &rNode;
		}
		else
		{
			it++;
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------

void Graph::remove(Edge& rEdge)
{
	// - der Pointer auf rEdge muss aus m_edges entfernt werden!
	// - der Pointer auf rEdge muss mit 'delete' freigegeben werden!

	list<Edge*>::iterator i = m_edges.begin();
	while (i != m_edges.end())
	{
		if (*i == &rEdge)
		{
			m_edges.erase(i++);
			delete &rEdge;
		}
		else
		{
			++i;
		}
	}
}


//---------------------------------------------------------------------------------------------------------------------

std::vector<Edge*> Graph::findEdges(const Node& rSrc, const Node& rDst)
{
	std::vector<Edge*> ret;

	// - findet alle edges, mit rSrc als Source-Node und rDst als Destination-Node.
	// - füge die Zeiger der Edges in den vector 'ret' ein.

	list<Edge*>::iterator i = m_edges.begin();
	while (i != m_edges.end())
	{
		if (&((*i)->getSrcNode()) == &rSrc && &((*i)->getDstNode()) == &rDst)
		{
			ret.push_back(*i);
		}
		i++;
	}
	return ret;
}

//---------------------------------------------------------------------------------------------------------------------

void Graph::findShortestPathDijkstra(std::deque<Edge*>& rPath, const Node& rSrcNode, const Node& rDstNode)
{
	priority_queue<Node> nodeQ;
	double altDist = 0;

	/*** Nodes initialisieren und in nodeQ einfuegen ***/

	for (std::list<Node*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
	{
		if ((*it)->getID().compare(rSrcNode.getID()) == 0)
		{
			(*it)->setDist(0);
			(*it)->setPrev(NULL);
		}
		else
		{
			(*it)->setDist(DBL_MAX);
			(*it)->setPrev(NULL);
		}
		nodeQ.push(**it);
	}

	/*** vom Start aus alle Nodes besuchen und Distanzen berechnen.
	In jeder Node wird die optimale Vorgaenger-edge gespeichert ***/

	while (!nodeQ.empty())
	{
		Node currentNode = nodeQ.top();
		nodeQ.pop();
		Node* test = &currentNode;

		for (std::list<Edge*>::iterator it = currentNode.getOutEdges().begin(); it != currentNode.getOutEdges().end(); it++)
		{
			altDist = (**it).getWeight() + currentNode.getDist();

			if (altDist < (**it).getDstNode().getDist())
			{
				(**it).getDstNode().setDist(altDist);
				(**it).getDstNode().setPrev(*it);
				nodeQ.push((**it).getDstNode());
			}
		}

	}

	/*** vom Ziel bis Start werden die optimalen edges in rPath eingetragen.
	Die edges in rPath fuehren dann vom Start (front) zum Ziel (back). ***/

	Edge* prev = (rDstNode.getPrev());

	while (prev != NULL)
	{
		rPath.push_front(prev);
		prev = prev->getSrcNode().getPrev();
	}
}

//---------------------------------------------------------------------------------------------------------------------

