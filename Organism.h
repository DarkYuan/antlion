#ifndef ORGANISM_H
#define ORGANISM_H

#include <iostream>

using namespace std;

class World;

class Organism
{
protected:
	int x;
	int y;
	int width;
	int height;
	int counter;
	bool moved;
	bool done;
	World *world;
	char symbol;

	enum { WEST, NORTH, EAST, SOUTH, NUM_DIRECTIONS };

public:
	Organism();
	Organism(int x, int y, World *world, int width, int height );
	virtual ~Organism();

	virtual void move();
	virtual void breed();
	virtual void spawn();

	void incCounter();
	void setPosition( int x, int y );
	void endTurn();
	bool isTurn();
	void endMove();
	bool hasMoved();

	virtual char getSymbol();
	bool isAnt();
	bool isLion();

	friend ostream& operator<<( ostream &output, Organism *organism );
};

#endif