#include "stdafx.h"
#include "Game.h"

void C_PlayerSeaBattle::Initialization(void)
	{
		strcpy_s(arrPlayerStatus, "in game");
		memset(arrMyBoard, 0, sizeof arrMyBoard);
		memset(arrCompBoard, 0, sizeof arrCompBoard);

		arrMyBoard[0][0] = 1;
		arrMyBoard[1][1] = 1;
		arrMyBoard[2][2] = 1;
		arrMyBoard[3][3] = 1;
	}

char* C_PlayerSeaBattle::PlayerStatus(void)
	{ return arrPlayerStatus; }


void C_PlayerSeaBattle::Attack(int &x, int&y)
	{
		x = 1;
		y = 1;
		if (arrMyBoard[1][1] == 1)
			destroyedShip++;
	}


char C_PlayerSeaBattle::TestCell(unsigned int x, unsigned int y)
	{
		if (x > 9 || y > 9) return ERROR;

		if (arrMyBoard[x][y] == 0) return NONE;

		if (destroyedShip == 1)
		{
			strcpy_s(arrPlayerStatus, "Proigral");
		}

		return KILL;
	}


void C_PlayerSeaBattle::DrawBoard(void)
	{
	for (int i = 0; i < 10; i++)
		for (int l = 0; l < 10; l++)
			cout << arrMyBoard[i][l];
	cout << endl;
	}
