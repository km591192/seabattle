#ifndef ENUM_H
#define ENUM_H
enum CellState { EMPTY, DECK, MISS, HITDECK, KILL};
enum ShipState { DESTROYED, SHIPHIT, SAFE };
struct CoordXY {
	int x;
	int y;
};
struct CoordXYcomp{
	int x;
	int y;
};
struct CoordShips{
	int x;
	int y;
};
#endif