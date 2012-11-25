#include <string>

#include "Game.h"

using namespace std;

int main(int argc, char ** args)
{
	Game life(3, 3);

	life.init(argc, args);

	return 0;
}
