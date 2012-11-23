#ifndef Game_h
#define Game_h


#include <map>

#include "Field.h"

class Game
{
	private:
		Field field;
		std::map<bool, std::map<int, actions> > rules;
		std::string name;

		void realRead(istream & input);
	public:
		Game();
		Game(const Game & other);
		virtual ~Game();

		void read(char * name);
		void tick(int n=1);
		void dump(const string name) const;
		void print() const;
		void help() const;
};

#endif //Game_h
