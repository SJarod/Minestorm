#include "world.hpp"

#include "math.hpp"
#include "collisiondetection.hpp"

#include "player.hpp"
#include "bullet.hpp"

World::World()
{

}

World::World(int screenWidth, int screenHeight)
{
    m_gameSpeed = 1.f;

    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

	m_center.x = (float)screenWidth / 2;
	m_center.y = (float)screenHeight / 2;
}

World::~World()
{
    m_players.clear();
    m_enemies.clear();
}

int World::getScreenWidth(int dif)
{
    return screenWidth + dif;
}

int World::getScreenHeight(int dif)
{
    return screenHeight + dif;
}

void World::displayMenu()
{
    DrawText("MINESTORM",               m_center.x - 120,    m_center.y - 100,           40,     WHITE);
    DrawText("Press 'F':",              m_center.x - 150,    m_center.y + 10 + 0 * 50,   20,     BLUE);
    DrawText("Solo mode",               m_center.x,          m_center.y + 10 + 0 * 50,   20,     BLUE);
    DrawText("Press 'K':",              m_center.x - 150,    m_center.y + 10 + 1 * 50,   20,     GREEN);
    DrawText("Two players mode",        m_center.x,          m_center.y + 10 + 1 * 50,   20,     GREEN);
    DrawText("Press 'Esc':",            m_center.x - 150,    m_center.y + 10 + 2 * 50,   20,     RED);
    DrawText("Exit",                    m_center.x,          m_center.y + 10 + 2 * 50,   20,     RED);
}

void World::displayHUD()
{
    DrawText("PLAYER ONE", 85, 80, 20, BLUE);

    if (m_playerCount > 0)
        for (int i = 0; i < m_players[0]->getHealth(); ++i)
        {
            int x = 100;

            if (m_players[0]->getId() == 2)
                x = 435;

            m_players[0]->draw({ x + (float)i * 30, 120 }, m_players[0]->m_color);
        }

    DrawText("Rotate : 'D' and 'G'", 85, 150, 10, LIGHTGRAY);
    DrawText("Move : 'R'", 85, 160, 10, LIGHTGRAY);
    DrawText("Shoot : 'F'", 85, 170, 10, LIGHTGRAY);
    DrawText("Teleport : 'E' or 'T'", 85, 180, 10, LIGHTGRAY);

    if (m_menu == TWO)
    {
        DrawText("PLAYER TWO", 420, 80, 20, RED);

        if (m_playerCount == 2)
            for (int i = 0; i < m_players[1]->getHealth(); ++i)
            {
                m_players[1]->draw({ 435 + (float)i * 30, 120 }, m_players[1]->m_color);
            }

        DrawText("Rotate : 'J' and 'L'", 420, 150, 10, LIGHTGRAY);
        DrawText("Move : 'I'", 420, 160, 10, LIGHTGRAY);
        DrawText("Shoot : 'K'", 420, 170, 10, LIGHTGRAY);
        DrawText("Teleport : 'U' or 'O'", 420, 180, 10, LIGHTGRAY);
    }
}

void World::displayGameOver()
{
    DrawText("GAME OVER",               m_center.x - 120,    m_center.y - 50,            40,    WHITE);
    DrawText("Score:",                  m_center.x - 150,    m_center.y + 10 + 0 * 50,   20,    GREEN);
    DrawText(TextFormat("%d", m_score), m_center.x,          m_center.y + 10 + 0 * 50,   20,    GREEN);
    DrawText("Press 'Enter':",          m_center.x - 150,    m_center.y + 10 + 1 * 50,   20,    BLUE);
    DrawText("Back to main menu",       m_center.x,          m_center.y + 10 + 1 * 50,   20,    BLUE);

    if (IsKeyPressed(KEY_ENTER))
    {
        m_menu = MENU;
    }
}

