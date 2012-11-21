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

		void read(char * name=NULL);
		void fread(char * name);//reading from file
		void sread();//reading from stdin
		void print() const;

		int countNeighbours(int x, int y);
};

#endif //Field_h
