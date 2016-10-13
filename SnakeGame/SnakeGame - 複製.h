#include <iostream>
#include <algorithm>
#include "Grid.h"
using namespace std;

class Cell
{
protected:
	int row;
	int col;
	int cellValue;
public:
	virtual int GetLocalMax() = 0;
};

class RootCell:public Cell
{
private:Grid grid;
public:
	RootCell(Grid grid, int row, int col)
	{
		Cell::row = row;
		Cell::col = col;
		Cell::cellValue = cellValue;
	}
	int GetLocalMax() { return Cell::cellValue; };
};

class SnakeGame:public Cell
{
private:Grid grid;
private:int row;
private:int col;
private:bool bAlreadyTeleport = false;

private:
	SnakeGame* upSG;
	SnakeGame* downSG;
	SnakeGame* rightSG;

private:
	bool bLeaf = false;

public:SnakeGame()
{
	SnakeGame::counter++;
	this->bLeaf = true;
}

public:SnakeGame(Cell* ptr_sg, int _row, int _col, Grid grid)
{
	SnakeGame::counter++;
	cout << "SnakeGame::counter = "<< SnakeGame::counter << endl;

	this->row = _row;
	this->col = _col;
	this->grid = grid;

	//keep self value
	Cell::cellValue = this->grid.GetCell(_row, _col);

	//visited mark
	this->grid.SetCell(_row, _col, -2);

	int up = this->grid.GetCell(RowFit(_row + 1), ColFit(col + 0));
	int down = this->grid.GetCell(RowFit(_row - 1), ColFit(col + 0));
	int right = this->grid.GetCell(RowFit(_row + 0), ColFit(col + 1));

	rightSG = (0 <= right) ? new SnakeGame(rightSG, RowFit(_row + 0), ColFit(col + 1), this->grid) :  new SnakeGame();
	upSG    = (0 <= up)    ? new SnakeGame(upSG, RowFit(_row + 1), ColFit(col + 0), this->grid) :  new SnakeGame();
	downSG  = (0 <= down)  ? new SnakeGame(downSG, RowFit(_row - 1), ColFit(col + 0), this->grid) :  new SnakeGame();
}

public:int GetLocalMax()
{ 
	if (bLeaf)
		return 0;
	else
	{
		//if (rightSG->bAlreadyTeleport || downSG->bAlreadyTeleport || upSG->bAlreadyTeleport)
		//if(this->bAlreadyTeleport)
		//{
		//	return max(rightSG->GetLocalMax(), max(downSG->GetLocalMax(), upSG->GetLocalMax()));
		//}
		//else
		{
			return Cell::cellValue + max(rightSG->GetLocalMax(), max(downSG->GetLocalMax(), upSG->GetLocalMax()));
		}
	}
}

private:static int counter;

private:int RowFit(int row)
{
	return RangeTeleport(row, grid.GetRows());
}
private:int ColFit(int col)
{
	//up limit
	if (col >= this->grid.GetCols())
		col = this->grid.GetCols() - 1;

	return col;
	//return RangeTeleport(col, grid.GetCols());
}
private:int RangeTeleport(int num, int limit)
{
	//Pay all current point
	if (num >= limit || num < 0) bAlreadyTeleport = true;

	num = num % limit;

	if (num < 0)
		return num + limit;
	else
		return num;
}

};
int SnakeGame::counter = 0;