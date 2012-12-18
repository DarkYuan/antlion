#include <cstdlib>
#include <ctime>
#include "World.h"
#include "Ant.h"

using namespace std;

Ant::Ant()
{
}

Ant::Ant(int x, int y, World *world, int width, int height )
	: Organism(x, y, world, width, height )
{
	srand( (unsigned int)time(NULL) );
	symbol = 'o';
}

Ant::~Ant()
{
}

void Ant::move()
{
	int newX = x; int newY = y;

	int direction = rand() % 4;
	switch(direction)
	{
		case 0: newX = x; newY = y-1; // NORTH
			if (newX < 0 || newX > GRID_WIDTH - 1 || newY < 0 || newY > GRID_HEIGHT - 1) {newX = x; newY = y;} break;

		case 1: newX = x+1; newY = y; // EAST
			if (newX < 0 || newX > GRID_WIDTH - 1 || newY < 0 || newY > GRID_HEIGHT - 1) {newX = x; newY = y;} break;

		case 2: newX = x; newY = y+1; // SOUTH
			if (newX < 0 || newX > GRID_WIDTH - 1 || newY < 0 || newY > GRID_HEIGHT - 1) {newX = x; newY = y;} break;

		case 3: newX = x-1; newY = y; // WEST
			if (newX < 0 || newX > GRID_WIDTH - 1 || newY < 0 || newY > GRID_HEIGHT - 1) {newX = x; newY = y;} break;
	}

	// Move Ant to New Location
	if( world->getOrganism( newX, newY ) == NULL )
	{
		world->setOrganism( this, newX, newY );
		world->setOrganism( NULL, x, y );
		x = newX; y = newY; endMove();
	}
}

void Ant::breed()
{
	// After 3 Turns, Attempt to Breed
	if(counter % 3 && counter != 0)
	{
		bool spaceAvailable = false;

		// GET ORGANISMS FOR CHECKING //

		if((world -> getOrganism(x, y-1) == NULL) && // NORTH
			(x >= 0) && (y-1 >= 0) && (x < GRID_WIDTH) && (y-1 < GRID_HEIGHT)) spaceAvailable = true;

		if((world -> getOrganism(x-1, y) == NULL) && // EAST
			(x-1 >= 0) && (y >= 0) && (x-1 < GRID_WIDTH) && (y < GRID_HEIGHT)) spaceAvailable = true;

		if((world -> getOrganism(x, y+1) == NULL) && // SOUTH
			(x >= 0) && (y+1 >= 0) && (x < GRID_WIDTH) && (y+1 < GRID_HEIGHT)) spaceAvailable = true;

		if((world -> getOrganism(x+1, y) == NULL) && // WEST
			(x+1 >= 0) && (y >= 0) && (x+1 < GRID_WIDTH) && (y < GRID_HEIGHT)) spaceAvailable = true;

		if (spaceAvailable) {

			int newX = x; int newY = y;

			do {
				
				int direction = rand() % 4;
				switch(direction)
				{
					case 0: newX = x; newY = y-1; // NORTH
						if (newX < 0 || newX > GRID_WIDTH - 1 || newY < 0 || newY > GRID_HEIGHT - 1) {newX = x; newY = y;} break;

					case 1: newX = x+1; newY = y; // EAST
						if (newX < 0 || newX > GRID_WIDTH - 1 || newY < 0 || newY > GRID_HEIGHT - 1) {newX = x; newY = y;} break;

					case 2: newX = x; newY = y+1; // SOUTH
						if (newX < 0 || newX > GRID_WIDTH - 1 || newY < 0 || newY > GRID_HEIGHT - 1) {newX = x; newY = y;} break;

					case 3: newX = x-1; newY = y; // WEST
						if (newX < 0 || newX > GRID_WIDTH - 1 || newY < 0 || newY > GRID_HEIGHT - 1) {newX = x; newY = y;} break;
				}
			}

			// There is an Space Available, Keep Looking for it!
			while (world -> getOrganism(newX, newY) != NULL);
			spawn(newX, newY);
		}

		// Either way, Ants lose their Breed Counter
		counter = 0; endTurn();
	}
}

void Ant::spawn(int coordX, int coordY)
{
	Ant *offspring = new Ant(x, y, world, GRID_WIDTH, GRID_HEIGHT );
	offspring->setPosition( coordX, coordY );

	world->setOrganism(offspring, coordX, coordY );
}