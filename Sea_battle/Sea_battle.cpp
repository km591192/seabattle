// Sea_battle.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "BattleShipGame.h"
#include "GameBoard.h"
#include <iostream>

using namespace std;

BattleShipGame battleShipGame;
int main(int argc, char** argv)
{
	battleShipGame.startGame();
	return 0;
}
