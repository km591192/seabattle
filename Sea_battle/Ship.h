
//#include "GameBoardCell.h"
#include "Enum.h"
//#include "GameBoard.h"

//ShipState
class GameBoardCell;
class GameBoard;

class Ship
{
public:
	Ship();
	void createShip(GameBoard& gameBoard, int size, int x, int y, bool horizontal); 
	void createShipcomp(GameBoard& gameBoard, int size, int x, int y, bool horizontal);
	~Ship();
	ShipState getState();
	ShipState getStatecomp();
	void shotShip(GameBoard& gameBoard, int x, int y);
	void shotShipcomp(GameBoard& gameBoard, int x, int y); 
	bool tryHit(int x, int y);
	bool tryHitcomp(int x, int y); 
private:
	GameBoardCell* cells_;
	GameBoardCell* cellscomp_;
	ShipState state_;
	ShipState statecomp_;
	int size_;
};

