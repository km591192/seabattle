#ifndef BATTLE_SHIP_GAME_H
#define BATTLE_SHIP_GAME_H
#include <iostream>
using namespace std;
class  BattleShipGame
{
public:
	BattleShipGame(std::ofstream* log);
	void mode(int btnCode);
	void statisticGame();
	void startGame();
private:
	std::ofstream* log_;
};
#endif


