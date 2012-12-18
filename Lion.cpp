#include <cstdlib>
#include <ctime>
#include "World.h"
#include "Ant.h"
#include "Lion.h"

using namespace std;

Lion::Lion() 
{
}

Lion::Lion(int x, int y, World *world, int width, int height) 
	:Organism(x, y, world, width, height )
{
	srand( (unsigned int)time(NULL) );
	eaten = false;
	symbol = '\x2';
}

Lion::~Lion() 
{
}

void Lion::eat(int coordX, int coordY)
{
	if(dynamic_cast<Ant *>(world->getOrganism(coordX, coordY)) != NULL) // if the space is occupied by an Ant
	{
			// move to the Ant's space and replace with the Lion
			newX = coordX;
			newY = coordY;

			world->setOrganism( this, newX, newY );
			world->setOrganism( NULL, x, y );

			x = newX;
			y = newY;

	}
}

void Lion::move()
{
	Organism* target[8];
	for (int i = 0; i < 8; i++)
		target[i] = NULL;

	// GET OBJECTS FOR ARRAY //

	if (y > 0)					target[0] = world -> getOrganism(x, y-1); // NORTH
	if (x < GRID_WIDTH - 1)		target[1] = world -> getOrganism(x+1, y); // EAST
	if (y < GRID_HEIGHT - 1)	target[2] = world -> getOrganism(x, y+1); // SOUTH
	if (x > 0)					target[3] = world -> getOrganism(x-1, y); // WEST

	if (y > 0 && x < GRID_WIDTH - 1)					target[4] = world -> getOrganism(x+1, y-1); // N-E
	if (y < GRID_HEIGHT - 1 && x < GRID_WIDTH - 1)		target[5] = world -> getOrganism(x+1, y+1); // S-E
	if (y < GRID_HEIGHT - 1 && x > 0)					target[6] = world -> getOrganism(x-1, y+1); // S-W
	if (y > 0 && x > 0)									target[7] = world -> getOrganism(x-1, y-1); // N-W

	bool antAvailable = false;
	for (unsigned i = 0; i < 8; i++) {
		if (target[i] != NULL && dynamic_cast <Ant*> (target[i]) != NULL) {antAvailable = true; break;}
	}
	
	int direction = 0;

	do {

		if (antAvailable) // There is an Ant, Randomly Move to one Adjacent
		{
			do {

				direction = rand() % 8;
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
					
					case 4: newX = x+1; newY = y-1; // N-E
						if (newX < 0 || newX > GRID_WIDTH - 1 || newY < 0 || newY > GRID_HEIGHT - 1) {newX = x; newY = y;} break;
					
					case 5: newX = x+1; newY = y+1; // S-E
						if (newX < 0 || newX > GRID_WIDTH - 1 || newY < 0 || newY > GRID_HEIGHT - 1) {newX = x; newY = y;} break;
					
					case 6: newX = x-1; newY = y+1; // S-W
						if (newX < 0 || newX > GRID_WIDTH - 1 || newY < 0 || newY > GRID_HEIGHT - 1) {newX = x; newY = y;} break;
					
					case 7: newX = x-1; newY = y-1; // N-W
						if (newX < 0 || newX > GRID_WIDTH - 1 || newY < 0 || newY > GRID_HEIGHT - 1) {newX = x; newY = y;} break;
				}
			}

			// There is an Ant, Keep Looking for it!
			while (dynamic_cast <Ant *> (world -> getOrganism(newX, newY)) == NULL);
			eaten = true;
		}

		else // There is no Ant, Move Anywhere Adjacent
		{
			direction = rand() % 4;
			switch(direction)
			{
				case 0: newX = x; newY = y-1; break; // NORTH
				case 1: newX = x+1; newY = y; break; // EAST
				case 2: newX = x; newY = y+1; break; // SOUTH
				case 3: newX = x-1; newY = y; break; // WEST
				default: newX = x; newY = y; break;
			}
		}
	}

	// Don't Accept the Movement if it goes over a Border
	while (newX < 0 || newX >= GRID_WIDTH || newY < 0 || newY >= GRID_HEIGHT);

	world -> setOrganism(this, newX, newY); // Move This to Target
	world -> setOrganism(NULL, x, y); // Delete Old Instance of This
	x = newX; y = newY; endMove(); // Set New Current Coords
}

void Lion::breed()
{
	// After 8 Turns, Attempt to Breed
	if(counter % 8 == 0 && counter != 0)
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
			spawn(newX, newY); counter = 0;
		}

		// Lions don't lose their Breed Counter
		endTurn();
	}
	/*
	// if 8 turns are up, attempt to breed
	if(counter % 8 == 0 && counter != 0)
	{
		// check availability of surrounding spaces for breeding
		if((world->getOrganism(x, y-1) == NULL) && (x >= 0) && (y-1 >=0) &&
			(x < GRID_WIDTH) && (y-1 < GRID_HEIGHT) ) // NORTH
		{
			// if the space is available, place new Lion
			spawn(x, y-1);
		}
		else if((world->getOrganism(x, y+1) == NULL) && (x >= 0) && (y+1 >=0) &&
			(x < GRID_WIDTH) && (y+1 < GRID_HEIGHT) ) // SOUTH
		{
			spawn(x, y+1);
		}
		else if((world->getOrganism(x+1, y) == NULL) && (x+1 >= 0) && (y >=0) &&
			(x+1 < GRID_WIDTH) && (y < GRID_HEIGHT)) // EAST
		{
			spawn(x+1, y);
		}
		else if((world->getOrganism(x-1, y) == NULL) && (x-1 >= 0) && (y >=0) && 
			(x-1 < GRID_WIDTH) && (y < GRID_HEIGHT) ) // WEST
		{
			spawn(x-1, y);
		}
		// if no available spaces, do not breed
	}*/
}

void Lion::starve()
{
	// if three turns have gone by
	if(counter % 3 == 0 && counter != 0)
	{
		// the Lion will starve if it hasn't eaten
		if(eaten == false)
		{
			world->setOrganism(NULL, x, y);
		}
		else
		{
			eaten = false;
		}
	}
	// last action for Lion of its turn
	done = true;
}


void Lion::spawn(int coordX, int coordY)
{
	// method to be called from breed() to instantiate new Lion
	Lion *offspring = new Lion(x, y, world, GRID_WIDTH, GRID_HEIGHT );
	offspring->setPosition( coordX, coordY );

	world->setOrganism(offspring, coordX, coordY );
}