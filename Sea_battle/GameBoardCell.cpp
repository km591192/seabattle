
#include "stdafx.h"
#include "GameBoardCell.h"
#include <iostream>
#include <Windows.h>

GameBoardCell::GameBoardCell(int x, int y, CellState state) : x_(x), y_(y), state_(state)
{
		/*x_ = x;
		y_ = y;
		state_ = state;*/
}

void GameBoardCell::setX(int x)
{
		x_ = x;
}

void GameBoardCell::setY(int y)
{
		y_ = y;
}

void GameBoardCell::setState(CellState state)
{
		state_ = state;
}

const CellState GameBoardCell::getState()
{
		return state_;
}

const int GameBoardCell::getX()
{
		return x_;
}

const int GameBoardCell::getY()
{
		return y_;
}

const bool GameBoardCell::tryHit(int x, int y)
{
		return x == x_ && y == y_ && state_ != HITDECK;
}

void GameBoardCell::printField()
{
	if (state_ == EMPTY)
	{
		std::cout << ' ';
	}
	
	else if (state_ == HITDECK)
	{
		std::cout << 'x';
	}
	else if (state_ == DECK)
	{
		std::cout << 'd';
	}
	else
	{
		std::cout << '*';
	}
}

void GameBoardCell::setStatecomp(CellState state)
{
	statecomp_ = state;
}

const CellState GameBoardCell::getStatecomp()
{
	return statecomp_;
}
const bool GameBoardCell::tryHitcomp(int x, int y)
{
	return x == x_ && y == y_ && statecomp_ != HITDECK;
}

void GameBoardCell::printFieldcomp()
{
	if (statecomp_ == EMPTY)
	{
		std::cout << ' ';
	}
	else if (statecomp_ == KILL)
	{
		std::cout << 'k';
	}
	else if (statecomp_ == HITDECK)
	{
		std::cout << 'x';
	}
	else if (statecomp_ == DECK)
	{
		std::cout << ' '; //' ' !!!
	}
	else
	{
		std::cout << '*';
	}
}
void GameBoardCell::printFieldcompintheend()
{
	if (statecomp_ == EMPTY)
	{
		std::cout << ' ';
	}
	else if (statecomp_ == KILL)
	{
		std::cout << 'k';
	}
	else if (statecomp_ == HITDECK)
	{
		std::cout << 'x';
	}
	else if (statecomp_ == DECK)
	{
		std::cout << 'f'; 
	}
	else
	{
		std::cout << '*';
	}
}




