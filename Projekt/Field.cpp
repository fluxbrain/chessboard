// Projekt - Bjoern Oke Maas

#include "Field.h"
#include <iostream>

using namespace std;

Field::Field()
{
}

Field::~Field()
{
}

Field::Field(int f_row, char f_column) : Node(std::to_string(f_row) + f_column)
{
	this->row = f_row;
	this->column = toupper(f_column);
	this->piece = NULL;

	if (row % 2 == 0)
	{
		if (strchr("ACEG", column))
		{
			color = Color::WHITE;
		}
		else
		{
			color = Color::BLACK;
		}
	}
	else
	{
		if (strchr("ACEG", column))
		{
			color = Color::BLACK;
		}
		else
		{
			color = Color::WHITE;
		}
	}

}

int Field::getRow()
{
	return this->row;
}

char Field::getColumn()
{
	return this->column;
}

Piece *Field::getPiece()
{
	return this->piece;
}

void Field::setPiece(Piece *piece)
{
	this->piece = piece;
}

std::stringstream Field::draw()
{
	std::stringstream ss;
	if (piece == NULL)
	{
		if (color == Color::BLACK)
		{
			ss.str(" ");
		}
		else
		{
			ss.str("X");
		}
	}
	else
	{
		ss << piece->draw().str();
	}
	return ss;
}

