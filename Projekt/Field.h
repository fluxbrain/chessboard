#pragma once

// Projekt - Bjoern Oke Maas

#include <sstream>
#include <iosfwd>
#include "Color.h"
#include "Piece.h"
#include "Node.h"

class Field : public Node
{
	Field();

	~Field();

public:
	Field(int f_row, char f_column);
	int getRow();
	char getColumn();
	Piece* getPiece();
	void setPiece(Piece* piece);
	std::stringstream draw();

private:
	int row;
	char column;
	Piece* piece;
	Color color;
};