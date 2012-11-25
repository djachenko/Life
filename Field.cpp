#include <iostream>
#include <fstream>
#include <queue>

#include "Field.h"

Field::Field()
{
}

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

void Field::read(const char * name)
{
	if (name)
	{
		ifstream input;

		input.open(name);

		this->read(input);
	}
	else
	{
		cout << "Enter cell coordinates:" << endl;

		this->read(cin);
	}
}

void Field::read(istream & input)
{
	int x;
	int y;

//	queue<int> queueX;
//	queue<int> queueY;
//
	for ( ; input.good(); )
	{
		input >> x >> y;

		if (-1==x && -1==y)
		{
			return;
		}

		(*this)[x][y].born();
		(*this)[x][y].update();

//		queueX.push(x);
//		queueY.push(y);
	}

//	for ( ; !queueX.empty(); )
//	{
//		(*this)[ queueX.front() ][ queueY.front() ].born();
//		(*this)[ queueX.front() ][ queueY.front() ].update();
//
//		queueX.pop();
//		queueY.pop();
//	}
}

void Field::print() const
{
	for(int i=0; i<sizeX; i++)
	{
		for (int j=0; j<sizeY; j++)
		{
			(*this)[i][j].print();
		}

		cout << endl;
	}
}

int Field::getSizeX() const
{
	return sizeX;
}

int Field::getSizeY() const
{
	return sizeY;
}

int Field::countNeighbours(int x, int y)
{
	int result=0;

	for (int i=-1; i<=1; i++)
	{
		for (int j=-1; j<=1; j++)
		{
			if (0==i && 0==j)
			{
				continue;
			}

			if ( (*this)[ ( x + i + sizeX ) % sizeX ][ ( y + j + sizeY ) % sizeY ].alive())
			{
				result++;
			}
		}
	}

	return result;
}

void Field::resize(const int newX, const int newY)
{
	table.resize(newX);

	for (int i=0; i<newX; i++)
	{
		table[i].resize(newY);
	}

	sizeX=newX;
	sizeY=newY;
}

void Field::update()
{
	for (int i=0; i < this->getSizeX(); i++)
	{
		for (int j=0; j < this->getSizeY(); j++)
		{
			(*this)[i][j].update();
		}
	}
}
