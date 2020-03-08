#pragma once

// Projekt - Bjoern Oke Maas

#include "Piece.h"
#include "Color.h"

class King : public Piece
{
public:
	King(Color color) : Piece(color)
	{
	}

	std::stringstream draw();
};