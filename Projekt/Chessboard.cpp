// Projekt - Bjoern Oke Maas

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <cctype>
#include <algorithm>
#include "Chessboard.h"
#include "Color.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"

using namespace std;


Chessboard::Chessboard()
{

}

Chessboard::~Chessboard()
{
}

void Chessboard::initialize(std::ifstream &infile)
{
	vector<string> figuresList = getFiguresFromFile(infile);
	initialize(figuresList);
}

void Chessboard::initialize(string figureListAsString)
{
	vector<string> figuresList = getFiguresFromString(figureListAsString);

	initialize(figuresList);
}

/*-------------------------------------------------------------------------
	Initialisieren des Brettes
*/
void Chessboard::initialize(vector<string> figuresList)
{

	for (int row = 8; row > 0; row--)
	{
		for (int column = 1; column <= 8; column++)
		{
			fields.push_back(new Field(row, char(column + 64)));
		}
	}

	for (unsigned int i = 0; i < figuresList.size(); i++)
	{
		if (figuresList.at(i).size() == 3)
		{
			char figure = figuresList.at(i)[0];
			char column = figuresList.at(i)[1];
			int row = figuresList.at(i)[2] - '0';
			Piece *piece = createPiece(figure);
			Field &field = findField(toupper(column), row);
			if ((&field) != NULL)
			{
				field.setPiece(piece);
			}

		}
	}
}

Piece * Chessboard::createPiece(char figure)
{

	Color color = getColor(figure);
	switch (figure)
	{
		case 's':
		case 'S':
			return new Knight(color);
		case 'b':
		case 'B':
			return new Pawn(color);
		case 'k':
		case 'K':
			return new King(color);
		default:
			cerr << "Ungueltiger Buchstabe fuer Figur!" << endl;
			return NULL;
	}
}

Color  Chessboard::getColor(char c)
{
	if (isupper(c) != 0)
	{
		return Color::BLACK;
	}
	return Color::WHITE;
}

std::list<Field*> Chessboard::getFields()
{
	return fields;
}

/*-------------------------------------------------------------------------
	Figurendaten aus Datei extrahieren
*/
vector<string>  Chessboard::getFiguresFromFile(std::ifstream &infile)
{
	std::string line;
	vector<string> result;

	if (infile.is_open())
	{
		while (getline(infile, line))
		{
			vector <string> tmp = extractSubstr(line);
			result.insert(result.end(), tmp.begin(), tmp.end());
		}
		infile.close();
	}
	else
	{
		throw invalid_argument("Konnte Datei nicht oeffnen!");
	}

	return result;
}

/*-------------------------------------------------------------------------
	Figurendaten aus String extrahieren
*/
vector<string>  Chessboard::getFiguresFromString(std::string line)
{
	return extractSubstr(line);
}

/*-------------------------------------------------------------------------
	String in Substrings fuer einzelne Figuren zerlegen
*/
vector <string> Chessboard::extractSubstr(string line)
{
	vector<string> result;
	line.erase(remove(line.begin(), line.end(), ' '), line.end());

	
	std::stringstream stream(line);
	while (stream.good())
	{
		string substr;
		getline(stream, substr, ',');
		if (checkInput(substr) != 0)
		{
			throw invalid_argument("Eingegebene Daten ungueltig!");
		}
		result.push_back(substr);
	}
	return result;
}

/*-------------------------------------------------------------------------
	Substrings auf Gueltigkeit pruefen
*/
int Chessboard::checkInput(std::string substr)
{
	if (substr.length() == 3
		&& strchr("sSbBkK", substr[0])
		&& strchr("abcdefghABCDEFGH", substr[1])
		&& strchr("12345678", substr[2]))
	{
		return 0;
	}
	return 1;
}

/*-------------------------------------------------------------------------
	Brettausgabe
*/
stringstream Chessboard::draw()
{
	std::stringstream stream;
	stream << "\n  A B C D E F G H \n";
	for (int digit = 8; digit > 0; digit--)
	{
		stream << digit;
		stream << "|";
		for (int column = 1; column <= 8; column++)
		{
			Field &field = findField(char(column + 64), digit);
			if ((&field) != NULL)
			{
				stream << field.draw().str();
				stream << "|";
			}
		}
		stream << "\n";
	}
	return stream;
}

/*-------------------------------------------------------------------------
	
*/
Field &Chessboard::findField(char column, int row)
{
	list<Field *>::iterator it;
	for (it = fields.begin(); it != fields.end(); ++it)
	{
		if ((*it)->getRow() == row)
		{
			if ((*it)->getColumn() == column)
			{
				return *(*it);
			}
		}
	}
	Field *pointer = NULL;
	Field &reference = *pointer;
	return reference;
}

/*-------------------------------------------------------------------------
	
*/
Field &Chessboard::findPiece(char pieceChar, Color color)
{
	for (Field *field : fields)
	{
		if (field->getPiece() != NULL)
		{
			Piece *piece = field->getPiece();
			if (piece->getColor() == color)
			{
				switch (pieceChar)
				{
					case 's':
					case 'S':
						if (dynamic_cast<Knight *>(piece) != NULL)
						{
							return *field;
						}
						break;
					case 'b':
					case 'B':
						if (dynamic_cast<Pawn *>(piece) != NULL)
						{
							return *field;
						}
						break;
					case 'k':
					case 'K':
						if (dynamic_cast<King *>(piece) != NULL)
						{
							return *field;
						}
						break;
					default:
						cerr << "Ungueltiger Buchstabe fuer Figur!" << endl;
						break;
				}
			}
		}
	}
	Field* ptr = NULL;
	return *ptr;
}