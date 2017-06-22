
#include "stdafx.h"
#include "BattleShipGame.h"
#include "GameBoard.h"
#include "Enum.h"
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <ctime>

using namespace std;


unsigned int endtime = 0, starttime = 0, endpausetime = 0, startpausetime = 0;
double clocktime = 0.0;
int sizeStruct = 0;
GameBoard gameBoard;
int globalFlag = 0;
CoordXYcomp *pointcomp = new CoordXYcomp[gameBoard.getCount()];
CoordXY *point = new CoordXY[gameBoard.getCount()];
BattleShipGame::BattleShipGame(std::ofstream* log) : log_(log) {}
void BattleShipGame::mode(int btnCode)
{
	if (btnCode == 71 || btnCode == 103) //G g
	{
		starttime = clock();
		cout << "Start;" << std::endl;	startGame(); 
	}
	if (btnCode == 83 || btnCode == 115) //S s
	{
		cout << "Statistic;" << std::endl; 
		endtime = clock();  
		clocktime = (endtime - starttime) / 60000.0;
		*log_ << "Time " << clocktime;
		*log_ << endl;
		statisticGame();
	}
	else if (btnCode == 80 || btnCode == 112)//P p
	{
		startpausetime = clock();
		cout << "Pause;" << std::endl; 
		if (_getch()) {
			endpausetime = clock();
			cout << "Wait time " << (endpausetime - startpausetime) / 60000.0 << endl;
			mode(_getch());
		}
	}
	else if (btnCode == 69 || btnCode == 101)//E e
	{
		cout << "Exit;" << std::endl;  exit(1);
	}
	else if (btnCode == 70 || btnCode == 102)//F f
	{
		cout << "Field;" << std::endl;  
		int t = 0;
		gameBoard.printFieldcompintheend();
		do{
			gameBoard.shotShipcomp(pointcomp[t].x, pointcomp[t].y);
			gameBoard.printFieldcompintheend();
			t++;
		} while (t < sizeStruct / 2);
		mode(_getch());
	}
	else
	{
		cout << "Error. Enter only S, P, E, G;" << std::endl; mode(_getch());
	}
}
void BattleShipGame::statisticGame()
{		
	cout << "Statistic" << endl;
	ifstream ifile("log.txt");
	string str;
	while (ifile) {
		getline(ifile, str);
		cout << str << endl;
	}
	cout << str;
	mode(_getch());
}

