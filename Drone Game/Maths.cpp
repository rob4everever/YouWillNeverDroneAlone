#include "Maths.hpp"

glm::mat4 Maths::createTransformationMatrix(glm::vec3 &translation, glm::vec3 &rotation, glm::vec3 &scale) {

	//Identity matrix
	glm::mat4 identityMatrix = glm::mat4(1.0f); 

	//Translation matrix
	glm::mat4 translationMatrix = glm::translate(identityMatrix, translation);

	//Rotation matrix
	glm::mat4 rotationX = glm::rotate(identityMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotationY = glm::rotate(identityMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotationZ = glm::rotate(identityMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 rotationMatrix = rotationX * rotationY * rotationZ;
	
	//Scale matrix
	glm::mat4 scaleMatrix = glm::scale(identityMatrix, scale);
	
	//Transformation matrix
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	return transformationMatrix;
}

glm::mat4 Maths::createViewMatrix(Camera &camera) {
	
	glm::mat4 viewMatrix = glm::mat4(1.0f); // identity matrix

	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.pitch), glm::vec3(1, 0, 0));
	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.yaw), glm::vec3(0, 1, 0));

	glm::vec3 cameraPos = camera.position;
	glm::vec3 negativeCameraPos = glm::vec3(-cameraPos[0], -cameraPos[1], -cameraPos[2]);

	viewMatrix = glm::translate(viewMatrix, negativeCameraPos);

	return viewMatrix;
}