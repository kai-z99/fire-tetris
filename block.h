#pragma once
#include <map>
#include <vector>
#include "position.h"
#include "colors.h"

class Block
{
public:
	Block();
	void Move(int rows, int cols);
	std::vector<Position> GetCellPositions();
	void Draw(int offsetX, int offsetY);
	void Rotate();
	void UndoRotate();
	int id;
	char spawnState;
	std::map<int, std::vector<Position>> cells;
	bool pastHalf;

private:
	int cellSize;
	int rotationState;
	int rowOffset;
	int colOffset;
	std::vector<Color> colors;
 
};