#include "Player.hpp"

Player::Player(glm::vec3 position, glm::vec3 size, glm::vec3 rotation, Model model) : GameObject(position, size, rotation, model) {}

void Player::move(float deltaTime) {
	
	changeRotation(0, currentTurnSpeed * deltaTime, 0);
	float distance = currentRunSpeed * deltaTime;
	float dx = distance * sin(glm::radians(this->rotation.y));
	float dz = distance * cos(glm::radians(this->rotation.y));
	
	if (currentThrust > (weight + 5.0f) && currentThrust <= 45.0f) {
		changePosition(dx, 2.0f, dz);
	}
	else if (currentThrust > (weight + 5.0f) && currentThrust > 45.0f) {
		changePosition(dx, 4.0f, dz);

	}

	else if (currentThrust < (weight - 5.0f) && currentThrust > 15.0f) {
		changePosition(dx, -2.0f, dz);
	}

	else if (currentThrust < (weight - 5.0f) && currentThrust <= 15.0f) {
		changePosition(dx, -4.0f, dz);
	}

	else {
		double x = rand() / static_cast<double>(RAND_MAX + 1);
		int randomNumber = 1 + static_cast<int>(x * (4 - 1));

		float thrustShift = 0;

		if (randomNumber == 1) {
			thrustShift = 2.5f;
		}
		else if (randomNumber == 2) {
			thrustShift = -2.5f;
		}

		changePosition(dx, thrustShift, dz);
	}
}

void Player::changePosition(float dx, float dy, float dz) {
	this->position.x += dx;
	this->position.y += dy;
	this->position.z += dz;
}

void Player::changeRotation(float dx, float dy, float dz) {
	this->rotation.x += dx;
	this->rotation.y += dy;
	this->rotation.z += dz;
}

void Player::increaseThrust() {

	if (currentThrust < MAX_THRUST) {
		currentThrust += 2.0f;
	}
}

void Player::decreaseThrust() {
	if (currentThrust > 00) {
		currentThrust -= 2.0f;
	}
}