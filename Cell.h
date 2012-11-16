#ifndef Cell_h
#define Cell_h

class Cell
{
	private:
		int state;
	public:
		Cell(int value = 0);
		Cell(Cell & other);
		~Cell();

		void born();
		void die();
		void update();

		int getState() const;
		void changeState(const int action);
};

#endif //Cell_h
