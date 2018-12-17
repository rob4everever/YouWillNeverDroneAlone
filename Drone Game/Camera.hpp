#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Player.hpp"

enum cameraState {
	THIRD_PERSON,
	FIRST_PERSON,
	TOP_DOWN
};

class Camera{
public:

	cameraState state;

	glm::vec3 position;
	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;
	GLfloat distanceFromPlayer;
	GLfloat angleAroundPlayer;
	Player player;

	Camera() {}
	Camera(Player &player);
	void calculateCameraPosition(GLfloat horizDistance, GLfloat verticDistance);
	void move(Player &target);
	GLfloat calculateHorizontalDistance();
	GLfloat calculateVerticalDistance();
};