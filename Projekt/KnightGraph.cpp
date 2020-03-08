// Projekt - Bjoern Oke Maas

#include <iostream>
#include "list"
#include "KnightGraph.h"
#include "Chessboard.h"
#include "Knight.h"
#include "King.h"

KnightGraph::KnightGraph(Chessboard *chessboard) : Graph()
{
	for (Field *srcField : chessboard->getFields())
	{
		if (!(std::find(this->m_nodes.begin(), this->m_nodes.end(), srcField) != this->m_nodes.end()))
		{
			try
			{
				this->addNode(srcField);
			}
			catch (std::invalid_argument)
			{
			}
		}
		if (srcField->getPiece() != NULL)
		{
			Piece *piece = srcField->getPiece();
			if (dynamic_cast<Knight *>(piece) != NULL && piece->getColor() == Color::WHITE)
			{
				addPossibleEdges(chessboard, srcField);
			}
		}
		else
		{
			addPossibleEdges(chessboard, srcField);
		}
	}
}

KnightGraph::~KnightGraph()
{
}

/*-------------------------------------------------------------------------
	moegliche Zuege (edges) vom srcField werden dem Graphen hinzugefuegt
*/
void KnightGraph::addPossibleEdges(Chessboard *chessboard, Field *srcField)
{
	std::list<Field *> dstFields = calculateDstFields(chessboard, srcField);
	for (Field *dst : dstFields)
	{
		this->addEdge(new KnightMove(srcField, dst));
	}
}

/*-------------------------------------------------------------------------
	mögliche Zielfelder (nodes) vom srcField werden ermittelt
*/
std::list<Field *> KnightGraph::calculateDstFields(Chessboard *chessboard, Field *srcField)
{
	std::list<Field *> dsts;
	int srcRow = srcField->getRow();
	char srcColumn = srcField->getColumn();
	int srcColumnInt = srcColumn - 64;

	int ROW[8] =    { 2, 1, -1, -2, -2, -1, 1, 2 };
	int COLUMN[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

	for (int i = 0; i < 8; i++)
	{
		int x = srcRow + ROW[i];
		int y = srcColumnInt + COLUMN[i];

		if (x > 0 && y > 0 && x <= 8 && y <= 8)
		{
			Field *dstField = &(chessboard->findField(char(y + 64), x));
			if (dstField->getPiece() != NULL)
			{
				Piece *piece = dstField->getPiece();
				if (piece->getColor() == Color::BLACK)
				{
					dsts.push_back(dstField);
				}
			}
			else
			{
				dsts.push_back(dstField);
			}
		}
	}
	return dsts;
}