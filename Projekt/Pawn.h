#pragma once

// Projekt - Bjoern Oke Maas

#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(Color color) : Piece(color)
	{
	}
	std::stringstream draw();
};