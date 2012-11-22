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

void Field::read(const char * name)
{
	//cout << "read" << endl;

	if (name)
	{
		ifstream input;

		input.open(name);

		this->fread(input);
	}
	else
	{
		this->fread(cin);
	}

	for (int i=0; i<sizeX; i++)
	{
		for (int j=0; j<sizeY; j++)
		{
			(*this)[i][j].update();
		}
	}
}

void Field::fread(istream & input)
{
	int x;
	int y;

	for ( ; input.good(); )
	{
		input >> x >> y;

		if (-1==x && -1==y)
		{
			return;
		}

//		cout << "x: " << x << endl << "y: " << y << endl;

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
//				cout << "++ " << ( x + i + sizeX ) % sizeX << ' ' << ( y + j + sizeY ) % sizeY << endl;
//				cout << x+i << ' ' << y+j << '|' << x+i+sizeX << ' ' << y+j+sizeY << endl;
				result++;
			}
		}
	}

	cout << "count " << x << ' ' << y << ' ' << result << endl;

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
