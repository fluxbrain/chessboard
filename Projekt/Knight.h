#pragma once

// Projekt - Bjoern Oke Maas

#include "Piece.h"
#include "Field.h"

class Knight : public Piece
{

public:
	Knight(Color color) : Piece(color)
	{
	}

	std::stringstream draw();

	void move(Field *src, Field *dst);
};