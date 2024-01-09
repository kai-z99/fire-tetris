#include "game.h"
#include <random>
#include <ctime>
#include <iostream>
#include <typeInfo>

Game::Game()
{
	srand(static_cast<unsigned int>(time(0)));

	grid = Grid();

	frameCount = 0;
	moveCooldownFrames = 5;

	blocksQueue = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();

	enemiesQueue = GetAllEnemies();
	currentEnemy = GetRandomEnemy();
	
	totalBlocksDropped = 1;
	enemyIsActive = false;
	currentEnemyMoves = 0;
	gameOver = false;
	canIncreaseSpeed = true;
	score = 0;
	

	InitAudioDevice();
	music = LoadMusicStream("Sounds/Music.mp3");
	PlayMusicStream(music);
	rotateSound = LoadSound("Sounds/Rotate.mp3");
	enemyRotateSound = LoadSound("Sounds/EnemyRotate.mp3");
	lockSound = LoadSound("Sounds/Lock.mp3");
	detonateSound = LoadSound("Sounds/Detonate.mp3");
	loseSound = LoadSound("Sounds/Lose.mp3");
	undoRotateSound = LoadSound("Sounds/UndoRotate.mp3");
	tetrisSound = LoadSound("Sounds/Tetris.mp3");
	oneLineClearSound = LoadSound("Sounds/1LineClear.mp3");
	twoLineClearSound = LoadSound("Sounds/2LineClear.mp3");
	threeLineClearSound = LoadSound("Sounds/3LineClear.mp3");
	fourLineClearSound = LoadSound("Sounds/4LineClear.mp3");
	enemySpawn = LoadSound("Sounds/EnemySpawn.mp3");

}

Game::~Game()
{
	UnloadSound(rotateSound);
	UnloadSound(enemyRotateSound);
	UnloadSound(detonateSound);
	UnloadSound(lockSound);
	UnloadSound(loseSound);
	UnloadSound(undoRotateSound);
	UnloadSound(tetrisSound);
	UnloadSound(oneLineClearSound);
	UnloadSound(twoLineClearSound);
	UnloadSound(threeLineClearSound);
	UnloadSound(fourLineClearSound);
	UnloadSound(enemySpawn);
	UnloadMusicStream(music);
	CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
	if (blocksQueue.empty())
	{
		blocksQueue = GetAllBlocks();
	}

	int randomIndex = rand() % blocksQueue.size();
	Block block = blocksQueue[randomIndex];
	blocksQueue.erase(blocksQueue.begin() + randomIndex);

	return block;
}

Block Game::GetRandomEnemy()
{
	if (enemiesQueue.empty())
	{
		enemiesQueue = GetAllEnemies();
	}

	int count = 0;
	for (Block item : enemiesQueue)
	{
		count++;
	}

	int randomIndex = rand() % enemiesQueue.size();
	Block enemy = enemiesQueue[randomIndex];
	enemiesQueue.erase(enemiesQueue.begin() + randomIndex);

	return enemy;
}

std::vector<Block> Game::GetAllBlocks()
{
	return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock(), BombBlock()};
}

char Game::GetRandomSpawnState()
{
	
	int randomNumber = GetRandomValue(1, 3);

	if (randomNumber == 1)
	{
		
		return 'L';
	}

	else if (randomNumber == 2)
	{
		return 'R';
	}
	
	return 'B';
}

std::vector<Block> Game::GetAllEnemies()
{
	int upperBound = 4; //grid.GetRows() / 3;
	int lowerBound = grid.GetRows() - 3; // - (grid.GetRows() / 4);

	
	return {EnemyJ(GetRandomValue(upperBound, lowerBound), GetRandomSpawnState()),
			EnemyO(GetRandomValue(upperBound, lowerBound), GetRandomSpawnState()),
			EnemyL(GetRandomValue(upperBound, lowerBound), GetRandomSpawnState()),
			EnemyT(GetRandomValue(upperBound, lowerBound), GetRandomSpawnState()),
			EnemyS(GetRandomValue(upperBound, lowerBound), GetRandomSpawnState()),
			EnemyZ(GetRandomValue(upperBound, lowerBound), GetRandomSpawnState()),
			EnemyI(GetRandomValue(upperBound, lowerBound), GetRandomSpawnState()),
			EnemyWall() };
	
}

