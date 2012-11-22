#include <iostream>
#include <fstream>

#include "Game.h"

using namespace std;

Game::Game()
:field(2,2)
{
}

Game::Game(const Game & other)
:field(other.field), rules(other.rules), name(other.name)
{
}

Game::~Game()
{
}

void Game::read(char * name)
{
	if (name)
	{
		ifstream input;

		input.open(name);

		this->realRead(input);
	}
	else
	{
		this->realRead(cin);
	}
}

void Game::realRead(istream & input)
{
	string str;

	getline(input, str);//descriptor
	
	cout << "str: " << str << endl;

//NAME
	
	input >> str;//#N

	getline(input,name);

	cout << "name: " << name << endl;

	input >> str;//#R

//RULES

	char c;

	cout << "birth: " << birth << endl;
	cout << "survival: " << survival << endl;
	cout << "death: " << death << endl;

	for ( ; c!='\n'; )
	{
		c=input.get();

		actions action;

		switch (c)
		{
			case 'B':
				action=birth;
				
				break;
			case 'S':
				action=survival;

				break;
			default:
				if (c>='0' && c<='9')
				{
					rules[c-'0']=action;
					cout << "c: " << c << ", action: " << rules[c-'0'] << endl;
				}
		}
	}

	map<int, actions>::iterator it;

	for (int i=0; i<=9; i++)
	{
		if (rules.find(i)==rules.end())
		{
			rules[i]=death;
		}
	}

//FIELD

	field.fread(input);

	for (int i=0; i<field.getSizeX(); i++)
	{
		for (int j=0; j<field.getSizeY(); j++)
		{
			field[i][j].update();
		}
	}
}

void Game::tick(int n)
{
	for ( ; n; n--)
	{
		cout << "n: " << n << endl;

		for (int i=0; i<field.getSizeX(); i++)
		{
			for (int j=0; j<field.getSizeY(); j++)
			{
				cout << i << ' ' << j << endl;

				field[i][j].changeState( rules[ field.countNeighbours(i, j) ] );
			}
		}

		for (int i=0; i<field.getSizeX(); i++)
		{
			for (int j=0; j<field.getSizeY(); j++)
			{
				field[i][j].update();
			}
		}

	}
}

void Game::print() const
{
	cout << name << endl;

	field.print();

	cout << endl << endl;
}
