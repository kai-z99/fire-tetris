#include <iostream>
#include "raylib.h"
#include "game.h"
#include "colors.h"



double lastDropTime = 0;
double dropInterval = 0.5;

double lastEnemyMoveTime = 0;
double enemyMoveInterval = 0.5;


bool DropTriggered(double interval)
{
    double currentTime = GetTime();

    if (currentTime - lastDropTime >= interval)
    {
        lastDropTime = currentTime;
        return true;
    }
    return false;
}

bool EnemyMoveTriggered(double interval)
{
    double currentTime = GetTime();

    if (currentTime - lastEnemyMoveTime >= interval)
    {
        lastEnemyMoveTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    //-------------------
    // INITIALIZATION
    //-------------------

    InitWindow(500, 620, "BlazeTetris");
    SetTargetFPS(60);
    HideCursor();
    DisableCursor();
 
    Font font = LoadFontEx("Fonts/MinecraftRegular-Bmg3.otf", 64, 0, 0);
    
    Game game = Game();
    

    //-------------------
    // GAME LOOP
    //-------------------

    while (!WindowShouldClose())
    {
        
        UpdateMusicStream(game.music);
        game.frameCount++;

        // Check for enemy collision
        if (game.enemyIsActive && game.gameOver == false)
        {
            game.CheckCollision();
        }
            
        game.HandleInput();
      
        if (DropTriggered(dropInterval))
        {
            game.MoveBlockDown(1);
        }

        // Enemy Movement
        if (EnemyMoveTriggered(enemyMoveInterval) && game.enemyIsActive && game.gameOver == false)// make this in game called handle enemy Movement
        {
            game.HandleEnemyMovement();
        }

        if (game.totalBlocksDropped % 8 == 0 && game.canIncreaseSpeed && dropInterval > 0.2)
        {
            dropInterval -= 0.0175;
            game.canIncreaseSpeed = false;        
        }

        if (game.totalBlocksDropped % 8 == 0 && !game.enemyIsActive)
        {
            game.SpawnEnemy();
        }

        if (game.gameOver)
        {
            lastDropTime = 0;
            dropInterval = 0.5;
            lastEnemyMoveTime = 0;
            enemyMoveInterval = 0.5;
        }

        //-------------------
        // DRAWING
        //-------------------

        BeginDrawing();

        ClearBackground(darkOrange);
        DrawTextEx(font, "Score", { 355, 15 }, 38, 2, WHITE);   
        DrawTextEx(font, "Next", { 370, 175 }, 38, 2, WHITE);
        DrawRectangleRounded({ 320, 55, 170, 60 }, static_cast<float>(0.3), 6, ORANGE);      // score rectangle
        DrawRectangleRounded({ 320, 215, 170, 180 }, static_cast<float>(0.3), 6, ORANGE);    // next block rectangle

        if (game.gameOver)
        {
            DrawTextEx(font, "Game Over!", { 320, 450 }, 38, 2, BLUE);
            DrawTextEx(font, " Press Enter\nto Play Again", { 338, 500 }, 20, 2, green);    
        }

        char scoreText[10];
        sprintf_s(scoreText, "%d", game.score);                                              // Voodoo magic alignment?? XD
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
        DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        
        game.Draw();
        EndDrawing();

    }

    CloseWindow();
}

