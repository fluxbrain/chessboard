#pragma once

// Projekt - Bjoern Oke Maas

#include <list>
#include <vector>
#include <string>
#include "Field.h"

class Chessboard
{
public:
	Chessboard();
	~Chessboard();

	Field &findPiece(char piece, Color color);
	Field &findField(char column, int row);

	void initialize(std::ifstream &a);
	void initialize(std::string figureListAsString);
	void initialize(std::vector<std::string> figuresList);

	std::stringstream draw();
	std::list<Field*> getFields();

private:
	std::list<Field *> fields;

	std::vector <std::string> getFiguresFromFile(std::ifstream &infile);
	std::vector <std::string> getFiguresFromString(std::string figureListAsString);
	std::vector <std::string> extractSubstr(std::string line);

	int checkInput(std::string substr);

	Piece *createPiece(char figure);

	Color getColor(char c);
};