#include <iostream>

#include "Cell.h"

using namespace std;

Cell::Cell()
:state(0)
{
}

Cell::Cell(const Cell &other)
:state(other.state)
{
}

Cell::~Cell()
{
}

void Cell::born()
{
	state=1;
}

void Cell::die()
{
	state=3;
}

void Cell::update()
{
	if (state%2)
	{
		state++;

		state%=4;
	}
}

bool Cell::alive() const
{
	return 2==state || 3==state;
}

bool Cell::dead() const
{
	return 0==state || 1==state;;
}

void Cell::print() const
{
	if (this->alive())
	{
		cout << "XX";
	}
	else
	{
		cout << "  ";
	}
}

int Cell::getState() const
{
	return state;
}

void Cell::changeState(const int action)
{
	switch (action)
	{
		case 1:
			this->born();
			break;
		case 2: this->die();
			break;
	}
}
