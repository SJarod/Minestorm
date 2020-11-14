
#include <raylib.h>

#include <iostream>

#include "world.hpp"
#include "player.hpp"
#include "enemy.hpp"

#include "math.hpp"
#include "myrectangle.hpp"
#include "myconvexpolygon.hpp"

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 640;
    int screenHeight = 800;

    World game(screenWidth, screenHeight);

    Player player(game);
    Enemy enemy(game);

    InitWindow(screenWidth, screenHeight, "minestorm");
    SetTargetFPS(60);

    int moving = 0;

    Texture2D texBackGround = LoadTexture("Assets/minestorm_background.png");
    Texture2D texHUD = LoadTexture("Assets/minestorm_forground.png");

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(texBackGround, 0, 0, RAYWHITE);

        //TODO : move moving variable in player.cpp,Player::move();
        moving = IsKeyDown(KEY_R) * 2 - 1;  //true : moving = 1, false : moving = -1
        player.thrust += moving / 10.f;
        player.thrust = Math::clamp(player.thrust, 0, 7);

        player.shape.polygons[0].angle += (IsKeyDown(KEY_D) - IsKeyDown(KEY_G)) * 4;

        //TODO : move edge function in world.hpp and .cpp
        if (player.shape.polygons[0].center.x < 40)
        {
            player.shape.polygons[0].center.x = screenWidth - 40;
        }
        if (player.shape.polygons[0].center.x > screenWidth - 40)
        {
            player.shape.polygons[0].center.x = 40;
        }
        if (player.shape.polygons[0].center.y < 40)
        {
            player.shape.polygons[0].center.y = screenHeight - 60;
        }
        if (player.shape.polygons[0].center.y > screenHeight - 60)
        {
            player.shape.polygons[0].center.y = 40;
        }

        player.update();
        player.move();

        //TODO: SAT

        player.draw();
        enemy.draw();

        DrawTexture(texHUD, 0, 0, RAYWHITE);

        EndDrawing();
    }

    UnloadTexture(texHUD);
    UnloadTexture(texBackGround);

    CloseWindow();        // Close window and OpenGL context

    return 0;
}