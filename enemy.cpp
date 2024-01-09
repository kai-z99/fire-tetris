#include "enemy.h"
#include <string>
#include <iostream>
EnemyJ::EnemyJ(int row, char spawnState)
{
	id = 9;
	this->spawnState = spawnState;

	cells[0] = { Position(0,0), Position(1,0), Position(1,1), Position(1,2) };
	cells[1] = { Position(0,1), Position(0,2), Position(1,1), Position(2,1) };
	cells[2] = { Position(1,0), Position(1,1), Position(1,2), Position(2,2) };
	cells[3] = { Position(0,1), Position(1,1), Position(2,0), Position(2,1) };

	if (spawnState == 'L')
	{
		Move(row, 0);
	}

	else if (spawnState == 'R')
	{
		Move(row, 7);
	}

	else
	{
		Move(18, std::max((row / 2), 0));
	}
	
}

EnemyO::EnemyO(int row, char spawnState)
{
	id = 10;
	this->spawnState = spawnState;

	cells[0] = { Position(0,0), Position(0,1), Position(1,0), Position(1,1) };

	if (spawnState == 'L')
	{
		Move(row, 0);
	}

	else if (spawnState == 'R')
	{
		Move(row, 8);
	}

	else
	{
		Move(18, std::max((row / 2), 0));
	}
}

EnemyL::EnemyL(int row, char spawnState)
{
	id = 11;
	this->spawnState = spawnState;

	cells[0] = { Position(0,2), Position(1,0), Position(1,1), Position(1,2) };
	cells[1] = { Position(0,1), Position(1,1), Position(2,1), Position(2,2) };
	cells[2] = { Position(1,0), Position(1,1), Position(1,2), Position(2,0) };
	cells[3] = { Position(0,0), Position(0,1), Position(1,1), Position(2,1) };

	if (spawnState == 'L')
	{
		Move(row, 0);
	}

	else if (spawnState == 'R')
	{
		Move(row, 7);
	}

	else
	{
		Move(18, std::max((row / 2), 0));
	}
}

EnemyT::EnemyT(int row, char spawnState)
{
	id = 12;
	this->spawnState = spawnState;

	cells[0] = { Position(0,1), Position(1,0), Position(1,1), Position(1,2) };
	cells[1] = { Position(0,1), Position(1,1), Position(1,2), Position(2,1) };
	cells[2] = { Position(1,0), Position(1,1), Position(1,2), Position(2,1) };
	cells[3] = { Position(0,1), Position(1,0), Position(1,1), Position(2,1) };

	if (spawnState == 'L')
	{
		Move(row, 0);
	}

	else if (spawnState == 'R')
	{
		Move(row, 7);
	}

	else
	{
		Move(18, std::max((row / 2), 0));
	}
}

EnemyS::EnemyS(int row, char spawnState)
{
	id = 13;
	this->spawnState = spawnState;

	cells[0] = { Position(0,1), Position(0,2), Position(1,0), Position(1,1) };
	cells[1] = { Position(0,1), Position(1,1), Position(1,2), Position(2,2) };
	cells[2] = { Position(1,1), Position(1,2), Position(2,0), Position(2,1) };
	cells[3] = { Position(0,0), Position(1,0), Position(1,1), Position(2,1) };

	if (spawnState == 'L')
	{
		Move(row, 0);
	}

	else if (spawnState == 'R')
	{
		Move(row, 7);
	}

	else
	{
		Move(18, std::max((row / 2), 0));
	}
}

EnemyZ::EnemyZ(int row, char spawnState)
{
	id = 14;
	this->spawnState = spawnState;

	cells[0] = { Position(0,0), Position(0,1), Position(1,1), Position(1,2) };
	cells[1] = { Position(0,2), Position(1,1), Position(1,2), Position(2,1) };
	cells[2] = { Position(1,0), Position(1,1), Position(2,1), Position(2,2) };
	cells[3] = { Position(0,1), Position(1,0), Position(1,1), Position(2,0) };

	if (spawnState == 'L')
	{
		Move(row, 0);
	}

	else if (spawnState == 'R')
	{
		Move(row, 7);
	}

	else
	{
		Move(18, std::max((row / 2) , 0));
	}
}

EnemyI::EnemyI(int row, char spawnState)
{
	id = 15;
	this->spawnState = spawnState;

	cells[0] = { Position(0,1), Position(1,1), Position(2,1), Position(3,1) };
	cells[1] = { Position(1,0), Position(1,1), Position(1,2), Position(1,3) };
	cells[2] = { Position(0,2), Position(1,2), Position(2,2), Position(3,2) };
	cells[3] = { Position(2,0), Position(2,1), Position(2,2), Position(2,3) };
	

	if (spawnState == 'L')
	{
		Move(row, -1);
	}

	else if (spawnState == 'R')
	{
		Move(row, 8);
	}

	else
	{
		cells[0] = { Position(1,0), Position(1,1), Position(1,2), Position(1,3) };
		cells[1] = { Position(0,2), Position(1,2), Position(2,2), Position(3,2) };
		cells[2] = { Position(2,0), Position(2,1), Position(2,2), Position(2,3) };
		cells[3] = { Position(0,1), Position(1,1), Position(2,1), Position(3,1) };
		Move(18, std::max((row / 2), 0)); // fix
	}
}

EnemyWall::EnemyWall()
{
	id = 16;
	pastHalf = false;

	cells[0] = { };

	for (int i = 0; i <= 19; i++)
	{
		cells[0].push_back(Position(i, 0));
	}

	int randomNum = GetRandomValue(1, 2);

	if (randomNum == 1)
	{
		spawnState = 'L';
	}

	else
	{
		spawnState = 'R';
		Move(0, 9);
	}


}
