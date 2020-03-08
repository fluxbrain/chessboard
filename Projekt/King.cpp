// Projekt - Bjoern Oke Maas

#include <sstream>
#include "King.h"

std::stringstream King::draw()
{
	std::stringstream stream;
	if (this->color == Color::BLACK)
	{
		stream.str("K");
	}
	else
	{
		stream.str("k");
	}
	return stream;
}