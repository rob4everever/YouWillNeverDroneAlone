/*
-	GameObjectRenderer.hpp
-
-	Author: 100086865
-
-	Represents a renderer for the game objects
-
*/

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "GameObject.hpp"
#include "Maths.hpp"
#include "Shader.hpp"

class GameObjectRenderer {

public:
	GameObjectRenderer() {}
	GameObjectRenderer(Shader shader, glm::mat4 projectionMatrix);
	void prepareInstance(GameObject &object);
	
	//this will take a list eventually
	void render(std::vector<GameObject> &entities);

private:
	Shader shader;
};