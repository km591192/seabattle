#pragma once
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
	CellState getState();
	int getX();
	int getY();
	bool tryHit(int x, int y);
	void printField();
private:
	int x_, y_;
	CellState state_;
};



