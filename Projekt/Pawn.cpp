// Projekt - Bjoern Oke Maas

#include <sstream>
#include "Pawn.h"

std::stringstream Pawn::draw()
{
	std::stringstream stream;
	if (this->color == Color::BLACK)
	{
		stream.str("B");
	}
	else
	{
		stream.str("b");
	}
	return stream;
}