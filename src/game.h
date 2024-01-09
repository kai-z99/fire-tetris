#pragma once
#include "grid.h"
#include "blocks.cpp"
#include "enemy.h"
#include <string>

class Game
{
public:
	Game();
	~Game();

	void Draw();
	void HandleInput();

	int totalBlocksDropped;
	bool canIncreaseSpeed;
	bool enemyIsActive;
	int score;
	int frameCount;

	void SpawnEnemy();
	void DespawnEnemy();

	void MoveBlockDown(int offset);
	void HandleEnemyMovement();
	void CheckCollision();

	bool gameOver;
	
	Music music;
	Grid grid;
	
private:
	void Reset();

	Block GetRandomBlock();
	Block GetRandomEnemy();

	std::vector<Block> GetAllBlocks();
	std::vector<Block> GetAllEnemies();
	std::vector<Block> blocksQueue;
	std::vector<Block> enemiesQueue;

	int moveCooldownFrames;
	int currentEnemyMoves;

	void MoveBlockLeft(int offset);
	void MoveBlockRight(int offset);
	void MoveBlockUp(int offset);

	Block currentBlock;
	Block nextBlock;
	Block currentEnemy;

	std::vector<Position> GetCurrentEnemyPosition();
	std::vector<Position> GetCurrentBlockPosition();
	char GetCurrentEnemyType();
	char GetRandomSpawnState();

	void DetonateBlock(int row, int col);
	void RotateBlock();
	void LockBlock();
	bool BlockFits();
	void UpdateScore(int linesCleared);

	void HandleWallMovement();
	void UpdatePastHalf();
	
	bool IsBlockOutside();
	
	bool EnemyCollided();
	bool IsEnemyOutside();
	void MoveEnemyLeft(int offset);
	void MoveEnemyRight(int offset);
	void MoveEnemyUp(int offset);
	void MoveEnemyDown(int offset);
	void RotateCurrentEnemy();
	
	Sound rotateSound;
	Sound enemyRotateSound;
	Sound detonateSound;
	Sound lockSound;
	Sound loseSound;
	Sound undoRotateSound;
	Sound tetrisSound;
	Sound oneLineClearSound;
	Sound twoLineClearSound;
	Sound threeLineClearSound;
	Sound fourLineClearSound;
	Sound enemySpawn;

};
