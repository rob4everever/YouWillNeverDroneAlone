/*
-	GameObject.cpp
-
-	Author: 100086865
-
-	Source code for GameObject.hpp
-
*/

#include "GameObject.hpp"

GameObject::GameObject(glm::vec3 position, glm::vec3 size, glm::vec3 rotation, Model model) : position(position), size(size), rotation(rotation), model(model){
}

void GameObject::draw(Shader s) {
	this->model.draw(s);
}