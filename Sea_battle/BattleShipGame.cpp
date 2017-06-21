
#include "stdafx.h"
#include "BattleShipGame.h"
#include "GameBoard.h"
#include "Enum.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


GameBoard gameBoard;
BattleShipGame::BattleShipGame(){}
void BattleShipGame::startGame()
{
	gameBoard.printField(); 
	do {
		cout << "Enter x coord: " << endl;
		int x;
		cin >> x;
		cout << "Enter y coord: " << endl;
		int y;
		cin >> y;
		gameBoard.shotShip(x, y);
		gameBoard.printField();
	} while (!gameBoard.allShipsDestroyed());
}


void Ship::createShip(GameBoard& gameBoard, int size, int x, int y, bool horizontal)
{
	size_ = size;
	cells_ = new GameBoardCell[size];
	for (int i = 0; i < size; i++)
	{
		if (horizontal) {
			cells_[i].setX(x + i);
			cells_[i].setY(y);
			gameBoard.setState(x + i, y, (CellState)DECK);
		}
		else {
			cells_[i].setX(x);
			cells_[i].setY(y + i);
			gameBoard.setState(x, y + i, (CellState)DECK);
		}
	}
}

Ship::~Ship()
{
if (size_)
delete cells_;
}

ShipState Ship::getState()
{
	int hitCount = 0;
	for (int i = 0; i < size_; i++) {
		if (cells_[i].getState() == HITDECK){
			hitCount++;
		}
		if (hitCount == 0) {
			state_ = (ShipState)SAFE;
		}
		else if (hitCount < size_) {
			state_ = (ShipState)SHIPHIT;
		}
		else {
			state_ = (ShipState)DESTROYED;
		}
	}
	return state_;
}

void Ship::shotShip(GameBoard & gameBoard, int x, int y)
{
	for (int i = 0; i < size_; i++) {
		if (cells_[i].tryHit(x, y)) {
			cells_[i].setState((CellState)HITDECK);
			gameBoard.setState(x, y, (CellState)HITDECK);
			break;
		}
		if (getState() == DESTROYED) {
			for (int i = 0; i < size_; i++)
			{
				int localX = cells_[i].getX();
				int localY = cells_[i].getY();

				if (localX - 1 >= 0 && localY - 1 >= 0 && !gameBoard.isDeck(localX - 1, localY - 1)){
					gameBoard.setState(localX - 1, localY - 1, (CellState)MISS);
				}
				if (localX - 1 >= 0 && !gameBoard.isDeck(localX - 1, localY)){
					gameBoard.setState(localX - 1, localY, (CellState)MISS);
				}
				if (localX - 1 >= 0 && localY + 1 < gameBoard.getSize() && !gameBoard.isDeck(localX - 1, localY + 1)){
					gameBoard.setState(localX - 1, localY + 1, (CellState)MISS);
				}
				if (localY - 1 >= 0 && !gameBoard.isDeck(localX, localY - 1)){
					gameBoard.setState(localX, localY - 1, (CellState)MISS);
				}
				if (localY + 1 < gameBoard.getSize() && !gameBoard.isDeck(localX, localY + 1)){
					gameBoard.setState(localX, localY + 1, (CellState)MISS);
				}
				if (localX + 1 < gameBoard.getSize() && localY - 1 >= 0 && !gameBoard.isDeck(localX + 1, localY - 1)){
					gameBoard.setState(localX + 1, localY - 1, (CellState)MISS);
				}
				if (localX + 1 < gameBoard.getSize() && !gameBoard.isDeck(localX + 1, localY)){
					gameBoard.setState(localX + 1, localY, (CellState)MISS);
				}
				if (localX + 1 < gameBoard.getSize() && localY + 1 < gameBoard.getSize() && !gameBoard.isDeck(localX + 1, localY + 1)){
					gameBoard.setState(localX + 1, cells_[i].getY() + 1, (CellState)MISS);
				}
			}
		}
	}
}

bool Ship::tryHit(int x, int y)
{
	for (int i = 0; i < size_; i++) {
		if (cells_[i].tryHit(x, y)) {
			return true;
		}
	}
	return false;
}


void GameBoard::generateBoard()
{
	for (int i = 0; i < FIELD_SIZE; i++)	{
		for (int j = 0; j < FIELD_SIZE; j++) {
			cells_[i][j].setState((CellState)EMPTY);
		}
	}
	/*
	int count = 0;
	int x, y, size, position;
	bool isPosition;
	while (count != 9)
	{
		cout << "Enter ship length" << endl;
		cin >> size;
		cout << "Enter ship x coord" << endl;
		cin >> x;
		cout << "Enter ship y coord" << endl;
		cin >> y;
		cout << "Enter 0 or 1 for position vertical or horizontal" << endl;
		cin >> position;

		(position == 0) ? ships_[count++].createShip(*this, size, x, y, false) : ships_[count++].createShip(*this, size, x, y, true);
	};
	*/
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
	for (int i = 0; i <  FIELD_SIZE; i++) {
		cout << "|";
		for (int j = 0; j <  FIELD_SIZE; j++) {
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
			cells_[y][x].setState((CellState)MISS);
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
