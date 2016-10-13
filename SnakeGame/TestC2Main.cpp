/*
 * TestC2Main.cpp
 *
 *  Created on: 2016年3月11日
 *      Author: Lin Kao-Yuan
 *		 Limit: max stack 256MB(java 50m)
 */

#include <iostream>
#include "SnakeGame - 複製.h"
using namespace std;

void PrintArray(Grid* g)
{
	for (int j = 0; j < g->GetRows(); j++)
	{
		for (int i = 0; i<g->GetCols(); i++)
		{
			cout << g->GetCell(i, j) << " ";
		}
		cout << endl;
	}
}

int main(){
	int row, col;
	cin >> row  >> col;
	Grid grid = Grid(row, col);

	//read array
	for(int j=0;j<row;j++){
		for(int i=0;i<col;i++){
			int num;
			cin >> num;
			grid.SetCell(i, j, num);
		}
	}

	//verification
	PrintArray(&grid);
	cout << endl;
	grid.Print();

	Cell* ptr_sg00 = new RootCell(grid, 0, 0);
	Cell* ptr_sg01 = new RootCell(grid, 0, 1);
	Cell* ptr_sg02 = new RootCell(grid, 0, 2);
	Cell* ptr_sg03 = new RootCell(grid, 0, 3);

	cout << ptr_sg00->GetLocalMax() << endl;
	cout << ptr_sg01->GetLocalMax() << endl;
	cout << ptr_sg02->GetLocalMax() << endl;
	cout << ptr_sg03->GetLocalMax() << endl;

	ptr_sg00 = new SnakeGame(ptr_sg00, 0, 0, grid);
	ptr_sg01 = new SnakeGame(ptr_sg01, 0, 1, grid);
	ptr_sg02 = new SnakeGame(ptr_sg02, 0, 2, grid);
	ptr_sg03 = new SnakeGame(ptr_sg03, 0, 3, grid);

	cout << max(
		max(ptr_sg00->GetLocalMax(), ptr_sg01->GetLocalMax()),
		max(ptr_sg02->GetLocalMax(), ptr_sg03->GetLocalMax())
		);

	system("PAUSE");
}



