#include "Game.h"

int main()
{
	Game life;

	life.read("testGame.txt");

	life.print();

	for (int i=0; i<5; i++)
	{
		life.tick();

		life.print();
	}

	return 0;
}