void World::gameLoopSingleplayer(float deltaTime, float currentTime)
{
    if (m_playerCount > 0)
    {
        m_players[0]->setInputs();
    }

    for (auto& players : m_players)
    {
        int moving = players->m_inputs.movingForward * 2 - 1;  //true : moving = 1, false : moving = -1
        players->m_thrust += moving / 10.f * deltaTime * m_gameSpeed;
        players->m_thrust = Math::clamp(players->m_thrust, 0, 7);

        for (auto& polygons : players->m_shape.polygons)
            polygons.angle += (players->m_inputs.rotateLeft - players->m_inputs.rotateRight) * 4 * deltaTime * m_gameSpeed;

        playerOnEdge();

        for (auto& enemies : m_enemies)
        {
            enemyOnEdge();
        }

        players->update(deltaTime, m_gameSpeed);
        players->move(*this, deltaTime);

        for (auto& enemies : m_enemies)
        {
            enemies->move(*this, deltaTime);
        }

        if (players->m_inputs.shooting)
        {
            if (currentTime - players->m_shootingTime >= 0.05f / deltaTime && m_gameSpeed > 0.f)
            {
                players->m_shootingTime = GetTime();
                players->shoot(players->m_shootingTime);
            }
        }

        int index = 0;
        for (auto& enemies : m_enemies)
        {
            if (Collide::cBulletEnemy(*players, *enemies))
            {
                m_enemies.erase(m_enemies.begin() + index);
            }
            ++index;
        }

        for (auto& bullets : players->m_bullet)
        {
            if (currentTime - bullets.m_lifeTime >= 1.f / deltaTime && m_gameSpeed > 0.f)
            {
                players->m_bullet.erase(players->m_bullet.begin());
            }

            bullets.move(deltaTime, m_gameSpeed);
            bulletOnEdge();
            bullets.draw(YELLOW);
        }

        players->draw(WHITE);
    }

    for (auto& players : m_players)
    {
        int index = 0;
        for (auto& enemies : m_enemies)
        {
            if (Collide::cPlayerEnemy(*players, *enemies))
            {
                enemies->draw(RED);
                m_enemies.erase(m_enemies.begin() + index);

                if (players->isHit())
                {
                    players->~Player();
                    m_players.pop_back();
                    --m_playerCount;
                }
            }
            else
            {
                enemies->draw(GREEN);
            }
            ++index;
        }
    }

    if (IsKeyPressed(KEY_F1))
    {
        m_enemies.push_back(new FloatingMine(*this));
        (*(m_enemies.end() - 1))->teleport(*this);
    }
    if (IsKeyPressed(KEY_F2))
    {
        m_enemies.push_back(new FireballMine(*this));
        (*(m_enemies.end() - 1))->teleport(*this);
    }
    if (IsKeyPressed(KEY_F3))
    {
        m_enemies.push_back(new MagneticMine(*this));
        (*(m_enemies.end() - 1))->teleport(*this);
    }
    if (IsKeyPressed(KEY_F4))
    {
        m_enemies.push_back(new MagneticFireballMine(*this));
        (*(m_enemies.end() - 1))->teleport(*this);
    }
    if (IsKeyPressed(KEY_F5))
    {
        m_enemies.push_back(new Minelayer(*this));
        (*(m_enemies.end() - 1))->teleport(*this);
    }
    if (IsKeyPressed(KEY_P))
    {
        m_gameSpeed = fabsf(m_gameSpeed - 1);
    }

    if (m_playerCount == 0)
    {
        m_menu = OVER;
    }
}

