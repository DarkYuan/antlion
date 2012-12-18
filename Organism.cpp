#include <iostream>
#include "World.h"
#include "Organism.h"
#include "Ant.h"
#include "Lion.h"

using namespace std;

Organism::Organism() : done(false)
{
}

Organism::Organism(int x, int y, World *world, int width, int height ) : done(false), moved(true)
{
	this->x = x;
	this->y = y;

	this->world = world;
	this->width = width;
	this->height = height;
	counter = 0;
}

Organism::~Organism()
{
}

void Organism::incCounter()
{
	counter++;
}

void Organism::setPosition( int x, int y ) 
{ 
	this->x = x; 
	this->y = y; 
}

void Organism::endTurn()
{
	done = false;
}

bool Organism::isTurn()
{
	return !done;
}

void Organism::endMove()
{
	moved = true;
}

bool Organism::hasMoved()
{
	return !moved;
}

ostream& operator<<( ostream &output, Organism *organism )
{
	if( dynamic_cast<Ant *>(organism) != NULL )
	{
		output << " " << ((Organism)*organism).getSymbol() << " ";
	}
	else if( dynamic_cast<Lion *>(organism) != NULL )
	{
		output << " " << ((Organism)*organism).getSymbol() << " ";
	}
	else
	{
		output << "   ";
	}

	return output;
}

void Organism::spawn(){}

void Organism::move(){}

void Organism::breed(){}

char Organism::getSymbol() {return this->symbol;}

bool Organism::isAnt() {return (dynamic_cast<Ant *>(this) != NULL)? true:false;}
bool Organism::isLion() {return (dynamic_cast<Lion *>(this) != NULL)? true:false;}