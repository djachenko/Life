#ifndef Game_h
#define Game_h

#include "Field.h"

class Game
{
	private:
		Field table;
		std::map<int, actions> rules;
		std::string name;
	public:
		Game();
		Game(const Game & other);
		virtual ~Game();

		void read();
		void tick(int n=1);
		void dump() const;
		void print() const;
		void help() const;
};

#endif //Game_h
