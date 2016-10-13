#include <iostream>
#include "SnakeGameDP.h"
using namespace std;

int main() {
	int row, col;
	cin >> row >> col;
	Grid grid = Grid(row, col);

	//read array
	for (int j = 0; j<row; j++) {
		for (int i = 0; i<col; i++) {
			int num;
			cin >> num;
			grid.SetCell(i, j, num);
		}
	}

	//verification input
	cout << endl;
	cout << grid.ToString() << endl;

	SnakeGame* sg = new SnakeGame(grid);

	cout << sg->GetGlobalMax(true);

	system("PAUSE");
}