#pragma once

// Projekt - Bjoern Oke Maas

#include <locale>
#include "Color.h"

class Piece
{

public:
	Color color;

	Piece(Color color) : color(color)
	{
	}

	~Piece()
	{
	};

	Color getColor();

	virtual std::stringstream draw() = 0;

private:

};