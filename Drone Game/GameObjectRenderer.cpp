/*
-	GameObjectRenderer.cpp
-
-	Author: 100086865
-
-	Source code for GameObjectRenderer.hpp
-
*/

#include "GameObjectRenderer.hpp"

GameObjectRenderer::GameObjectRenderer(Shader shader, glm::mat4 projectionMatrix) : shader(shader) {
	//Pass the shader to the vertex shader (uses before passing)
	shader.setMatrix4("projection", projectionMatrix, GL_TRUE);
}

void GameObjectRenderer::prepareInstance(GameObject &object) {
	glm::mat4 transformationMatrx = Maths::createTransformationMatrix(object.position, object.rotation, object.size);
	shader.setMatrix4("model", transformationMatrx);
}

void GameObjectRenderer::render(std::vector<GameObject> &entities) {
	for (GameObject &e : entities) {
		prepareInstance(e);
		e.draw(shader);
	}
}