void Game::Draw()
{
	grid.Draw();
	currentBlock.Draw(11, 11);

	if (enemyIsActive)
	{
		if (!IsEnemyOutside())
		{
			currentEnemy.Draw(11, 11);
		}
		
	}

	switch (nextBlock.id)
	{
	case 3:
		nextBlock.Draw(255, 290);
		break;

	case 4:
		nextBlock.Draw(255, 280);
		break;

	case 7:
		nextBlock.Draw(245, 280);
		break;

	case 8:
		nextBlock.Draw(240, 290);
		break;

	default:
		nextBlock.Draw(270, 270);
	}
}

void Game::HandleInput()
{
	int keyPressed = GetKeyPressed();

	if (gameOver && keyPressed == KEY_ENTER)
	{
		Reset();
		gameOver = false;
	}

	if (IsKeyDown(KEY_S) && frameCount >= moveCooldownFrames)
	{
		MoveBlockDown(1);
		frameCount = 0;
	}

	switch (keyPressed)
	{
	case KEY_A:
		MoveBlockLeft(1);
		break;

	case KEY_D:
		MoveBlockRight(1);
		break;

		/*
	case KEY_S:
		MoveBlockDown(1);
		break;
		*/

	case KEY_W:
		RotateBlock();
		break;
	}

}

void Game::MoveBlockLeft(int offset)
{
	if (!gameOver)
	{
		currentBlock.Move(0, -offset);

		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Move(0, offset);
		}
	}
}

void Game::MoveBlockRight(int offset)
{
	if (!gameOver)
	{
		currentBlock.Move(0, offset);

		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Move(0, -offset);
		}
	}
}

void Game::MoveBlockDown(int offset)
{
	if (!gameOver)
	{
		currentBlock.Move(offset, 0);

		if (IsBlockOutside() || BlockFits() == false)
		{
			currentBlock.Move(-1, 0);

			if (currentBlock.id != 8)
			{
				LockBlock();
			}

			else
			{
				std::vector<Position> tiles = currentBlock.GetCellPositions();

				for (Position item : tiles)
				{
					DetonateBlock(item.row, item.col);
					PlaySound(detonateSound);
				}
			}

		}
	}
}

void Game::DetonateBlock(int row, int col)
{
	grid.ClearCell(row, col);
	grid.ClearCell(row + 1, col);
	grid.ClearCell(row - 1, col);
	grid.ClearCell(row, col + 1);
	grid.ClearCell(row, col - 1);
	grid.ClearCell(row + 1, col + 1);
	grid.ClearCell(row - 1, col - 1);
	grid.ClearCell(row + 1, col - 1);
	grid.ClearCell(row - 1, col + 1);

	currentBlock = nextBlock;
	totalBlocksDropped++;
	canIncreaseSpeed = true;
	nextBlock = GetRandomBlock();
}

void Game::SpawnEnemy()
{
	if (!gameOver)
	{
		enemyIsActive = true;
		currentEnemy = GetRandomEnemy();
		PlaySound(enemySpawn);
	}	
}

void Game::DespawnEnemy()
{
	enemyIsActive = false;
	currentEnemyMoves = 0;
}

void Game::MoveEnemyLeft(int offset)
{
	if (!gameOver)
	{
		currentEnemy.Move(0, -offset);
		currentEnemyMoves++;
	}
}

void Game::MoveEnemyRight(int offset)
{
	if (!gameOver)
	{
		currentEnemy.Move(0, offset);
		currentEnemyMoves++;	

	}
}

void Game::MoveEnemyUp(int offset)
{
	if (!gameOver)
	{
		currentEnemy.Move(-offset, 0);
		currentEnemyMoves++;

	}
}

void Game::MoveEnemyDown(int offset)
{
	if (!gameOver)
	{
		currentEnemy.Move(offset, 0);
		currentEnemyMoves++;

	}
}

