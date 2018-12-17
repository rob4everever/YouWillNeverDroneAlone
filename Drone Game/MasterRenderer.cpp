/*
-	MasterRenderer.cpp
-
-	Author: 100086865
-
-	Source code for MasterRenderer.hpp
-
*/

#include "MasterRenderer.hpp"


//render - 
//sets shader values
//calls all other renderers (gameobj, terrain)

MasterRenderer::MasterRenderer(GLuint width, GLuint height) {

	this->displayWidth = width;
	this->displayHeight = height;

	FOV = 70;
	NEAR_PLANE = 0.1f;
	FAR_PLANE = 1000000.0f;
}

void MasterRenderer::init() {
	createProjectionMatrix();
	 
	//load shaders in
	entityShader = ResourceLoader::loadShader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl", nullptr, "defaultShader");
	terrainShader = ResourceLoader::loadShader("shaders/terrainVertexShader.glsl", "shaders/terrainFragmentShader.glsl", nullptr, "terrainShader");

	//init renderers
	gameObjectRenderer = GameObjectRenderer(entityShader, projectionMatrix);
	terrainRenderer = TerrainRenderer(terrainShader, projectionMatrix);
}

void MasterRenderer::render(std::vector<GameObject> &entities, std::vector<GameObject> &terrainList, Camera &camera, Light &light) {

	//Prepare for rendering
	prepare();

	//Calculate View matrix
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera);

	//load in vars for each shader
	entityShader.use();
	entityShader.setMatrix4("view", viewMatrix);
	entityShader.setVector3f("lightPosition", light.position);
	entityShader.setVector3f("lightColour", light.colour );
	entityShader.setFloat("shine", entities[0].shine );
	entityShader.setFloat("reflection", entities[0].reflection );

	gameObjectRenderer.render(entities); //this

	terrainShader.use();
	terrainShader.setMatrix4("view", viewMatrix);
	terrainShader.setVector3f("lightPosition", light.position);
	terrainShader.setVector3f("lightColour", light.colour);
	terrainShader.setFloat("shine", terrainList[0].shine);
	terrainShader.setFloat("reflection", terrainList[0].reflection);
	std::cout << terrainList.size() << std::endl;

	terrainRenderer.render(terrainList); //this

}

void MasterRenderer::prepare() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_MULTISAMPLE);
}

void MasterRenderer::createProjectionMatrix() {
	projectionMatrix = glm::perspective(glm::radians(45.0f), (float) displayWidth / (float) displayHeight, NEAR_PLANE, FAR_PLANE);
}