#ifndef LION_H
#define LION_H

#include "Organism.h"

class Lion : public Organism
{
protected:
	int newX, 
		newY;
	bool eaten;

public:
	Lion();
	Lion(int x, int y, World *world, int width, int height);
	virtual ~Lion();

	void eat(int coordX, int coordY);
	void move();
	void breed();
	void starve();
	void spawn(int coordX, int coordY);
};

#endif