void Game::RotateCurrentEnemy()
{
	if (currentEnemy.id != 10 && currentEnemy.id != 16)
	{
		currentEnemy.Rotate();
		PlaySound(enemyRotateSound);
		// play a sound
	}
	
}

void Game::MoveBlockUp(int offset)
{
	if (!gameOver)
	{
		currentBlock.Move(-offset, 0);

		if (IsBlockOutside())
		{
			currentBlock.Move(1, 0);
		}
	}
}

void Game::Reset()
{
	DespawnEnemy();
	grid.Initialize();
	std::vector<Block> blocksQueue = GetAllBlocks();
	std::vector<Block> enemiesQueue = GetAllEnemies();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	score = 0;
	totalBlocksDropped = 1;	
	canIncreaseSpeed = true;
}

void Game::UpdateScore(int linesCleared)
{
	switch (linesCleared)
	{
	case 1:
		score += static_cast<int>(100 * (1 + (totalBlocksDropped * 0.01)));
		PlaySound(oneLineClearSound);
		break;

	case 2:
		score += static_cast<int>(300 * (1 + (totalBlocksDropped * 0.01)));
		PlaySound(twoLineClearSound);
		break;

	case 3:
		score += static_cast<int>(900 * (1 + (totalBlocksDropped * 0.01)));
		PlaySound(threeLineClearSound);
		break;

	case 4:
		score += static_cast<int>(2700 * (1 + (totalBlocksDropped * 0.01)));
		PlaySound(fourLineClearSound);
		PlaySound(tetrisSound);
		break;

	default:
		break;
	}
}



bool Game::IsBlockOutside()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();

	for (Position item : tiles)
	{
		if (grid.IsCellOutside(item.row, item.col))
		{
			return true;
		}
	}

	return false;
}

bool Game::IsEnemyOutside()
{
	std::vector<Position> tiles = currentEnemy.GetCellPositions();

	for (Position item : tiles)
	{
		if (grid.IsCellOutside(item.row, item.col))
		{
			return true;
		}
	}

	return false;
}

char Game::GetCurrentEnemyType()
{
	return currentEnemy.spawnState;
}

void Game::RotateBlock()
{
	if (!gameOver)
	{
		currentBlock.Rotate();

		if (!BlockFits())
		{
			currentBlock.UndoRotate();
			PlaySound(undoRotateSound);
		}

		else if (IsBlockOutside())
		{
			std::vector<Position> tiles = currentBlock.GetCellPositions();

			for (Position item : tiles)
			{
				if (item.col < 0)
				{
					MoveBlockRight(abs(item.col));

					if (IsBlockOutside())									// MoveBlockRight will not move block if BlockFits() == false
					{														// So check if it didn't move (aka its still outside)
						currentBlock.UndoRotate();
						PlaySound(undoRotateSound);
					}

					else
					{
						PlaySound(rotateSound);
					}
				}

				else if (item.col >= grid.GetCols())
				{
					MoveBlockLeft(item.col - (grid.GetCols() - 1));

					if (IsBlockOutside())
					{
						currentBlock.UndoRotate();
						PlaySound(undoRotateSound);
					}

					else
					{
						PlaySound(rotateSound);
					}
				}

				else if (item.row >= grid.GetRows())
				{
					MoveBlockUp(1);
				}
			}
		}

		else
		{
			PlaySound(rotateSound);
		}

	}
}

void Game::LockBlock()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();

	for (Position item : tiles)
	{
		grid.grid[item.row][item.col] = currentBlock.id;
	}

	PlaySound(lockSound);

	currentBlock = nextBlock;
	nextBlock = GetRandomBlock();
	totalBlocksDropped++;
	canIncreaseSpeed = true;

	if (!BlockFits())
	{
		PlaySound(loseSound);
		gameOver = true;
	}

	else
	{
		; // play a lockblock sound
	}

	int rowsCleared = grid.ClearFullRows();

	if (rowsCleared > 0)
	{
		UpdateScore(rowsCleared);
	}


}

