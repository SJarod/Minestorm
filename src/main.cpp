
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
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 640;
    int screenHeight = 800;

    srand(time(0));

    World game(screenWidth, screenHeight);

    //TODO : menu

    //TODO : move player and enemy to class World (std::vector)
    Player player(game);
    MagneticFireballMine enemy(game);
    //FireballMine enemy2(game);
    //MagneticMine enemy3(game);
    //MagneticFireballMine enemy4(game);
    //Minelayer enemy5(game);

    InitWindow(screenWidth, screenHeight, "minestorm");
    SetTargetFPS(60);

    int moving = 0;

    Texture2D texBackGround = LoadTexture("Assets/minestorm_background.png");
    Texture2D texHUD = LoadTexture("Assets/minestorm_forground.png");

    float deltaTime;
    float currentTime;
    float previousTime = 0.f;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        deltaTime = GetFrameTime() * 50;
        currentTime = GetTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        //TODO : move all to a function gameLoop();

        DrawTexture(texBackGround, 0, 0, RAYWHITE);

        //TODO : move moving variable in player.cpp,Player::move();
        moving = IsKeyDown(KEY_R) * 2 - 1;  //true : moving = 1, false : moving = -1
        player.m_thrust += moving / 10.f * deltaTime;
        player.m_thrust = Math::clamp(player.m_thrust, 0, 7);

        for (auto& polygons : player.m_shape.polygons)
            polygons.angle += (IsKeyDown(KEY_D) - IsKeyDown(KEY_G)) * 4 * deltaTime;

        game.playerOnEdge(player);

        player.update(deltaTime);
        player.move(game, deltaTime);

        if (IsKeyDown(KEY_F))
        {
            if (currentTime - previousTime >= 0.1f / deltaTime)
            {
                previousTime = GetTime();
                player.shoot(previousTime);
            }
        }

        Collide::cBulletEnemy(player, enemy);
        //Collide::cBulletEnemy(player, enemy2);
        //Collide::cBulletEnemy(player, enemy3);
        //Collide::cBulletEnemy(player, enemy4);
        //Collide::cBulletEnemy(player, enemy5);

        for (auto& bullets : player.m_bullet)
        {
            if (currentTime - bullets.m_lifeTime >= 1.f / deltaTime)
            {
                player.m_bullet.erase(player.m_bullet.begin());
            }

            bullets.move(deltaTime);
            game.bulletOnEdge(bullets);
            bullets.draw(YELLOW);
        }

        if (Collide::cPlayerEnemy(player, enemy))
        {
            player.draw(RED);
            enemy.draw(RED);
        }
        else
        {
            player.draw(GREEN);
            enemy.draw(GREEN);
        }

        //enemy2.draw(BLUE);
        //enemy3.draw(BLUE);
        //enemy4.draw(BLUE);
        //enemy5.draw(BLUE);

        DrawTexture(texHUD, 0, 0, RAYWHITE);

        EndDrawing();
    }

    UnloadTexture(texHUD);
    UnloadTexture(texBackGround);

    CloseWindow();        // Close window and OpenGL context

    return 0;
}