#pragma once
#include <iostream>
#include <algorithm>
using namespace std;

class SnakeGame
{
private:int rows;
private:int cols;
private:int** nOrinigal2Darr;

private:int** CopyDayn2DArr(int** _n2Darr)
{
	int** n2Darr = new int*[rows];
	for (int i = 0; i<rows; i++)
	{
		n2Darr[i] = new int[cols];
	}

	for (int i = 0; i<this->cols; i++)
	{
		for (int j = 0; j<this->rows; j++)
		{
			n2Darr[i][j] = _n2Darr[i][j];
		}
	}

	return n2Darr;
}
int SnakeGame::BoxCounter = 0;

public: SnakeGame(int rows, int cols)
{
	if (rangeChack(rows) && rangeChack(cols))
	{//pass check
		this->rows = rows;
		this->cols = cols;

		nOrinigal2Darr = new int*[rows];
		for (int i = 0; i<rows; i++)
		{
			nOrinigal2Darr[i] = new int[cols];
		}
	}
	else
	{
		cout << "range ERROR" << endl;
	}
}

public:void fillNum(int row, int col, int num)
{
	nOrinigal2Darr[row][col] = num;
}

public:void PrintArray()
{
	for (int i = 0; i<this->rows; i++)
	{
		for (int j = 0; j<this->cols; j++)
		{
			cout << this->nOrinigal2Darr[i][j] << " ";
		}
		cout << endl;
	}
}

private:void PrintArray(int** _n2Darr)
{
	for (int i = 0; i<this->rows; i++)
	{
		for (int j = 0; j<this->cols; j++)
		{
			cout << _n2Darr[i][j] << " ";
		}
		cout << endl;
	}
}

private:bool rangeChack(int num)
{
	if (1 <= num && num <= 500)
		return true;
	else
		return false;
}

private:int RowFit(int row)
{
	//up limit
	//if (row >= this->rows)
	//	row = this->rows - 1;

	return RangeTeleport(row, this->rows);
}
private:int ColFit(int col)
{
	//up limit
	if (col >= this->cols)
		col = this->cols-1;
	
	return col;
	//return RangeTeleport(col, this->cols);
}
private:int RangeTeleport(int num, int limit)
{
	num = num % limit;
	
	if (num < 0)
		return num + limit;
	else
		return num;
}

public:int FindMax(int row, int col, int** _n2Darr)
{
	SnakeGame::BoxCounter++;
	//cout << SnakeGame::BoxCounter << endl;
	cout << "row=" << row <<" ,col="<<col << endl;
	PrintArray(_n2Darr);

	//three direction
	int up = _n2Darr[RowFit(row + 1)][col];
	int down = _n2Darr[RowFit(row - 1)][col];
	int right = _n2Darr[row][ColFit(col + 1)];

	//save core number
	int tempCoreCell = _n2Darr[row][col];
	
	//used mark
	_n2Darr[row][col] = -2;

	if (0 > up)up = 0;
	else up = FindMax(RowFit(row + 1),col,CopyDayn2DArr(_n2Darr));
	
	if (0 >  down)down = 0;
	else down = FindMax(RowFit(row - 1), col, CopyDayn2DArr(_n2Darr));

	if (0 > right)right = 0;
	else right = FindMax(row, ColFit(col + 1), CopyDayn2DArr(_n2Darr));

	//delete
	for (int j = 0; j<this->rows; j++)
	{
		delete[] _n2Darr[j];
	}
	delete _n2Darr;

	SnakeGame::BoxCounter--;
	return tempCoreCell + max(up, max(down, right));
}

public:int GetBiggestAns()
{
	//int row = 3, col = 0;
	int* startCell = new int[this->rows];
	int maxValue = 0;

	for (int i = 0; i < this->rows; i++)
	{
		startCell[i] = FindMax(i, 0, CopyDayn2DArr(this->nOrinigal2Darr));
	}

	for (int i = 0; i < this->rows; i++)
	{
		maxValue = max(maxValue, startCell[i]);
	}

	return maxValue;
}
};