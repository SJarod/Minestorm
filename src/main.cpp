
#include <raylib.h>

#include <iostream>

#include "math.hpp"
#include "myrectangle.hpp"

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 640;
    int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    MyRectangle rect;
    rect.center.x = screenWidth / 2;
    rect.center.y = screenHeight / 2;

    Texture2D texBackGround = LoadTexture("Assets/minestorm_background.png");
    Texture2D texHUD = LoadTexture("Assets/minestorm_forground.png");

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(texBackGround, 0, 0, RAYWHITE);

        DrawTexture(texHUD, 0, 0, RAYWHITE);

        rect.center.x += (IsKeyDown(KEY_G) - IsKeyDown(KEY_D)) * 4;
        rect.center.y += (IsKeyDown(KEY_F) - IsKeyDown(KEY_R)) * 4;

        rect.center.x = Math::clamp(rect.center.x, 80, 560);
        rect.center.y = Math::clamp(rect.center.y, 100, 636);

        DrawRectangleRec(rect, RED);

        EndDrawing();
    }

    UnloadTexture(texHUD);
    UnloadTexture(texBackGround);

    CloseWindow();        // Close window and OpenGL context

    return 0;
}