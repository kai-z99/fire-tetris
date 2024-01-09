#pragma once
#include <vector>
#include "raylib.h"

class Grid {
public:
	Grid();
	void Initialize();
	void Print();
	void Draw();
	bool IsCellOutside(int row, int col);
	bool IsCellEmpty(int row, int col);
	int ClearFullRows();
	int grid[20][10];
	int GetRows();
	int GetCols();
	void ClearCell(int row, int col);
	void AssignSingleCellId(int row, int col, int id);
	

private:
	bool IsRowFull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int numRows);
	int numRows;
	int numCols;
	int cellSize;
	std::vector<Color> colors;

};
