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
	//cout << "Cell::print()" << endl;

	cout << this->getState();

	return;

	if (this->alive())
	{
		cout << "X";
	}
	else
	{
		cout << "O";
	}
}

int Cell::getState() const
{
	return state;
}

void Cell::changeState(const actions action)
{
	switch (action)
	{
		case birth:
			cout << "birth" << endl;

			this->born();
			break;
		case death: 
			cout << "death X_X" << endl;

			this->die();
			break;
	}
}
