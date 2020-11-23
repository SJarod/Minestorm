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

    m_spawnPoint = new MyVector2[14];
}

World::~World()
{
    m_players.clear();
    m_enemies.clear();

    delete[] m_spawnPoint;
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
    {
        for (int i = 0; i < m_players[0]->getHealth(); ++i)
        {
            int x = 100;

            if (m_players[0]->getId() == 2)
                x = 435;

            m_players[0]->draw({ x + (float)i * 30, 120 }, m_players[0]->m_color);
        }
    }

    DrawText("Rotate : 'D' and 'G'", 85, 150, 10, LIGHTGRAY);
    DrawText("Move : 'R'", 85, 160, 10, LIGHTGRAY);
    DrawText("Shoot : 'F'", 85, 170, 10, LIGHTGRAY);
    DrawText("Teleport : 'E' or 'T'", 85, 180, 10, LIGHTGRAY);

    DrawText(TextFormat("LEVEL : %d", m_level), m_center.x - 55, 80, 20, WHITE);
    DrawText(TextFormat("SCORE : %d", m_score), m_center.x - 55, 100, 20, WHITE);
    DrawText("Pause : 'P'", 460, 680, 20, YELLOW);

    if (m_menu == TWO)
    {
        DrawText("PLAYER TWO", 420, 80, 20, RED);

        if (m_playerCount == 2)
        {
            for (int i = 0; i < m_players[1]->getHealth(); ++i)
            {
                m_players[1]->draw({ 435 + (float)i * 30, 120 }, m_players[1]->m_color);
            }
        }

        DrawText("Rotate : 'J' and 'L'", 420, 150, 10, LIGHTGRAY);
        DrawText("Move : 'I'", 420, 160, 10, LIGHTGRAY);
        DrawText("Shoot : 'K'", 420, 170, 10, LIGHTGRAY);
        DrawText("Teleport : 'U' or 'O'", 420, 180, 10, LIGHTGRAY);
    }
}

void World::displayPause()
{
    DrawText("PAUSE", m_center.x - 60, m_center.y - 50, 40, WHITE);
    DrawText("Score:", m_center.x - 150, m_center.y + 10 + 0 * 50, 20, GREEN);
    DrawText(TextFormat("%d", m_score), m_center.x, m_center.y + 10 + 0 * 50, 20, GREEN);

    DrawText("Press 'P':", m_center.x - 150, m_center.y + 10 + 1 * 50, 20, BLUE);
    DrawText("Resume game", m_center.x, m_center.y + 10 + 1 * 50, 20, BLUE);

    DrawText("Press 'Enter':", m_center.x - 150, m_center.y + 10 + 2 * 50, 20, RED);
    DrawText("Back to main menu", m_center.x, m_center.y + 10 + 2 * 50, 20, RED);

    if (IsKeyPressed(KEY_P))
    {
        m_gameSpeed = 1.f;
    }
    if (IsKeyPressed(KEY_ENTER))
    {
        m_menu = MENU;
        endGame();
    }
}

void World::displayGameOver()
{
    DrawText("GAME OVER",               m_center.x - 120,    m_center.y - 50,            40,    WHITE);
    DrawText("Score:",                  m_center.x - 150,    m_center.y + 10 + 0 * 50,   20,    GREEN);
    DrawText(TextFormat("%d", m_score), m_center.x,          m_center.y + 10 + 0 * 50,   20,    GREEN);

    DrawText("Press 'Enter':",          m_center.x - 150,    m_center.y + 10 + 1 * 50,   20,    RED);
    DrawText("Back to main menu",       m_center.x,          m_center.y + 10 + 1 * 50,   20,    RED);

    if (IsKeyPressed(KEY_ENTER))
    {
        m_menu = MENU;
    }
}

void World::setGame()
{
    m_gameSpeed = 1.f;

    m_level = 1;
    m_score = 0;

    m_spawnNum = 13;
    m_spawnTime = GetTime();
    m_enemyNum = 2;

    for (int i = 0; i < m_spawnNum; ++i)
    {
        MyVector2 pos;
        pos.x = rand() % getScreenWidth(-200) + 100;
        pos.y = rand() % getScreenHeight(-200) + 100;

        m_spawnPoint[i] = pos;
    }
}

