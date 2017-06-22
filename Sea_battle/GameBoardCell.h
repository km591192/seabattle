#ifndef GAME_BOARD_CELL_H
#define GAME_BOARD_CELL_H
//CellState
#include "Enum.h"

class GameBoardCell 
{
public:
	GameBoardCell(int x = 0, int y = 0, CellState state = (CellState) EMPTY);
	void setX(int x);
	void setY(int y);
	void setState(CellState state);
	void setStatecomp(CellState state);
	const CellState getState();
	const CellState getStatecomp();
	const int getX();
	const int getY();
	const bool tryHit(int x, int y);
	void printField();
	const bool tryHitcomp(int x, int y);
	void printFieldcomp(); 
	void printFieldcompintheend();
private:
	int x_, y_;
	CellState state_;
	CellState statecomp_;
};
#endif