bool Game::EnemyCollided()
{
	std::vector<Position> blockTiles = GetCurrentBlockPosition();
	std::vector<Position> enemyTiles = GetCurrentEnemyPosition();

	for (Position blockPos : blockTiles)
	{
		for (Position enemyPos : enemyTiles)
		{
			if (blockPos.col == enemyPos.col && blockPos.row == enemyPos.row)
			{
				return true;
			}
		}
	}

	return false;

}

void Game::CheckCollision()
{
	if (EnemyCollided())
	{
		if (currentBlock.id != 8)
		{
			PlaySound(loseSound);
			gameOver = true;
		}

		else
		{
			DespawnEnemy();
			std::vector<Position> tiles = currentBlock.GetCellPositions();

			for (Position item : tiles)
			{
				DetonateBlock(item.row, item.col);
				PlaySound(detonateSound);
				PlaySound(twoLineClearSound);
			}

			score += static_cast<int>(100 * (1 + (totalBlocksDropped * 0.01)));
		}
		
	}
}

void Game::HandleEnemyMovement()
{
	std::vector<Position> currentEnemyPosition = GetCurrentEnemyPosition();

	// move enemy left / right
	if (currentEnemy.id != 16)
	{
		if (GetCurrentEnemyType() == 'L')
		{
			MoveEnemyRight(1);

			if (currentEnemyMoves == 1)
			{
				MoveEnemyLeft(1);
			}
		}

		else if (GetCurrentEnemyType() == 'R')
		{
			MoveEnemyLeft(1);

			if (currentEnemyMoves == 1)
			{
				MoveEnemyRight(1);
			}
		}

		else if (GetCurrentEnemyType() == 'B')
		{
			MoveEnemyUp(1);

			if (currentEnemyMoves == 1)
			{
				MoveEnemyDown(1);
			}

			for (Position item : currentEnemyPosition) // dont let the block get to the spawn point
			{
				if (item.row <= 4)
				{
					DespawnEnemy();
				}
			}
		}
	}

	else
	{
		HandleWallMovement();
	}

	// despawn enemy
	if (IsEnemyOutside())
	{
		DespawnEnemy();
	}

	// rotate enemy
	if (currentEnemyMoves > 3)
	{
		int randomNumber = GetRandomValue(1, 2);

		if (randomNumber == 2) // && game.GetCurrentEnemyId != 16 or somehting
		{
			RotateCurrentEnemy();
		}

	}
}

void Game::HandleWallMovement()
{
	if (GetCurrentEnemyType() == 'L')
	{
		UpdatePastHalf();

		if (!currentEnemy.pastHalf)
		{
			MoveEnemyRight(1);

			if (currentEnemyMoves == 1)
			{
				MoveEnemyLeft(1);
			}
		}

		else
		{
			MoveEnemyLeft(1);
		}
		
	}

	else if (GetCurrentEnemyType() == 'R')
	{
		UpdatePastHalf();

		if (!currentEnemy.pastHalf)
		{
			MoveEnemyLeft(1);

			if (currentEnemyMoves == 1)
			{
				MoveEnemyRight(1);
			}
		}

		else
		{
			MoveEnemyRight(1);
		}
	}
}

void Game::UpdatePastHalf()
{
	std::vector<Position> currentEnemyPosition = GetCurrentEnemyPosition();

	if (currentEnemy.spawnState == 'L')
	{
		for (Position item : currentEnemyPosition)
		{
			if (item.col >= 4)
			{
				currentEnemy.pastHalf = true;
			}
		}
	}

	else
	{
		for (Position item : currentEnemyPosition)
		{
			if (item.col <= 5)
			{
				currentEnemy.pastHalf = true;
			}
		}
	}

}

std::vector<Position> Game::GetCurrentEnemyPosition()
{
	return currentEnemy.GetCellPositions();
}

std::vector<Position> Game::GetCurrentBlockPosition()
{
	return currentBlock.GetCellPositions();
}


bool Game::BlockFits()
{
	std::vector<Position> tiles = currentBlock.GetCellPositions();

	for (Position item : tiles)
	{
		if (!grid.IsCellEmpty(item.row, item.col))
		{
			return false;
		}
	}

	return true;
}
