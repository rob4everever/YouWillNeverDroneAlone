#pragma once

#include "Player.hpp"

class CollisionDetection {
public:
	CollisionDetection();
	static void checkCollisions(Player &player, std::vector<GameObject> &entities);
	static void checkAreaBoundaries(Player &player); 
};
