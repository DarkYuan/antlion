#ifndef ANT_H
#define ANT_H

#include "Organism.h"

class Ant : public Organism
{
public:
	Ant(); 
	Ant(int x, int y, World *world, int width, int height );
	virtual ~Ant();

	void move();
	void breed();
	void spawn(int coordX, int coordY);
};

#endif