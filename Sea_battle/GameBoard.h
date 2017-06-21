
#include "GameBoardCell.h"
#include "Ship.h"
#include "Enum.h"

class GameBoard 
{
public:
	GameBoard();
	void setState(int x, int y, CellState state);
	bool isDeck(int x, int y);
	void printField();
	int getCount();
	int getSize();
	void shotShip(int x, int y);
	bool allShipsDestroyed();

private:
	static const int FIELD_SIZE = 10;
	static const int DECK_SHIP_COUNT_4 = 1;
	static const int DECK_SHIP_COUNT_3 = 2;
	static const int DECK_SHIP_COUNT_2 = 3;
	static const int DECK_SHIP_COUNT_1 = 4;
	static const int SHIPS_COUNT = DECK_SHIP_COUNT_4 + DECK_SHIP_COUNT_3 + DECK_SHIP_COUNT_2 + DECK_SHIP_COUNT_1;
	GameBoardCell cells_[FIELD_SIZE][FIELD_SIZE];
	GameBoardCell cellscomp_[FIELD_SIZE][FIELD_SIZE];
	Ship ships_ [SHIPS_COUNT];
	void generateBoard();
};