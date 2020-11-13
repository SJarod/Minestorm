
#include <raylib.h>

#include <iostream>

#include "world.hpp"
#include "player.hpp"

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

    InitWindow(screenWidth, screenHeight, "minestorm");
    SetTargetFPS(60);

    MyRectangle rect;
    rect.center.x = game.center.x;
    rect.center.y = game.center.y;

    int moving = 0.f;

    Texture2D texBackGround = LoadTexture("Assets/minestorm_background.png");
    Texture2D texHUD = LoadTexture("Assets/minestorm_forground.png");

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(texBackGround, 0, 0, RAYWHITE);

        moving = IsKeyDown(KEY_R) * 2 - 1;  //true : moving = 1, false : moving = -1
        player.thrust += moving / 10.f;
        player.thrust = Math::clamp(player.thrust, 0, 7);

        player.shape.angle += (IsKeyDown(KEY_D) - IsKeyDown(KEY_G)) * 4;

        //player.shape.center.x = Math::clamp(player.shape.center.x, 80, 560);
        //player.shape.center.y = Math::clamp(player.shape.center.y, 100, 636);

        if (player.shape.center.x < 40)
        {
            player.shape.center.x = screenWidth - 40;
        }
        if (player.shape.center.x > screenWidth - 40)
        {
            player.shape.center.x = 40;
        }
        if (player.shape.center.y < 40)
        {
            player.shape.center.y = screenHeight - 60;
        }
        if (player.shape.center.y > screenHeight - 60)
        {
            player.shape.center.y = 40;
        }

        player.update();
        player.move();

        //TODO: SAT

        //std::cout << player.movement.x << std::endl;
        //std::cout << player.movement.y << std::endl;
        //std::cout << player.shape.angle << std::endl;

        player.draw();

        // DrawRectangleRec(rect, RED);

        DrawTexture(texHUD, 0, 0, RAYWHITE);

        EndDrawing();
    }

    UnloadTexture(texHUD);
    UnloadTexture(texBackGround);

    CloseWindow();        // Close window and OpenGL context

    return 0;
}