
#include "stdafx.h"
#include "GameBoard.h"
#include <iostream>
using namespace std;

GameBoard::GameBoard()
{
	generateBoard();
}


void GameBoard::setState(int x, int y, CellState state)
{
		cells_[y][x].setState(state);
}


bool GameBoard::isDeck(int x, int y)
{
		return cells_[y][x].getState() == DECK || cells_[y][x].getState() == HITDECK;
}


int GameBoard::getCount()
{
	return FIELD_SIZE * FIELD_SIZE;
}

int GameBoard::getSize()
{
		return FIELD_SIZE;
}

/*
void GameBoard::generateBoard()
{
	for (int i = 0; i < FIELD_SIZE; i++)	{
		for (int j = 0; j < FIELD_SIZE; j++) {
			cells_[i][j].setState((CellState)EMPTY);
		}
	}

	int idx = 0;
	ships_[idx++].createShip(*this, 4, 0, 0, true);
	ships_[idx++].createShip(*this, 3, 0, 2, false);
	ships_[idx++].createShip(*this, 3, 8, 1, false);
	ships_[idx++].createShip(*this, 2, 3, 9, true);
	ships_[idx++].createShip(*this, 2, 2, 6, true);
	ships_[idx++].createShip(*this, 2, 6, 5, true);
	ships_[idx++].createShip(*this, 1, 4, 2, true);
	ships_[idx++].createShip(*this, 1, 8, 8, true);
	ships_[idx++].createShip(*this, 1, 0, 8, true);
	ships_[idx++].createShip(*this, 1, 6, 0, true);
	
}

void GameBoard::printField()
{
	for (int i = 0; i < FIELD_SIZE; i++) {
		cout << "|";
		for (int j = 0; j < FIELD_SIZE; j++) {
			cells_[i][j].printField();
			cout << "|";
		}
		cout << endl;
	}
}

void GameBoard::shotShip(int x, int y)
{
	for (int i = 0; i < SHIPS_COUNT; i++) {
		if (ships_[i].tryHit(x, y))	{
			ships_[i].shotShip(*this, x, y);
			break;
		}
		else {
			cells_[y][x].setState((CellState) MISS);
		}
	}
}

bool GameBoard::allShipsDestroyed()
{
	for (int i = 0; i < SHIPS_COUNT; i++) {
		if (ships_[i].getState() != DESTROYED) {
			return false;
		}
	}
	return true;  
}

*/