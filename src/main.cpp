
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

    game.m_players.push_back(Player(game));

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

        for (auto& players : game.m_players)
        {
            //TODO : move moving variable in player.cpp,Player::move();
            moving = IsKeyDown(KEY_R) * 2 - 1;  //true : moving = 1, false : moving = -1
            players.m_thrust += moving / 10.f * deltaTime * game.m_gameSpeed;
            players.m_thrust = Math::clamp(players.m_thrust, 0, 7);

            for (auto& polygons : players.m_shape.polygons)
                polygons.angle += (IsKeyDown(KEY_D) - IsKeyDown(KEY_G)) * 4 * deltaTime * game.m_gameSpeed;

            game.playerOnEdge(players);

            for (auto& enemies : game.m_enemies)
            {
                game.enemyOnEdge(enemies);
            }

            players.update(deltaTime, game.m_gameSpeed);
            players.move(game, deltaTime, game.m_gameSpeed);

            for (auto& enemies : game.m_enemies)
            {
                enemies.move(game, deltaTime, game.m_gameSpeed);
            }

            if (IsKeyDown(KEY_F))
            {
                if (currentTime - previousTime >= 0.1f / deltaTime)
                {
                    previousTime = GetTime();
                    players.shoot(previousTime);
                }
            }

            int index = 0;
            for (auto& enemies : game.m_enemies)
            {
                if (Collide::cBulletEnemy(players, enemies))
                {
                    game.m_enemies.erase(game.m_enemies.begin() + index);
                }
                ++index;
            }

            for (auto& bullets : players.m_bullet)
            {
                if (currentTime - bullets.m_lifeTime >= 1.f / deltaTime)
                {
                    players.m_bullet.erase(players.m_bullet.begin());
                }

                bullets.move(deltaTime, game.m_gameSpeed);
                game.bulletOnEdge(bullets);
                bullets.draw(YELLOW);
            }

            index = 0;
            for (auto& enemies : game.m_enemies)
            {
                if (Collide::cPlayerEnemy(players, enemies))
                {
                    enemies.draw(RED);
                    game.m_enemies.erase(game.m_enemies.begin() + index);
                    //TODO : delete player
                    game.m_players.pop_back();
                }
                else
                {
                    enemies.draw(GREEN);
                }
                ++index;
            }

            players.draw(WHITE);
        }

        if (IsKeyPressed(KEY_KP_1))
        {
            game.m_enemies.push_back(FloatingMine(game));
            (game.m_enemies.end() - 1)->teleport(game);
        }
        else if (IsKeyPressed(KEY_KP_2))
        {
            game.m_enemies.push_back(FireballMine(game));
            (game.m_enemies.end() - 1)->teleport(game);
        }
        else if (IsKeyPressed(KEY_KP_3))
        {
            game.m_enemies.push_back(MagneticMine(game));
            (game.m_enemies.end() - 1)->teleport(game);
        }
        else if (IsKeyPressed(KEY_KP_4))
        {
            game.m_enemies.push_back(MagneticFireballMine(game));
            (game.m_enemies.end() - 1)->teleport(game);
        }
        else if (IsKeyPressed(KEY_KP_5))
        {
            game.m_enemies.push_back(Minelayer(game));
            (game.m_enemies.end() - 1)->teleport(game);
        }
        else if (IsKeyPressed(KEY_ENTER))
        {
            game.m_players.push_back(Player(game));
            (game.m_players.end() - 1)->teleport(game);
        }

        DrawTexture(texHUD, 0, 0, RAYWHITE);

        EndDrawing();
    }

    UnloadTexture(texHUD);
    UnloadTexture(texBackGround);

    CloseWindow();        // Close window and OpenGL context

    return 0;
}