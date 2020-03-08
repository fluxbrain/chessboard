#pragma once

// Projekt - Bjoern Oke Maas

#include "list"
#include "KnightMove.h"
#include "Chessboard.h"
#include "Graph.h"

class KnightGraph : public Graph
{
public:
	KnightGraph(Chessboard* chessboard);

	~KnightGraph();

	void addPossibleEdges(Chessboard* chessboard, Field* srcField);

private:
	std::list<Field *> calculateDstFields(Chessboard *chessboard, Field *srcField);
	std::list<KnightMove*> legalMoves;
};