void World::endGame()
{
    while (!m_players.empty())
    {
        m_players.pop_back();
    }
    while (!m_enemies.empty())
    {
        m_enemies.pop_back();
    }
}

void World::nextLevel()
{
    if (m_spawnNum <= 0 && m_enemies.empty())
    {
        ++m_level;

        for (auto& players : m_players)
        {
            players->addHealth();
        }

        m_spawnNum = 13;
        m_spawnTime = GetTime();
        m_enemyNum = 2;

        for (int i = 0; i < m_spawnNum; ++i)
        {
            MyVector2 pos;
            pos.x = rand() % getScreenWidth(-200) + 100;
            pos.y = rand() % getScreenHeight(-200) + 100;

            m_spawnPoint[i] = pos;
        }
    }
}

void World::playerLoop(float deltaTime, float currentTime)
{
    for (auto& players : m_players)
    {
        int moving = players->m_inputs.movingForward * 2 - 1;  //true : moving = 1, false : moving = -1
        players->m_thrust += moving / 10.f * deltaTime * m_gameSpeed;
        players->m_thrust = Math::clamp(players->m_thrust, 0, 7);

        for (auto& polygons : players->m_shape.polygons)
            polygons.angle += (players->m_inputs.rotateLeft - players->m_inputs.rotateRight) * 4 * deltaTime * m_gameSpeed;

        players->update(deltaTime, m_gameSpeed);
        players->move(*this, deltaTime);

        for (auto& enemies : m_enemies)
        {
            enemies->move(*this, deltaTime);
        }

        if (players->m_inputs.shooting)
        {
            if (currentTime - players->m_shootingTime >= 0.08f / deltaTime && m_gameSpeed > 0.f)
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
                if (enemies->shoot())
                {
                    MyVector2 dir = m_players[0]->m_shape.polygons[0].center.pointsVector(enemies->m_shape.polygons[0].center).normalizeVect();
                    Fireball temp(enemies->m_shape.polygons[0].center, dir, currentTime);
                    m_fireballs.push_back(temp);
                }

                m_score += 100;
                enemies->divide(*this);
                m_enemies.erase(m_enemies.begin() + index);

                break;
            }
            ++index;
        }

        index = 0;
        for (auto& fireballs : m_fireballs)
        {
            if (currentTime - fireballs.m_lifeTime >= 1.f / deltaTime && m_gameSpeed > 0.f)
            {
                m_fireballs.erase(m_fireballs.begin());
            }

            if (Collide::cFireballPlayer(fireballs, *m_players[0]))
            {
                m_fireballs.erase(m_fireballs.begin() + index);

                if (players->isHit())
                {
                    players->~Player();
                    m_players.pop_back();
                    --m_playerCount;
                }
            }

            fireballs.move(deltaTime, m_gameSpeed);
            fireballs.draw(RED);

            ++index;
        }

        for (auto& bullets : players->m_bullet)
        {
            if (currentTime - bullets.m_lifeTime >= 0.5f / deltaTime && m_gameSpeed > 0.f)
            {
                players->m_bullet.erase(players->m_bullet.begin());
            }

            bullets.move(deltaTime, m_gameSpeed);
            bulletOnEdge();
            bullets.draw(YELLOW);
        }
    }

    entitiesOnEdge();
}

void World::playerDraw()
{
    if (m_playerCount > 0)
    {
        if (m_playerCount == 2)
        {
            m_players[0]->draw(m_players[0]->m_color);
            m_players[1]->draw(m_players[1]->m_color);
        }
        else if (m_menu == TWO)
            m_players[0]->draw(m_players[0]->m_color);
        else
            m_players[0]->draw(WHITE);
    }
}

