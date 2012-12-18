/* David Russell's 3 Most Important Rules of Programming
 * 
 * 1. BACK IT UP!
 * 2. BACK IT UP!
 * 3. BACK IT UP!
 *
 */

#include <iostream>
#include <ctime>
#include <string>
//#include <Windows.h>
using namespace std;

#include "World.h"
#include "Ant.h"
#include "Lion.h"

// Global Variables
World sim;
int w = sim.getWidth();
int h = sim.getHeight();
string str = "";
bool debug = false;

void createAnt(int count = 1)
{
	for (unsigned ant = 0; ant < count; ant++)
	{
		int x = 0; int y = 0;
		do {x = rand() % w; y = rand() % h;}				// Generate Random Coordonate
		while (sim.getOrganism(x,y) != NULL);				// Until Space is Available
		sim.setOrganism(new Ant(x, y, &sim, w, h), x, y);	// Put an Organism in that Space
	}
}
void createLion(int count = 1)
{
	for (unsigned lion = 0; lion < count; lion++)
	{
		int x = 0; int y = 0;
		do {x = rand() % w; y = rand() % h;}					// Generate Random Coordonate
		while (sim.getOrganism(x,y) != NULL);					// Until Space is Available
		sim.setOrganism(new Lion(x, y, &sim, w, h), x, y);		// Put an Organism in that Space
	}
}

void splashScreen()
{
	// F0 = Notepad
	// 0A = Matrix
//	system("Color F0"); 
	
	string height = "\n\n\n\n\n\n\n";
	for (unsigned line = 0; line < h; line++) height += "\n\n";

	if (!debug) 
	{
		cout	<< "\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4"
				<< height << "Resize the window until you can see both lines on screen, then press ENTER.\n"
				<< "\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4";

		getline(cin, str); // Wait for User Response
	}
}

void runSimulation()
{
	sim = World();
	srand((unsigned)time(NULL));
	
	// Populate Board
	createAnt(100); createLion(5);

	string turnNumber = "";
	int extTurn = -1;

	// Loop Through Steps
	for (unsigned i = 0; i <= 10000; i++)
	{
		if (!debug) cout << sim << endl;

		// Get Count of Both Species
		int antCount = 0; int lionCount = 0;
		for (unsigned x = 0; x < w; x++) {
			for (unsigned y = 0; y < h; y++)
			{
				Organism* org = sim.getOrganism(x,y);
				if (dynamic_cast<Ant *>(org) != NULL) antCount++;		// If Organism is an Ant
				if (dynamic_cast<Lion *>(org) != NULL) lionCount++;		// If Organism is a Lion
			}
		}

		// Output Step Information

		if (debug) cout << endl;
		if (i == 0) cout << "  Initial Board" << endl;
		else cout << "  Turn: " << i << endl;

		cout << "\n  Remaining Ants: " << antCount << "  Lions: " << lionCount;
		if (i == 0) cout << "\n\n"; // For Initial Spacing

		if (antCount == 0 || lionCount == 0) {extTurn = i; break;}
		else if (i == 100 && !debug) {break;}

//		if (!debug) Sleep(500);
		system("cls"); sim.move();
	}

	if (extTurn != -1) cout << "\n  Extinction on Turn: " << extTurn;
	else cout << "\n  Survival Untill Turn 100!";
	getline(cin, str); runSimulation();
}

int main()
{
	splashScreen();
	runSimulation();
	return 0;
}