
#include <stdlib.h>
#include <crtdbg.h>

#include <raylib.h>

#include <time.h>

#include <iostream>

#include "world.hpp"
#include "player.hpp"
#include "enemy.hpp"

#include "collisiondetection.hpp"

#include "math.hpp"
#include "myrectangle.hpp"
#include "myconvexpolygon.hpp"

int main(int argc, char* argv[])
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 640;
    int screenHeight = 800;

    srand(time(0));

    World game(screenWidth, screenHeight);

    InitWindow(screenWidth, screenHeight, "minestorm");
    SetTargetFPS(60);

    Texture2D texBackGround = LoadTexture("Assets/minestorm_background.png");
    Texture2D texHUD = LoadTexture("Assets/minestorm_forground.png");

    float deltaTime;
    float currentTime;
    float previousTime = 0.f;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (game.m_menu == MENU)
        {
            if (IsKeyPressed(KEY_F))
            {
                game.m_playerCount = 1;
                game.m_players.push_back(new Player(game.m_center));
                game.m_menu = ONE;
            }
            else if (IsKeyPressed(KEY_K))
            {
                game.m_playerCount = 2;
                game.m_players.push_back(new Player({ game.m_center.x - 100, game.m_center.y }));
                game.m_players.push_back(new Player({ game.m_center.x + 100, game.m_center.y }));
                (*(game.m_players.end() - 1))->setSecondPlayer();
                game.m_menu = TWO;
            }
        }

        deltaTime = GetFrameTime() * 50;
        currentTime = GetTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        //TODO : move all to a function gameLoop();

        //TODO : spawning enemies
        //TODO : advanced enemy types
        //TODO : free memory leaks
            //https://www.fluentcpp.com/2018/09/18/how-to-remove-pointers-from-a-vector-in-cpp/
            //https://www.oreilly.com/library/view/c-cookbook/0596007612/ch06s05.html

        //TODO : destroy all enemies when game over

        DrawTexture(texBackGround, 0, 0, RAYWHITE);

        if (game.m_menu == MENU)
        {
            game.displayMenu();
        }
        else if (game.m_menu == ONE)
        {
            game.displayHUD();
            game.gameLoopSingleplayer(deltaTime, currentTime);
        }
        else if (game.m_menu == TWO)
        {
            game.displayHUD();
            game.gameLoopMultiplayer(deltaTime, currentTime);
        }
        else if (game.m_menu == OVER)
        {
            game.displayGameOver();
        }

        printf("X : %d, Y : %d\r", GetMouseX(), GetMouseY());

        DrawTexture(texHUD, 0, 0, RAYWHITE);

        EndDrawing();
    }

    UnloadTexture(texHUD);
    UnloadTexture(texBackGround);

    CloseWindow();        // Close window and OpenGL context

    return 0;
}