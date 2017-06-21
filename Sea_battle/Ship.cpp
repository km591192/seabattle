
#include "stdafx.h"
#include "Ship.h"

Ship::Ship() 
{
		cells_ = 0;
		size_ = 0;
}

/*
void Ship::createShip(GameBoard& gameBoard, int size, int x, int y, bool horizontal)
{
	size_ = size;
	cells_ = new GameBoardCell[size];
	for (int i = 0; i < size; i++)
	{
		if (horizontal) {
			cells_[i].setX(x + i);
			cells_[i].setY(y);
			gameBoard.setState(x + i, y, (CellState) DECK);
		}
		else {
			cells_[i].setX(x);
			cells_[i].setY(y + i);
			gameBoard.setState(x, y + i, (CellState) DECK);
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
			state_ = (ShipState) SAFE;
		}
		else if (hitCount < size_) {
			state_ = (ShipState) SHIPHIT;
		}
		else {
			state_ = (ShipState) DESTROYED;
		}
	}
	return state_;
}

void Ship::shotShip(GameBoard& gameBoard, int x, int y)
{
	for (int i = 0; i < size_; i++) {
		if (cells_[i].tryHit(x, y)) {
			cells_[i].setState((CellState) HITDECK);
			gameBoard.setState(x, y, (CellState) HITDECK);
			break;
		}
		if (getState() == DESTROYED) {
			for (int i = 0; i < size_; i++)
			{
				int localX = cells_[i].getX();
				int localY = cells_[i].getY();

				if (localX - 1 >= 0 && localY - 1 >= 0 && !gameBoard.isDeck(localX - 1, localY - 1)){
					gameBoard.setState(localX - 1, localY - 1, (CellState) MISS);
				}
				if (localX - 1 >= 0 && !gameBoard.isDeck(localX - 1, localY)){
					gameBoard.setState(localX - 1, localY, (CellState) MISS);
				}
				if (localX - 1 >= 0 && localY + 1 < gameBoard.getSize() && !gameBoard.isDeck(localX - 1, localY + 1)){
					gameBoard.setState(localX - 1, localY + 1, (CellState) MISS);
				}
				if (localY - 1 >= 0 && !gameBoard.isDeck(localX, localY - 1)){
					gameBoard.setState(localX, localY - 1, (CellState) MISS);
				}
				if (localY + 1 < gameBoard.getSize() && !gameBoard.isDeck(localX, localY + 1)){
					gameBoard.setState(localX, localY + 1, (CellState) MISS);
				}
				if (localX + 1 < gameBoard.getSize() && localY - 1 >= 0 && !gameBoard.isDeck(localX + 1, localY - 1)){
					gameBoard.setState(localX + 1, localY - 1, (CellState) MISS);
				}
				if (localX + 1 < gameBoard.getSize() && !gameBoard.isDeck(localX + 1, localY)){
					gameBoard.setState(localX + 1, localY, (CellState) MISS);
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
*/