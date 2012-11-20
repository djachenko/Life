#include <iostream>
#include <fstream>

#include "Field.h"

Field::Field(int x, int y)
:table(x, vector<Cell>(y) ), sizeX(x), sizeY(y)
{
}

Field::Field(const Field & other)
:table(other.table), sizeX(other.sizeX), sizeY(other.sizeY)
{
}

Field::~Field()
{
}

vector<Cell> & Field::operator[](int i)
{
	return table[i];
}

void Field::read(char * name)
{
	if (name)
	{
		this->fread(name);
	}
	else
	{
		this->sread();
	}
}

void Field::fread(char * name)
{
	ifstream input;

	input.open(name);

	int x;
	int y;

	for ( ; input.good(); )
	{
		input >> x >> y;

		(*this)[x][y].born();
	}
}

void Field::sread()
{
	int x;
	int y;

	for ( ; cin.good(); )
	{
		cin >> x >> y;

		(*this)[x][y].born();
	}
}

void Field::print() const
{
	for(int i=0; i<sizeX; i++)
	{
		for (int j=0; j<sizeY; j++)
		{
			field[i][j].print();
		}

		cout >> endl;
	}
}
