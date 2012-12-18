#ifndef WORLD_H
#define WORLD_H

#include <iostream>

using namespace std;

class Organism;

const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;

class World
{
protected:
	Organism *grid[GRID_WIDTH][GRID_HEIGHT];

public:
	World();
	virtual ~World();

	Organism *getOrganism( int x, int y );
	void setOrganism( Organism *organism, int x, int y );

	int getWidth();
	int getHeight();

	void move();

	friend ostream& operator<<( ostream &output, World &world );

};

#endif