#pragma once

#include "player.hpp"
#include "enemy.hpp"

#include "myvector2.hpp"
#include "myrectangle.hpp"
#include "mycircle.hpp"
#include "myconvexpolygon.hpp"
#include "myconcavepolygon.hpp"

namespace Collide
{
	// Point - Box
	bool    cPointBox(MyVector2 p1, MyRectangle box);
	// Box - Box
	bool    cBoxBox(MyRectangle& b1, MyRectangle& b2);
	// Circle - Box
	bool    cCircleBox(MyCircle& c1, MyRectangle& box);
	// Point - Point
	bool    cPointPoint(MyVector2 p1, MyVector2 p2);
	// Point - Circle
	bool    cPointCircle(MyVector2 p1, MyCircle c1);
	// Circle - Circle
	bool    cCircleCircle(MyCircle c1, MyCircle c2);

	// Convex - Box
	bool	cConvexBox(MyConvexPolygon p1, MyRectangle box);
	// Convex - Circle
	bool	cConvexCircle(MyConvexPolygon p1, MyCircle c1);
	// Convex - Convex
	bool	cConvexConvex(MyConvexPolygon p1, MyConvexPolygon p2);

	bool	cPlayerEnemy(Player& player, Enemy& enemy);
	bool	cPlayerPlayer(Player& player, Player& player2);
	bool	cBulletEnemy(Player& player, Enemy& enemy);
	bool	cFireballPlayer(Fireball& fireball, Player& player);
}