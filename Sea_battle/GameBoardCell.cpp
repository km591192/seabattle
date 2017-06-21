
#include "stdafx.h"
#include "GameBoardCell.h"
#include <iostream>
#include <Windows.h>

GameBoardCell::GameBoardCell(int x, int y, CellState state) /*: x_(x), y_(y), state_(state)*/
{
		x_ = x;
		y_ = y;
		state_ = state;
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

CellState GameBoardCell::getState()
{
		return state_;
}

int GameBoardCell::getX()
{
		return x_;
}

int GameBoardCell::getY()
{
		return y_;
}

bool GameBoardCell::tryHit(int x, int y)
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