void World::gameLoopMultiplayer(float deltaTime, float currentTime)
{
    if (m_playerCount > 0)
    {
        m_players[0]->setInputs();

        if (m_playerCount == 2)
        {
            m_players[1]->setInputs();
        }
    }

    for (auto& players : m_players)
    {
        int moving = players->m_inputs.movingForward * 2 - 1;  //true : moving = 1, false : moving = -1
        players->m_thrust += moving / 10.f * deltaTime * m_gameSpeed;
        players->m_thrust = Math::clamp(players->m_thrust, 0, 7);

        for (auto& polygons : players->m_shape.polygons)
            polygons.angle += (players->m_inputs.rotateLeft - players->m_inputs.rotateRight) * 4 * deltaTime * m_gameSpeed;

        playerOnEdge();

        for (auto& enemies : m_enemies)
        {
            enemyOnEdge();
        }

        players->update(deltaTime, m_gameSpeed);
        players->move(*this, deltaTime);

        for (auto& enemies : m_enemies)
        {
            enemies->move(*this, deltaTime);
        }

        if (players->m_inputs.shooting)
        {
            if (currentTime - players->m_shootingTime >= 0.05f / deltaTime && m_gameSpeed > 0.f)
            {
                players->m_shootingTime = GetTime();
                players->shoot(players->m_shootingTime);
            }
        }

        int index = 0;
        for (auto& enemies : m_enemies)
        {
            if (Collide::cBulletEnemy(*players, *enemies))
            {
                m_enemies.erase(m_enemies.begin() + index);
            }
            ++index;
        }

        for (auto& bullets : players->m_bullet)
        {
            if (currentTime - bullets.m_lifeTime >= 1.f / deltaTime && m_gameSpeed > 0.f)
            {
                players->m_bullet.erase(players->m_bullet.begin());
            }

            bullets.move(deltaTime, m_gameSpeed);
            bulletOnEdge();
            bullets.draw(YELLOW);
        }
    }

    if (m_playerCount > 0)
    {
        m_players[0]->draw(m_players[0]->m_color);

        if (m_playerCount == 2)
            m_players[1]->draw(m_players[1]->m_color);
    }

    int pindex = 0;
    for (auto& players : m_players)
    {
        int index = 0;
        for (auto& enemies : m_enemies)
        {
            if (Collide::cPlayerEnemy(*players, *enemies))
            {
                enemies->draw(RED);
                m_enemies.erase(m_enemies.begin() + index);

                if (players->isHit())
                {
                    players->~Player();
                    m_players.erase(m_players.begin() + pindex);
                    --m_playerCount;
                }
            }
            else
            {
                enemies->draw(GREEN);
            }
            ++index;
        }

        ++pindex;
    }

    if (m_playerCount == 2)
    {
        if (Collide::cPlayerPlayer(*m_players[0], *m_players[1]))
        {
            if (m_players[1]->isHit())
            {
                m_players[1]->~Player();
                m_players.pop_back();
                --m_playerCount;
            }
            if (m_players[0]->isHit())
            {
                m_players[0]->~Player();
                m_players.erase(m_players.begin());
                --m_playerCount;
            }
        }
    }

    if (IsKeyPressed(KEY_F1))
    {
        m_enemies.push_back(new FloatingMine(*this));
        (*(m_enemies.end() - 1))->teleport(*this);
    }
    if (IsKeyPressed(KEY_F2))
    {
        m_enemies.push_back(new FireballMine(*this));
        (*(m_enemies.end() - 1))->teleport(*this);
    }
    if (IsKeyPressed(KEY_F3))
    {
        m_enemies.push_back(new MagneticMine(*this));
        (*(m_enemies.end() - 1))->teleport(*this);
    }
    if (IsKeyPressed(KEY_F4))
    {
        m_enemies.push_back(new MagneticFireballMine(*this));
        (*(m_enemies.end() - 1))->teleport(*this);
    }
    if (IsKeyPressed(KEY_F5))
    {
        m_enemies.push_back(new Minelayer(*this));
        (*(m_enemies.end() - 1))->teleport(*this);
    }
    if (IsKeyPressed(KEY_P))
    {
        m_gameSpeed = fabsf(m_gameSpeed - 1);
    }

    if (m_playerCount == 0)
    {
        m_menu = OVER;
    }
}

void World::playerOnEdge()
{
    for (auto& players : m_players)
        for (auto& polygons : players->m_shape.polygons)
        {
            if (polygons.center.x < 40)
            {
                polygons.center.x = screenWidth - 40;
            }
            if (polygons.center.x > screenWidth - 40)
            {
                polygons.center.x = 40;
            }
            if (polygons.center.y < 40)
            {
                polygons.center.y = screenHeight - 60;
            }
            if (polygons.center.y > screenHeight - 60)
            {
                polygons.center.y = 40;
            }
        }
}

void World::bulletOnEdge()
{
    for (auto& players : m_players)
        for (auto& bullet : players->m_bullet)
        {
            if (bullet.m_shape.center.x < 40)
            {
                bullet.m_shape.center.x = screenWidth - 40;
            }
            if (bullet.m_shape.center.x > screenWidth - 40)
            {
                bullet.m_shape.center.x = 40;
            }
            if (bullet.m_shape.center.y < 40)
            {
                bullet.m_shape.center.y = screenHeight - 60;
            }
            if (bullet.m_shape.center.y > screenHeight - 60)
            {
                bullet.m_shape.center.y = 40;
            }
        }
}

void World::enemyOnEdge()
{
    for (auto& enemies : m_enemies)
        for (auto& polygons : enemies->m_shape.polygons)
        {
            for (int i = 0; i < polygons.count; ++i)
            {
                polygons.points[i] -= polygons.center;
            }

            if (polygons.center.x < 40)
            {
                polygons.center.x = screenWidth - 40;
            }
            if (polygons.center.x > screenWidth - 40)
            {
                polygons.center.x = 40;
            }
            if (polygons.center.y < 40)
            {
                polygons.center.y = screenHeight - 60;
            }
            if (polygons.center.y > screenHeight - 60)
            {
                polygons.center.y = 40;
            }

            for (int i = 0; i < polygons.count; ++i)
            {
                polygons.points[i] += polygons.center;
            }
        }
}