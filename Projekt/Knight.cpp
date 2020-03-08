// Projekt - Bjoern Oke Maas

#include <iostream>
#include <sstream>
#include "King.h"
#include "Knight.h"

std::stringstream Knight::draw()
{
	std::stringstream ss;
	if (this->color == Color::BLACK)
	{
		ss.str("S");
	}
	else
	{
		ss.str("s");
	}
	return ss;
}

void Knight::move(Field *src, Field *dst)
{
	if (dst->getPiece() == NULL || (dynamic_cast<King *>(dst->getPiece()) != NULL))
	{
		dst->setPiece(this);
		src->setPiece(NULL);
	}
	else
	{
		std::cerr << "Zug nicht moeglich, das Feld ist bereits besetzt.\n";
	}
}