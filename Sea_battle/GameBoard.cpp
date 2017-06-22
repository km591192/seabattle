
#include "stdafx.h"
#include "GameBoard.h"
#include <iostream>
using namespace std;

GameBoard::GameBoard()
{
	generateBoard();
	generateBoardcomp();
}
void GameBoard::setState(int x, int y, CellState state)
{
		cells_[y][x].setState(state);
}


const bool GameBoard::isDeck(int x, int y)
{
		return cells_[y][x].getState() == DECK || cells_[y][x].getState() == HITDECK;
}

void GameBoard::setStatecomp(int x, int y, CellState state)
{
	cellscomp_[y][x].setStatecomp(state);
}


const bool GameBoard::isDeckcomp(int x, int y)
{
	return cellscomp_[y][x].getStatecomp() == DECK || cellscomp_[y][x].getStatecomp() == HITDECK;
}

const int GameBoard::getCount()
{
	return FIELD_SIZE * FIELD_SIZE;
}

const int GameBoard::getSize()
{
		return FIELD_SIZE;
}
