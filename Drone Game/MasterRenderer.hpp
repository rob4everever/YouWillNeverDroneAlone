/*
-	MasterRenderer.hpp
-
-	Author: 100086865
-
-	Class that defines a master renderer
-
*/

#pragma once

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "Camera.hpp"
#include "Debug.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "GameObjectRenderer.hpp"
#include "Light.hpp"
#include "ResourceLoader.hpp"
#include "TerrainRenderer.hpp"

class MasterRenderer {

public:
	GLfloat FOV;
	GLfloat NEAR_PLANE;
	GLfloat FAR_PLANE;

	MasterRenderer() {}
	MasterRenderer(GLuint width, GLuint height);
	void init();
	void prepare();
	void render(std::vector<GameObject> &entities, std::vector<GameObject> &terrainList, Camera &camera, Light &light); //objs//lights//terrain

private:
	GLuint displayWidth, displayHeight;
	glm::mat4 projectionMatrix;
	GameObjectRenderer gameObjectRenderer;
	TerrainRenderer terrainRenderer;
	Shader entityShader;
	Shader terrainShader;

	void createProjectionMatrix();
};