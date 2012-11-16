#include "Cell.h"

Cell::Cell(int value)
:state(value)
{
}

Cell::Cell(Cell &other)
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