void World::gameLoopSingleplayer(float deltaTime, float currentTime)
{
    if (m_playerCount > 0)
    {
        m_players[0]->setInputs();
    }

    playerLoop(deltaTime, currentTime);
    playerDraw();

    for (auto& players : m_players)
    {
        int index = 0;
        for (auto& enemies : m_enemies)
        {
            if (Collide::cPlayerEnemy(*players, *enemies))
            {
                enemies->draw(RED);
                enemies->divide(*this);
                m_enemies.erase(m_enemies.begin() + index);

                if (players->isHit())
                {
                    players->~Player();
                    m_players.pop_back();
                    --m_playerCount;
                }

                break;
            }
            else
            {
                enemies->draw(GREEN);
            }
            ++index;
        }
    }

    nextLevel();

    drawSpawnPoint();
    if (currentTime - m_spawnTime >= 5.f && m_spawnNum >= 0 && m_enemyNum > 0)
    {
        spawn(BIG);
        --m_enemyNum;
        m_spawnTime = GetTime();
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

    playerLoop(deltaTime, currentTime);
    playerDraw();

    int pindex = 0;
    for (auto& players : m_players)
    {
        int index = 0;
        for (auto& enemies : m_enemies)
        {
            if (Collide::cPlayerEnemy(*players, *enemies))
            {
                enemies->draw(RED);
                enemies->divide(*this);
                m_enemies.erase(m_enemies.begin() + index);

                if (players->isHit())
                {
                    players->~Player();
                    m_players.erase(m_players.begin() + pindex);
                    --m_playerCount;
                }

                break;
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

    nextLevel();

    drawSpawnPoint();
    if (currentTime - m_spawnTime >= 5.f && m_spawnNum >= 0 && m_enemyNum > 0)
    {
        spawn(BIG);
        --m_enemyNum;
        m_spawnTime = GetTime();
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

void World::drawSpawnPoint()
{
    for (int i = 0; i < m_spawnNum + 1; ++i)
    {
        Color gray = { 130, 130, 130, 128 };
        DrawCircle(m_spawnPoint[i].x, m_spawnPoint[i].y, 5, gray);
    }
}

void World::spawn(EnemySize size)
{
    int num = Math::random(0, 3);
    int i = Math::random(0, m_spawnNum);

    if (num == 0)
    {
        m_enemies.push_back(new FloatingMine(*this, size));
        (*(m_enemies.end() - 1))->teleport(m_spawnPoint[i]);
    }
    else if (num == 1)
    {
        m_enemies.push_back(new FireballMine(*this, size));
        (*(m_enemies.end() - 1))->teleport(m_spawnPoint[i]);
    }
    else if (num == 2)
    {
        m_enemies.push_back(new MagneticMine(*this, size));
        (*(m_enemies.end() - 1))->teleport(m_spawnPoint[i]);
    }
    else if (num == 3)
    {
        m_enemies.push_back(new MagneticFireballMine(*this, size));
        (*(m_enemies.end() - 1))->teleport(m_spawnPoint[i]);
    }
    if (num == 4)
    {
        m_enemies.push_back(new Minelayer(*this));
        (*(m_enemies.end() - 1))->teleport(m_spawnPoint[i]);
    }

    m_spawnPoint[i] = m_spawnPoint[m_spawnNum];
    --m_spawnNum;
}

void World::playerOnEdge()
{
    for (auto& players : m_players)
    {
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
}

void World::bulletOnEdge()
{
    for (auto& players : m_players)
    {
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
}

void World::fireballOnEdge()
{
    for (auto& fireballs : m_fireballs)
    {
        if (fireballs.m_shape.center.x < 40)
        {
            fireballs.m_shape.center.x = screenWidth - 40;
        }
        if (fireballs.m_shape.center.x > screenWidth - 40)
        {
            fireballs.m_shape.center.x = 40;
        }
        if (fireballs.m_shape.center.y < 40)
        {
            fireballs.m_shape.center.y = screenHeight - 60;
        }
        if (fireballs.m_shape.center.y > screenHeight - 60)
        {
            fireballs.m_shape.center.y = 40;
        }
    }
}

void World::enemyOnEdge()
{
    for (auto& enemies : m_enemies)
    {
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
}

void World::entitiesOnEdge()
{
    playerOnEdge();
    bulletOnEdge();
    fireballOnEdge();
    enemyOnEdge();
}