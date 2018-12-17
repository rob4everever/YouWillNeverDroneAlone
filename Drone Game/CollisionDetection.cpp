#include "CollisionDetection.hpp"

CollisionDetection::CollisionDetection() {}

void CollisionDetection::checkCollisions(Player &player, std::vector<GameObject> &entities) {
	checkAreaBoundaries(player);

}

void CollisionDetection::checkAreaBoundaries(Player &player) {

	if (player.position.y <= 2.5f) {
		player.position.y = 4.5f;
	}
	if (player.position.y >= 1600.0f) {
		player.position.y = 1600.0f;
	}
}
