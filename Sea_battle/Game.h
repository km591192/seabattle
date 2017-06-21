#include <iostream>
#include <string>
#include <cctype>
using namespace std;
class C_PlayerSeaBattle
{
public:
	
	C_PlayerSeaBattle(void) {}
	virtual ~C_PlayerSeaBattle(void) {}
	void Initialization(void);
	char* PlayerStatus(void);
	void Attack(int &x, int&y);
	enum Cellstatus
	{
		ERROR,
		NONE,
		KILL
	};
	char TestCell(unsigned int x, unsigned int y);
	void DrawBoard(void);

private:	
	int arrMyBoard[10][10];
	int arrCompBoard[10][10];
	char arrPlayerStatus[100];
	int destroyedShip = 0;
	
};