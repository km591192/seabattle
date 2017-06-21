
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
	~Ship();
	ShipState getState();
	void shotShip(GameBoard& gameBoard, int x, int y);
	bool tryHit(int x, int y);
private:
	GameBoardCell* cells_;
	ShipState state_;
	int size_;
};

