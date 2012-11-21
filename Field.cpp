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

const vector<Cell> & Field::operator[](int i) const
{
	return table[i];
}

void Field::read(char * name)
{
	//cout << "read" << endl;

	if (name)
	{
		this->fread(name);
	}
	else
	{
		this->sread();
	}

	for (int i=0; i<sizeX; i++)
	{
		for (int j=0; j<sizeY; j++)
		{
			(*this)[i][j].update();
		}
	}
}

void Field::fread(char * name)
{
	//cout << "fread" << endl;

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
	//cout << "sread" << endl;

	int x;
	int y;

	for ( ; ; )
	{
		cin >> x >> y;

		if (x==-1 && y==-1)
		{
			return;
		}

		(*this)[x][y].born();
	}
}

void Field::print() const
{
	//cout << "Field::print()" << endl;

	for(int i=0; i<sizeX; i++)
	{
		for (int j=0; j<sizeY; j++)
		{
			(*this)[i][j].print();
		}

		cout << endl;
	}
}
