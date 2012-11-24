#include <string>

#include "Game.h"

using namespace std;

int main(int argc, string * args)
{
	Game life;

	life.init(argc, args);

	return 0;

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
