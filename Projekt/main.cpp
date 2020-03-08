// Projekt - Bjoern Oke Maas

#include <iostream>
#include <fstream>
#include <deque>
#include "Node.h"
#include "Edge.h"
#include "NodeIdException.h"
#include "Chessboard.h"
#include "KnightGraph.h"
#include "UI.h"

using namespace std;

string sourceFilePrefix = "./board/Board";
string fileExtension = ".txt";
string resultFilePrefix = "./board/result";
string createFileName(string filePrefix, int i);
void writeInFile(ofstream &resultFile, Field &src, Field &dst, std::deque<Edge *> rPath, Chessboard &chessboard);
void playChess(Chessboard& chessboard, int counter);
void playChess(Chessboard& chessboard);

int main()
{
/*-------------------------------------------------------------------------
	Die vier Beispieldateien werden eingelesen und abgearbeitet.
*/
	for (int i = 1; i < 5; i++)
	{
		string filename = createFileName(sourceFilePrefix, i);
		std::ifstream infile(filename);

		Chessboard *chessboard = new Chessboard();

		try { chessboard->initialize(infile); }
		catch (invalid_argument& ex) 
		{ 
			cerr << "Fehler: " << ex.what() << endl;
			delete chessboard;
			continue;
		}

		try { playChess(*chessboard, i); }
		catch (invalid_argument& ex) { cerr << "Fehler: " << ex.what() << endl; }
		delete chessboard;
	}

	/*-------------------------------------------------------------------------
	Initialisierungsdaten werden von cin gelesen und verarbeitet.
	*/
	while (1)
	{
		string input = UI::userInput();

		if (input.compare("exit") == 0)
		{ break; }

		Chessboard *chessboard = new Chessboard();

		try { chessboard->initialize(input); }
		catch (invalid_argument& ex)
		{ 
			cerr << "Fehler: " << ex.what() << endl;
			delete chessboard;
			continue;
		}

		try { playChess(*chessboard); }
		catch (invalid_argument& ex) { cerr << "Fehler: " << ex.what() << endl; }
		delete chessboard;
	}

	return 0;
}

/*-------------------------------------------------------------------------
	Ausgabe in Konsole: Brett & optimaler Pfad 
*/
void playChess(Chessboard &chessboard)
{
	KnightGraph *knightGraph = new KnightGraph(&chessboard);

	string s = chessboard.draw().str();
	cout << s << endl;

	Field &whiteKnight = chessboard.findPiece('s', Color::WHITE);
	Field &blackKing = chessboard.findPiece('k', Color::BLACK);

	if (&whiteKnight == NULL || &blackKing == NULL)
	{
		delete knightGraph;
		throw exception("Weisser Springer und/oder schwarzer Koenig fehlt!");
	}

	deque<Edge *> rPath;
	knightGraph->findShortestPathDijkstra(rPath, whiteKnight, blackKing);

	if (rPath.size() == 0)
	{
		cout << "Es gibt leider keine Loesung!\n";
	}
	else
	{
		for (Edge *n : rPath)
		{
			cout << n->toString() << '\n';
		}
	}
	delete knightGraph;
}

/*-------------------------------------------------------------------------
	Ausgabe in Konsole und Datei: Brett & optimaler Pfad
*/
void playChess(Chessboard &chessboard, int counter)
{
	ofstream resultFile;
	string filename = createFileName(resultFilePrefix, counter);
	resultFile.open(filename);

	KnightGraph *knightGraph = new KnightGraph(&chessboard);

	string s = chessboard.draw().str();
	cout << s << endl;

	Field &whiteKnight = chessboard.findPiece('s', Color::WHITE);
	Field &blackKing = chessboard.findPiece('k', Color::BLACK);

	if (&whiteKnight == NULL || &blackKing == NULL)
	{
		resultFile.close();
		delete knightGraph;
		throw exception("Kein weisser Springer und/oder kein Schwarzer Koenig!");
	}

	deque<Edge *> rPath;
	knightGraph->findShortestPathDijkstra(rPath, whiteKnight, blackKing);

	writeInFile(resultFile, whiteKnight, blackKing, rPath, chessboard);
	resultFile.close();

	delete knightGraph;
}

/*-------------------------------------------------------------------------
	
*/
void writeInFile(ofstream &resultFile, Field &src, Field &dst, deque<Edge *> rPath, Chessboard &chessboard)
{
	resultFile	<< "Ziehe weissen Springer von " << src.getID() 
				<< " zum schwarzen Koenig auf " << dst.getID() << "\n\n";

	string s = chessboard.draw().str();
	resultFile << s << endl;

	if (rPath.size() == 0)
	{
		cout << "Es gibt leider keine Loesung!\n";
		resultFile << "Es gibt leider keine Loesung!";
	}

	for (Edge *n : rPath)
	{
		resultFile << n->toString() << '\n';
		cout << n->toString() << '\n';
	}
	resultFile << '\n';
	
}

/*-------------------------------------------------------------------------

*/
string createFileName(string filePrefix, int i)
{
	std::ostringstream oss;
	oss << filePrefix << i << fileExtension;
	return oss.str();
}