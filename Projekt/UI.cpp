// Projekt - Bjoern Oke Maas

#include <iomanip>
#include "UI.h"

using namespace std;

UI::UI()
{
}

UI::~UI()
{
}

std::string UI::userInput()
{
	char input[320];

	cout	<< "\nBitte geben sie eine Schachbrettinitialisierung im beschriebenen Format ein:\n"
			<< "(z.B. \"sa1,bc2,bd4,be6,Kh8\")\n"
			<< "s - Springer, b - Bauer, k - Koenig\n"
			<< "Kleinbuchstabe = weiss, Grossbuchstabe = schwarz\n"
			<< "\"exit\" fuer Programm beenden\n";

	cin.getline(input, sizeof(input));

	return input;
}