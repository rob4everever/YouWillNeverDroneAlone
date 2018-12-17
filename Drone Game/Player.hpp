#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "GameObject.hpp"
#include "Model.hpp"

class Player : public GameObject{

public:

	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 imin;
	glm::vec3 imax;

	float weight = 30.0f;

	float currentThrust = 0.0f;
	float MAX_THRUST = 60.0f;

	float RUN_SPEED = 160.0f;
	float TURN_SPEED = 80.0f;
	float currentRunSpeed = 0.0f;
	float currentTurnSpeed = 0.0f;
	
	Player(){}
	Player(glm::vec3 position, glm::vec3 size, glm::vec3 rotation, Model model);
	void move(float deltaTime);
	void changePosition(float dx, float dy, float dz);
	void changeRotation(float dx, float dy, float dz);
	void increaseThrust();
	void decreaseThrust();

private:
};