void BattleShipGame::startGame()
{
	cout << "User field " << endl;
	gameBoard.printField();
	cout << endl;
	cout << "Comp field " << endl;
	int indx = 0, flag = 0;
	gameBoard.printFieldcomp();
	
		do {
			if (flag == 0){
				cout << "Enter x coord user: " << endl;
				int x = rand() % 9;
				cout << x << endl;
				cout << "Enter y coord user: " << endl;
				int y = rand() % 9;
				cout << y << endl;
				for (int u = 0; u < indx + 1; u++){
					if (point[u].x == x && point[u].y == y){
						flag = -1;
					}
				}
				if (flag != -1) {
					point[indx].x = x;
					point[indx].y = y;
					gameBoard.shotShip(x, y);
					indx++;
					flag = 1;
				}
				if (globalFlag == 1){
					globalFlag = 0;
					flag = 0;
				}
				if (flag == -1){
					flag = 0;
				}
				cout << "User field " << endl;
				gameBoard.printField();
				cout << endl;
				cout << "Comp field " << endl;
				gameBoard.printFieldcomp();
			}
		cout << endl;
		if (flag == 1){
			cout << "Enter x coord comp: " << endl;
			int xcomp;
			while (!(cin >> xcomp))
			{
				cin.clear();
				while (cin.get() != '\n');
				mode(_getch());
			}
			cout << "Enter y coord comp: " << endl;
			int ycomp;
			while (!(cin >> ycomp))
			{
				cin.clear();
				while (cin.get() != '\n');
				mode(_getch());
			}
			for (int u = 0; u < indx + 1; u++){
				if (pointcomp[u].x == xcomp && pointcomp[u].y == ycomp){
					flag = -1;
				}
			}
			if (flag != -1) {
				pointcomp[indx].x = xcomp;
				pointcomp[indx].y = ycomp;
				gameBoard.shotShipcomp(xcomp, ycomp);
				indx++;
				flag = 0;
			}
			if (globalFlag == 1){
				globalFlag = 0;
				flag = 1;
			}
			if (flag == -1){
				flag = 1;
			}
			cout << "User field " << endl;
			gameBoard.printField();
			cout << endl;
			cout << "Comp field " << endl;
			gameBoard.printFieldcomp();
		}
		endtime = clock();
		clocktime = (endtime - starttime) / 60000.0;
		*log_ << "Time " << clocktime << endl;
		*log_ << "Count Destroyed ship =" << gameBoard.countDestroyedShip() << endl;
		*log_ << "Count Destroyed ship comp =" << gameBoard.countDestroyedShipcomp() << endl;
		sizeStruct = indx;
		} while (!gameBoard.allShipsDestroyed() || !gameBoard.allShipsDestroyedcomp());
	
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
	if (size_){
		delete cells_;
		delete cellscomp_;//
	}
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


void Ship::createShipcomp(GameBoard& gameBoard, int size, int x, int y, bool horizontal)
{
	size_ = size;
	cellscomp_ = new GameBoardCell[size];
	for (int i = 0; i < size; i++)
	{
		if (horizontal) {
			cellscomp_[i].setX(x + i);
			cellscomp_[i].setY(y);
			gameBoard.setStatecomp(x + i, y, (CellState)DECK);
		}
		else {
			cellscomp_[i].setX(x);
			cellscomp_[i].setY(y + i);
			gameBoard.setStatecomp(x, y + i, (CellState)DECK);
		}
	}
}

ShipState Ship::getStatecomp()
{
	int hitCount = 0;
	for (int i = 0; i < size_; i++) {
		if (cellscomp_[i].getStatecomp() == HITDECK){
			hitCount++;
		}
		if (hitCount == 0) {
			statecomp_ = (ShipState)SAFE;
		}
		else if (hitCount < size_) {
			statecomp_ = (ShipState)SHIPHIT;
		}
		else {
			statecomp_ = (ShipState)DESTROYED;
		}
	}
	return statecomp_;
}

void Ship::shotShipcomp(GameBoard & gameBoard, int x, int y)
{
	for (int i = 0; i < size_; i++) {
		if (cellscomp_[i].tryHitcomp(x, y)) {
			cellscomp_[i].setStatecomp((CellState)HITDECK);
			gameBoard.setStatecomp(x, y, (CellState)HITDECK);
			break;
		}
		
		if (getStatecomp() == DESTROYED) {
			for (int i = 0; i < size_; i++)
			{
				int localX = cellscomp_[i].getX();
				int localY = cellscomp_[i].getY();

				if (localX - 1 >= 0 && localY - 1 >= 0 && !gameBoard.isDeckcomp(localX - 1, localY - 1)){
					gameBoard.setStatecomp(localX - 1, localY - 1, (CellState)MISS);
				}
				if (localX - 1 >= 0 && !gameBoard.isDeckcomp(localX - 1, localY)){
					gameBoard.setStatecomp(localX - 1, localY, (CellState)MISS);
				}
				if (localX - 1 >= 0 && localY + 1 < gameBoard.getSize() && !gameBoard.isDeckcomp(localX - 1, localY + 1)){
					gameBoard.setStatecomp(localX - 1, localY + 1, (CellState)MISS);
				}
				if (localY - 1 >= 0 && !gameBoard.isDeckcomp(localX, localY - 1)){
					gameBoard.setStatecomp(localX, localY - 1, (CellState)MISS);
				}
				if (localY + 1 < gameBoard.getSize() && !gameBoard.isDeckcomp(localX, localY + 1)){
					gameBoard.setStatecomp(localX, localY + 1, (CellState)MISS);
				}
				if (localX + 1 < gameBoard.getSize() && localY - 1 >= 0 && !gameBoard.isDeckcomp(localX + 1, localY - 1)){
					gameBoard.setStatecomp(localX + 1, localY - 1, (CellState)MISS);
				}
				if (localX + 1 < gameBoard.getSize() && !gameBoard.isDeckcomp(localX + 1, localY)){
					gameBoard.setStatecomp(localX + 1, localY, (CellState)MISS);
				}
				if (localX + 1 < gameBoard.getSize() && localY + 1 < gameBoard.getSize() && !gameBoard.isDeckcomp(localX + 1, localY + 1)){
					gameBoard.setStatecomp(localX + 1, cellscomp_[i].getY() + 1, (CellState)MISS);
				}
			}
		}
	}
}

bool Ship::tryHitcomp(int x, int y)
{
	for (int i = 0; i < size_; i++) {
		if (cellscomp_[i].tryHitcomp(x, y)) {
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
			globalFlag = 1;
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
int countelementCoordShips = 0;
void GameBoard::autoAddShip(int deckcount, int idx)
{
	CoordShips *coordShips = new CoordShips[gameBoard.getCount()];
	int x, y;
	int position;
	int flag = 0;
	do{
		x = rand() % 9;
		y = rand() % 9;
		position = 0;//rand() % 1;
		int temp = y;
		if (position == 0) {
			for (int u = 0; u < countelementCoordShips; u++){
				if (coordShips[u].x == x && coordShips[u].y == y){
					flag = -1;
				}
			}
			if (flag != -1){
				if (y + deckcount < 10){
					for (int u = countelementCoordShips; u < countelementCoordShips + (deckcount*3+6); u+=3){
						coordShips[u].x = x - 1; if (y < (deckcount + temp)) { coordShips[u].y == y-1;  }
						coordShips[u].x = x; if (y < (deckcount + temp)) { coordShips[u].y == y-1; }
						coordShips[u].x = x + 1; if (y < (deckcount + temp)) { coordShips[u].y == y-1; }
						//y++;
					}
					shipscomp_[idx++].createShipcomp(*this, deckcount, x, y, false);
					flag = 1;
					countelementCoordShips = countelementCoordShips + (deckcount * 3 + 6);
				}
			}
			if (flag != 1){
				flag = 0;
			}
		}
		if (position == 1){
			shipscomp_[idx++].createShipcomp(*this, deckcount, x, y, true);
		}
	} while (flag != 1);

	/*enum State { LOAD, UNLOAD, NONE };
	State state = NONE;
	int i = x - 1;
	if (i < 0){
		i = 0;
	}
	int j = y - 1;
	if (j < 0){
		j = 0;
	}
	int toh = y + 2;
	if (toh -1 == 9){
		toh = 10;
	}
	int tow = deckcount + 1;
	if (tow - 1 == 9){
		tow = 10;
	}
	int towv = x + 1;
	if (towv - 1 == 9){
		towv = 10;
	}
	if (towv < 0){
		towv = 0;
	}
	int tohv = deckcount + 1;
	if (tohv - 1 == 9){
		tohv = 10;
	}
	/*do{
		/*if (!(tow > 10 || towv > 10 || tow < 0 || towv < 0 || toh > 10 | tohv > 10 || toh < 0 || tohv < 0))	{
			if (position == 1){
				for (i; i < i + tow; i++){
					for (j; j < toh; j++){
						if (cellscomp_[i][j].getStatecomp() != EMPTY){
							state = UNLOAD;
						}
					}
				}
				if (state != UNLOAD){
					shipscomp_[idx].createShipcomp(*this, deckcount, x, y, true);
					state = LOAD;
				}
			}
			else if (position == 0){
				for (i; i < towv; i++){
					for (j; j < j + tohv; j++){
						if (cellscomp_[i][j].getStatecomp() != EMPTY){
							state = UNLOAD;
						}
					}
				}
				if (state != UNLOAD){
					shipscomp_[idx].createShipcomp(*this, deckcount, x, y, false);
					state = LOAD;
				}
			}*/
		//}
		/*
		if (cellscomp_[x][y].getStatecomp() == EMPTY && (cellscomp_[x + deskcount][y].getStatecomp() == EMPTY || cellscomp_[x][y + deskcount].getStatecomp() == EMPTY)){
			if (cellscomp_[x + deskcount][y].getStatecomp() == EMPTY && cellscomp_[x][y + deskcount].getStatecomp() == EMPTY){
				if (position == 0){
					shipscomp_[idx++].createShipcomp(*this, deskcount, x, y, false);
				}
				else if (position == 1){
					shipscomp_[idx++].createShipcomp(*this, deskcount, x, y, true);
				}
				state = LOAD;
			}
			else if (cellscomp_[x + deskcount][y].getStatecomp() == EMPTY && !cellscomp_[x][y + deskcount].getStatecomp() == EMPTY){
				shipscomp_[idx++].createShipcomp(*this, deskcount, x, y, true);
				state = LOAD;
			}
			else if (!cellscomp_[x + deskcount][y].getStatecomp() == EMPTY && cellscomp_[x][y + deskcount].getStatecomp() == EMPTY){
				shipscomp_[idx++].createShipcomp(*this, deskcount, x, y, false);
				state = LOAD;
			}*{/
		//	else {
				x = rand() % 9;
				y = rand() % 9;
				position = rand() % 1;
		//	}
		//}
	} while (state != LOAD);*/

}


void GameBoard::generateBoardcomp()
{
	for (int i = 0; i < FIELD_SIZE; i++)	{
		for (int j = 0; j < FIELD_SIZE; j++) {
			cellscomp_[i][j].setStatecomp((CellState)EMPTY);
		}
	}

	int idx = 0;
	/*autoAddShip(4, idx++);
	autoAddShip(3, idx++);
	autoAddShip(3, idx++);
	autoAddShip(2, idx++);
	autoAddShip(2, idx++);
	autoAddShip(2, idx++);
	autoAddShip(1, idx++);
	autoAddShip(1, idx++);
	autoAddShip(1, idx++);
	autoAddShip(1, idx++);
	*/
	shipscomp_[idx++].createShipcomp(*this, 4, 0, 0, true);
	shipscomp_[idx++].createShipcomp(*this, 3, 0, 2, false);
	shipscomp_[idx++].createShipcomp(*this, 3, 8, 1, false);
	shipscomp_[idx++].createShipcomp(*this, 2, 3, 9, true);
	shipscomp_[idx++].createShipcomp(*this, 2, 2, 6, true);
	shipscomp_[idx++].createShipcomp(*this, 2, 6, 5, true);
	shipscomp_[idx++].createShipcomp(*this, 1, 4, 2, true);
	shipscomp_[idx++].createShipcomp(*this, 1, 8, 8, true);
	shipscomp_[idx++].createShipcomp(*this, 1, 0, 8, true);
	shipscomp_[idx++].createShipcomp(*this, 1, 6, 0, true);
	

}



void GameBoard::printFieldcomp()
{
	for (int i = 0; i < FIELD_SIZE; i++) {
		cout << "|";
		for (int j = 0; j < FIELD_SIZE; j++) {
			cellscomp_[i][j].printFieldcomp();
			cout << "|";
		}
		cout << endl;
	}
}

void GameBoard::printFieldcompintheend()
{
	for (int i = 0; i < FIELD_SIZE; i++) {
		cout << "|";
		for (int j = 0; j < FIELD_SIZE; j++) {
			cellscomp_[i][j].printFieldcompintheend();
			cout << "|";
		}
		cout << endl;
	}
}
void GameBoard::shotShipcomp(int x, int y)
{
	for (int i = 0; i < SHIPS_COUNT; i++) {
		if (shipscomp_[i].tryHitcomp(x, y))	{
			shipscomp_[i].shotShipcomp(*this, x, y);
			globalFlag = 1;
			break;
		}
		else {
			cellscomp_[y][x].setStatecomp((CellState)MISS);
		}
	}
}

bool GameBoard::allShipsDestroyedcomp()
{
	for (int i = 0; i < SHIPS_COUNT; i++) {
		if (shipscomp_[i].getStatecomp() != DESTROYED) {
			return false;
		}
	}
	return true;
}

int GameBoard::countDestroyedShipcomp()
{
	int counter = 0;
	for (int i = 0; i < SHIPS_COUNT; i++) {
		if (shipscomp_[i].getStatecomp() == DESTROYED) {
			counter++;
		}
	}
	return counter;
}

int GameBoard::countDestroyedShip()
{
	int counter = 0;
	for (int i = 0; i < SHIPS_COUNT; i++) {
		if (ships_[i].getState() == DESTROYED) {
			counter++;
		}
	}
	return counter;
}