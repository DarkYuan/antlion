#include <iostream>
#include "World.h"
#include "Organism.h"
#include "Ant.h"
#include "Lion.h"

using namespace std;

World::World()
{	
	for( int i=0; i<GRID_WIDTH; i++ )
	{
		for( int j=0; j<GRID_HEIGHT; j++ )
		{
			grid[i][j] = NULL;
		}
	}
}

World::~World() 
{
	 //free up allocated memory
	for( int i=0; i<GRID_WIDTH; i++ )
	{
		for( int j=0; j<GRID_HEIGHT; j++ )
		{
			if( grid[i][j] != NULL )
			{
				delete grid[i][j];
			}
		}
	}
}

Organism *World::getOrganism( int x, int y )
{
//	if (x <= 0 || x > GRID_WIDTH || y <= 0 || y > GRID_HEIGHT) return NULL;
	return grid[x][y];
}

void World::setOrganism( Organism *org, int x, int y )
{
	grid[x][y] = org;
}

int World::getWidth() {return GRID_WIDTH;}
int World::getHeight() {return GRID_HEIGHT;}

void World::move()
{
	// object method call priority:

	// 1 - Move all Lions
	for( int i=0; i<GRID_WIDTH; i++ )
	{
		for( int j=0; j<GRID_HEIGHT; j++ )
		{
			// verify organism is a Lion and that the Lion
			// has not already moved once, before moving
			if( (dynamic_cast<Lion *>(grid[i][j]) != NULL) &&
			    (grid[i][j]->isTurn()) && !(grid[i][j]->hasMoved()) )
			{
				grid[i][j]->move();
			}
		}
	}

	// 2 - Move all ants
	for( int i=0; i<GRID_WIDTH; i++ )
	{
		for( int j=0; j<GRID_HEIGHT; j++ )
		{
			// verify organism is an Ant and that the Ant
			// has not already moved once, before moving
			if( (dynamic_cast<Ant *>(grid[i][j]) != NULL) &&
			    (grid[i][j]->isTurn()) && !(grid[i][j]->hasMoved()) )
			{
				grid[i][j]->move();
			}
		}
	}

	// 3 - Breed all eligible Lions
	for( int i=0; i<GRID_WIDTH; i++ )
	{
		for( int j=0; j<GRID_HEIGHT; j++ )
		{
			// verify organism is a Lion and that it's the Lion's
			// turn before attempting to breed
			if( (dynamic_cast<Lion *>(grid[i][j]) != NULL) &&
			    (grid[i][j]->isTurn()) )
			{
				grid[i][j]->breed();
			}
		}
	}

	// 4 - Breed all eligible ants
	for( int i=0; i<GRID_WIDTH; i++ )
	{
		for( int j=0; j<GRID_HEIGHT; j++ )
		{
			// verify organism is an Ant and that it's the Ant's
			// turn before attempting to breed
			if( (dynamic_cast<Ant *>(grid[i][j]) != NULL) &&
			    (grid[i][j]->isTurn()) )
			{
				grid[i][j]->breed();
			}
		}
	}

	// 6 - Starve all eligible Lions
	for( int i=0; i<GRID_WIDTH; i++ )
	{
		for( int j=0; j<GRID_HEIGHT; j++ )
		{
			// verify organism is a Lion and that it's the Lion's
			// turn before attempting to starve
			if( (dynamic_cast<Lion *>(grid[i][j]) != NULL) &&
			    (grid[i][j]->isTurn()) )
			{
				(dynamic_cast<Lion *>(grid[i][j])->starve());
			}
		}
	}

	// 7 - End all the organism's turns
	for( int i=0; i<GRID_WIDTH; i++ )
	{
		for( int j=0; j<GRID_HEIGHT; j++ )
		{
			// verify presence of organism
			if( grid[i][j] != NULL )
			{
				grid[i][j]->endTurn();
			}
		}
	}

	// 8 - All remaining organisms have "survived" this step. Increment each organism's counter by one.
	for( int i=0; i<GRID_WIDTH; i++ )
	{
		for( int j=0; j<GRID_HEIGHT; j++ )
		{
			// verify presence of organism
			if( grid[i][j] != NULL )
			{
				grid[i][j]->incCounter();
			}
		}
	}

}

ostream& operator<<( ostream &output, World &world ) // Display Grid
{
	// Top Border
	output << "\xC9\xCD"; for (unsigned line = 0; line < GRID_WIDTH; line++) output << "\xCD\xCD\xCD"; output << "\xCD\xBB\n";
	
	// Filler First-Row
	output << "\xBA "; for (unsigned line = 0; line < GRID_WIDTH; line++) output << "   "; output << " \xBA\n";

	for(unsigned i = 0; i < GRID_HEIGHT; i++)
	{
		// Data Row
		output << "\xBA "; for(unsigned j = 0; j < GRID_WIDTH; j++) output << world.grid[i][j]; output << " \xBA\n";

		// Filler After-Row
		output << "\xBA "; for (unsigned line = 0; line < GRID_WIDTH; line++) output << "   "; output << " \xBA\n";
	}

	// Bottom Border
	output << "\xC8\xCD"; for (unsigned line = 0; line < GRID_WIDTH; line++) output << "\xCD\xCD\xCD"; output << "\xCD\xBC\n";

	return output;
}