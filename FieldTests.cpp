#include "Field.h"

int main()
{
	Field field(2,2);

	field.read("field.txt");

	field.print();

	return 0;
}
