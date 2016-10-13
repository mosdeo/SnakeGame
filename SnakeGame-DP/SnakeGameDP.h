#pragma once
#include<iostream>
#include<iomanip>
#include<sstream>
#include<algorithm>
#include"Grid.h"
using namespace std;

class SnakeGame
{
private:Grid grid;
private:int* ptrEnterPortMaxScore;
public:int** ptrColMaxMat;

public:SnakeGame(Grid grid)
{
	this->grid = grid;

	//set all 0
	this->ptrEnterPortMaxScore = new int[grid.GetRows()];
	for (int i = 0; i < grid.GetRows(); i++)
	{
		ptrEnterPortMaxScore[i] = 0;
	}

	//allocat mem
	ptrColMaxMat = new int*[grid.GetRows()];
	for (int i = 0; i < grid.GetRows(); i++)
	{
		ptrColMaxMat[i] = new int[grid.GetRows()];
	}
}

private:void CalcColMaxMat(int col)
{
	//fill ptrColMaxMat
	for (int i = 0; i<this->grid.GetRows(); i++)
	{
		for (int j = 0; j<this->grid.GetRows(); j++)
		{
			int localSum = 0;

			if (i != j)
			{
				for (int k = min(i, j); k <= max(i, j); k++)
				{
					if (-1 == grid.GetCell(col, k))
					{//block cell
						localSum = -1;
						break;
					}
					else
					{
						localSum += grid.GetCell(col, k);
					}
				}
			}
			else if (i == j)
			{//¹ï¨¤½u¤W
				if (-1 == grid.GetCell(col, i))
				{//block cell
					localSum = -1;
				}
				else
				{
					localSum = grid.GetCell(col, i);
				}
			}

			ptrColMaxMat[i][j] = localSum;
		}
	}



}

private:void CalcColumnLocalMax1DArray()
{
	//add ptrEnterPortMaxScore into column local max array
	for (int i = 0; i < grid.GetCols(); i++)
	{
		for (int j = 0; j < grid.GetCols(); j++)
		{
			if (-1 != ptrColMaxMat[i][j])
			{
				ptrColMaxMat[i][j] += ptrEnterPortMaxScore[i];
			}
		}
	}

	//fill column local max  1D-array, ex:10, 9, 8, 10
	for (int i = 0; i < grid.GetCols(); i++)
	{
		bool bTheRowEnterNotAllBlock = false;
		for (int j = 0; j < grid.GetCols(); j++)
		{
			if (-1 != ptrColMaxMat[j][i])
			{
				bTheRowEnterNotAllBlock = true;
				ptrEnterPortMaxScore[i] = max(ptrEnterPortMaxScore[i], ptrColMaxMat[j][i]);
			}
		}

		if (!bTheRowEnterNotAllBlock) ptrEnterPortMaxScore[i] = -1;
	}
}

public:int GetGlobalMax(bool bShowDetail=false)
{
	int m = grid.GetCols();
	while (m-- > 0)
	{
		CalcColMaxMat(m);
		if (bShowDetail)
		{
			cout << "Single Column Score Matrix" << endl;
			cout << ToString(grid.GetCols(), grid.GetCols(), ptrColMaxMat);
		}

		CalcColumnLocalMax1DArray();
		if (bShowDetail)
		{
			cout << "Column Local Max 1DArray" << endl;
			cout << ToString(grid.GetCols(), ptrEnterPortMaxScore);
			cout << endl;
		}
	}

	int GlobalMax = -1;
	for (int i = 0; i < grid.GetRows(); i++)
	{
		GlobalMax = max(GlobalMax, ptrEnterPortMaxScore[i]);
	}

	return GlobalMax;
}

private:string ToString(int cols, int rows, int** n2DArr)
{
	stringstream outString;

	for (int j = 0; j < cols; j++)
	{
		for (int i = 0; i<rows; i++)
		{
			outString << std::setfill(' ') << setw(2) << n2DArr[i][j] << " ";
		}
		outString << endl;
	}

	return outString.str();
}

private:string ToString(int cols, int* n1DArr)
{
	stringstream outString;

	for (int i = 0; i < cols; i++)
	{
		outString << std::setfill(' ') << setw(2) << n1DArr[i] << " ";
	}
	outString << endl;

	return outString.str();
}

};