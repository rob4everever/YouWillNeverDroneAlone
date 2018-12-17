#include "Camera.hpp"

Camera::Camera(Player &player) : player(player) {
	position = glm::vec3(0, 0, 0);
	pitch = 10.0f;
	yaw = 0.0f;
	roll = 0.0f;
	distanceFromPlayer = 45;
	angleAroundPlayer = 0;
	state = THIRD_PERSON;
}

void Camera::calculateCameraPosition(GLfloat horizDistance, GLfloat verticDistance) {

	if (state == THIRD_PERSON) {
		//pitch = 10.0f;
		distanceFromPlayer = 45;
		GLfloat theta = player.rotation.y + 0;
		GLfloat offsetX = horizDistance * sin(glm::radians(theta));
		GLfloat offsetZ = horizDistance * cos(glm::radians(theta));
		position.x = player.position.x - offsetX;
		position.z = player.position.z - offsetZ;
		position.y = player.position.y + verticDistance;
		yaw = 180 - (player.rotation.y + angleAroundPlayer);
	}

	else if (state == FIRST_PERSON) {
		pitch = 10.0f;
		distanceFromPlayer = 45;
		GLfloat theta = player.rotation.y + 0;
		GLfloat offsetX = horizDistance * sin(glm::radians(theta));
		GLfloat offsetZ = horizDistance * cos(glm::radians(theta));
		position.x = player.position.x;
		position.z = player.position.z;
		position.y = player.position.y + verticDistance;
		yaw = 180 - (player.rotation.y + angleAroundPlayer);
	}

	if (state == TOP_DOWN) {
		pitch = 90.0f;
		distanceFromPlayer = 150.00f;
		GLfloat theta = player.rotation.y + 0;
		GLfloat offsetX = horizDistance * sin(glm::radians(theta));
		GLfloat offsetZ = horizDistance * cos(glm::radians(theta));
		position.x = player.position.x - offsetX;
		position.z = player.position.z - offsetZ;
		position.y = player.position.y + verticDistance;
		yaw = 180 - (player.rotation.y + angleAroundPlayer);
	}

}

void Camera::move(Player &target) {
	this->player = target;
	GLfloat horizontalDistance = calculateHorizontalDistance();
	GLfloat verticalDistance = calculateVerticalDistance();
	calculateCameraPosition(horizontalDistance, verticalDistance);
}

GLfloat Camera::calculateHorizontalDistance() {
	return distanceFromPlayer * cos(glm::radians(pitch));
}

GLfloat Camera::calculateVerticalDistance() {
	return distanceFromPlayer * sin(glm::radians(pitch));
}