#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>

#include "Game.h"

using namespace std;

Game::Game()
:field(3,3)
{
}

Game::Game(const Game & other)
:field(other.field), rules(other.rules), name(other.name)
{
}

Game::~Game()
{
}

void Game::read(const char * name)
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

	input.get();

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
					rules[birth!=action][c-'0']=action;
					cout << "c: " << c << ", action: " << rules[birth!=action][c-'0'] << endl;
				}
		}
	}

	map<int, actions>::iterator it;

	for (int i=0; i<=9; i++)
	{
		if (rules[false].find(i)==rules[false].end())
		{
			rules[false][i]=death;
		}

		if (rules[true].find(i)==rules[true].end())
		{
			rules[true][i]=death;
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
//		cout << "n: " << n << endl;

		for (int i=0; i<field.getSizeX(); i++)
		{
			for (int j=0; j<field.getSizeY(); j++)
			{
	//			cout << i << ' ' << j << endl;

				field[i][j].changeState( rules[ field[i][j].alive() ][ field.countNeighbours(i, j) ] );
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

void Game::dump(const string & name)
{
	ofstream output;

	output.open(name.c_str());

	output << "#Life 1.06" << endl;

	output << "#N " << name << endl;

	output << "#R B";

	for (int i=0; i<=9; i++)
	{
		if (rules[false][i]==birth)
		{
			output << i;
		}
	}

	output << "/S";

	for (int i=0; i<=9; i++)
	{
		if (rules[true][i]==survival)
		{
			output << i;
		}
	}

	output << endl;

	for (int i=0; i<field.getSizeX(); i++)
	{
		for (int j=0; j<field.getSizeY(); j++)
		{
			if (field[i][j].alive())
			{
				output << i << ' ' << j << endl;
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

void Game::help() const
{
	cout << "HELP:" << endl;

	cout << "1. For dumping game state into file <filename> enter \"dump <filename>\"" << endl;
	cout << "2. For counting N iterations enter \"tick <N>\" (by default N=1)" << endl;
	cout << "3. For help enter \"help\"" << endl;
	cout << "4. For finishing game enter \"exit\"" << endl;
}

void Game::init(int & argc, string * args)
{
	bool offline=false;
	int iterations=0;
	string output;
	string input;

	for (int i=1; i<argc; )
	{
		if (args[i].compare(0, 13, "--iterations="))
		{
			if (iterations)
			{
				throw duplicateIValue;
			}

			for (int j=13; j<args[i].length(); j++)
			{
				if ( isdigit( args[i][j] ) )
				{
					iterations=iterations*10+args[i][j]-'0';
				}
				else
				{
					throw wrongIValue;
				}
			}

			i++;

			offline=true;

			continue;
		}

		if ( args[i].compare("-i") )
		{
			if (iterations)
			{
				throw duplicateIValue;
			}

			i++;

			if (i==argc)
			{
				throw wrongIValue;
			}

			for (int j=0; j<args[i].length(); j++)
			{
				if ( isdigit( args[i][j] ) )
				{
					iterations=iterations*10+args[i][j]-'0';
				}
				else
				{
					throw wrongIValue;
				}
			}

			i++;

			offline=true;

			continue;
		}

		if ( args[i].compare(0, 9, "--output=") )
		{
			if ( !output.empty() )
			{
				throw duplicateOValue;
			}

			output=args[i].substr(9);

			i++;

			offline = true;

			continue;
		}

		if ( args[i].compare("-o") )
		{
			if ( !output.empty() )
			{
				throw duplicateOValue;
			}

			i++;

			if (i==argc)
			{
				throw wrongOValue;
			}

			output=args[i];

			i++;

			offline = true;

			continue;
		}

		if ( i==argc-1 )
		{
			input=args[i];
		}
		else
		{
			throw wrongParameter;
		}
	}

	this->read( input.c_str() );

	if (offline)
	{
		this->tick(iterations);

		this->dump(output);

		return;
	}

	this->print();

	while ( 1 )
	{
		string command;

		cin >> command;

		if ( command.compare("tick") || command.compare("t") )
		{
			char val[256];

			cin.getline(val, 256, '\n');//pot_error

			string value=val;

			if ( !value.empty() )
			{
				this->tick( atoi( value.c_str() ) );
			}
			else
			{
				this->tick();
			}

			this->print();

			continue;
		}

		if ( command.compare("dump") )
		{
			string value;

			cin >> value;

			this->dump(value);

			continue;
		}

		if ( command.compare("help") )
		{
			this->help();

			continue;
		}

		if ( command.compare("exit") )
		{
			return;
		}
	}
}
