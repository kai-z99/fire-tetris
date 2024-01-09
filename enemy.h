#pragma once
#include "block.h"
#include "position.h"

class EnemyJ : public Block
{
public:
	EnemyJ(int row, char spawnState);

	
};

class EnemyL : public Block
{
public:
	EnemyL(int row, char spawnState);

};

class EnemyO : public Block
{
public:
	EnemyO(int row, char spawnState);

};

class EnemyT : public Block
{
public:
	EnemyT(int row, char spawnState);

};

class EnemyS : public Block
{
public:
	EnemyS(int row, char spawnState);
};

class EnemyZ : public Block
{
public:
	EnemyZ(int row, char spawnState);
};

class EnemyI : public Block
{
public:
	EnemyI(int row, char spawnState);
};

class EnemyWall : public Block
{
public:
	EnemyWall();
};





// make a big ahh wall that cuts of half the screen hehe