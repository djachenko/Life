#ifndef Field_h
#define Field_h

#include <vector>
#include <string>

#include "Cell.h"

using namespace std;

class Field
{
	private:
		vector< vector< Cell > > table;
		int sizeX;
		int sizeY;
	public:
		Field(int x=0, int y=0);
		Field(const Field & other);
		virtual ~Field();

		vector<Cell> & operator[](int i);
		const vector<Cell> & operator[](int i) const;

		void read(const char * name=NULL);
		void fread(istream & input);
		void print() const;

		int countNeighbours(int x, int y);

		void resize(const int newY, const int newY);
};

#endif //Field_h
