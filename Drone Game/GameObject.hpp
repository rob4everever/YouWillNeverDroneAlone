#pragma once

/*
-	GameObject.hpp
-
-	Author: 100086865
-
-	Represents a generic object in the game
-
*/

#include <glm/glm.hpp>

#include <iostream>

#include "Model.hpp"
#include "Shader.hpp"

class GameObject {
public:
	glm::vec3 position;
	glm::vec3 size;
	glm::vec3 rotation;
	Model model;

	glm::vec3 min;
	glm::vec3 max;

	float shine;
	float reflection;

	GameObject() {}
	GameObject(glm::vec3 position, glm::vec3 size, glm::vec3 rotation, Model model);
	void draw(Shader s);
private:
};

