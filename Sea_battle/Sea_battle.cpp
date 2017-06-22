// Sea_battle.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "BattleShipGame.h"
#include "GameBoard.h"
#include <iostream>
#include <conio.h>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
	std::ofstream log("log.txt", std::ios::out | std::ios::trunc);
	BattleShipGame battleShipGame(&log);
	battleShipGame.mode(_getch());
	log.close();
	return 0;
}
