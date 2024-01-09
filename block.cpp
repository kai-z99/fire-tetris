#include "block.h"


Block::Block()
{
	cellSize = 30;
	rotationState = 0;
	colors = GetCellColors();
	rowOffset = 0;
	colOffset = 0;
	spawnState = 0;
}

void Block::Draw(int offsetX, int offsetY)
{
	std::vector<Position> tiles = GetCellPositions();

	for (Position item : tiles)
	{
		DrawRectangle(item.col * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[std::min(id, 9)]);
	}
}

void Block::Move(int rows, int cols)
{
	rowOffset += rows;
	colOffset += cols;
}

std::vector<Position> Block::GetCellPositions()
{
	std::vector<Position> tiles = cells[rotationState];
	std::vector<Position> movedTiles;

	for (Position item : tiles)
	{
		Position newPos = Position(item.row + rowOffset, item.col + colOffset);
		movedTiles.push_back(newPos);
	}

	return movedTiles;
}

void Block::Rotate()
{
	rotationState += 1;

	if (rotationState == cells.size())	
	{
		rotationState = 0;
	}
}

void Block::UndoRotate()
{
	rotationState -= 1;

	if (rotationState == -1)
	{
		rotationState = static_cast<int>(cells.size() - 1);
	}
}