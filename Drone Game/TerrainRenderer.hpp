#pragma once

#include "GameObject.hpp"
#include "Maths.hpp"
#include "Shader.hpp"
#include "TerrainRenderer.hpp"


class TerrainRenderer {
public:
	TerrainRenderer() {}
	TerrainRenderer(Shader shader, glm::mat4 projectionMatrix);
	void prepareInstance(GameObject &object);

	//this will take a list eventually
	void render(std::vector<GameObject> &entities);

private:
	Shader shader;
};