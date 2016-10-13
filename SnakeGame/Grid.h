#pragma once
#pragma once
#include <iostream>
using namespace std;

class Grid
{
private:int rows;
private:int cols;
private:int** n2DArr;

public:Grid()
{}

public:Grid(const Grid &g)
{
	cout << "Copy constructor!" << endl;

	this->rows = g.rows;
	this->cols = g.cols;

	//allocat mem
	this->n2DArr = new int*[rows];
	for (int i = 0; i<rows; i++)
	{
		this->n2DArr[i] = new int[cols];
	}

	//set value
	for (int j = 0; j < this->rows; j++)
	{
		for (int i = 0; i < this->cols; i++)
		{
			this->n2DArr[i][j] = g.n2DArr[i][j];
		}
	}
}

	   // 複製指定運算子成員函式
	   Grid& operator=(const Grid& clone)
	   {
		   cout << "Grid& operator=(const Grid& clone)" << endl;
		   // 保護：禁止自己設值給自己
		   if (this != &clone)
		   {
			   this->rows = clone.rows;
			   this->cols = clone.cols;

			   //allocat mem
			   this->n2DArr = new int*[rows];
			   for (int i = 0; i<rows; i++)
			   {
				   this->n2DArr[i] = new int[cols];
			   }

			   //set value
			   for (int j = 0; j < this->rows; j++)
			   {
				   for (int i = 0; i < this->cols; i++)
				   {
					   this->n2DArr[i][j] = clone.n2DArr[i][j];
				   }
			   }
		   }
		   return *this;
	   }

public:Grid(int rows, int cols, int** _n2DArr)
{
	this->rows = rows;
	this->cols = cols;

	//allocat mem
	this->n2DArr = new int*[rows];
	for (int i = 0; i<rows; i++)
	{
		this->n2DArr[i] = new int[cols];
	}

	//set value
	for (int j = 0; j < this->rows; j++)
	{
		for (int i = 0; i < this->cols; i++)
		{
			this->n2DArr[i][j] = _n2DArr[i][j];
		}
	}

	Grid::counter++;
}

public:Grid(int rows, int cols)
{
	this->rows = rows;
	this->cols = cols;

	//allocat mem
	this->n2DArr = new int*[rows];
	for (int i = 0; i<rows; i++)
	{
		this->n2DArr[i] = new int[cols];
	}

	Grid::counter++;
}

public:void SetCell(int row, int col, int num)
{
	this->n2DArr[row][col] = num;
}

public:int GetCell(int row, int col)
{
	return this->n2DArr[row][col];
}

public:int GetRows() { return this->rows; }
public:int GetCols() { return this->cols; }

	   ~Grid()
	   {
		   //delete
		   for (int j = 0; j<this->rows; j++)
		   {
			   delete[] this->n2DArr[j];
		   }
		   delete this->n2DArr;

		   Grid::counter--;
	   }

private:static int Grid::counter;
public:int GetCount() { return Grid::counter; }

public:void Print()
{
	for (int j = 0; j < this->cols; j++)
	{
		for (int i = 0; i < this->rows; i++)
		{
			cout << this->n2DArr[i][j];
		}
		cout << endl;
	}

}
};
int Grid::counter = 0;
