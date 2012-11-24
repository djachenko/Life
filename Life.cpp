#include <string>

#include "Game.h"

using namespace std;

int main(int argc, string * args)
{
	string base[]={"-i", "--iterations=", "-o", "--output="};

	for(int i=1; i<argc; i++)
	{
		for (int j=0; j<4; j++)
		{
			if (base[j].compare(args[i]))
			{

			}
		}
	}

	Game life;

	life.read("testGame.txt");

	life.print();

	for (int i=0; i<5; i++)
	{
		life.tick();

		life.print();
	}

	life.tick();

	life.dump("dump.txt");

	life.help();

	return 0;
}
