/*
-	Game.cpp
-
-	Author: 100086865
-
-	Source file for Game.hpp
-
*/

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <irrKlang/irrKlang.h>

#include<cstdlib>
#include<ctime>

#include "Camera.hpp"
#include "CollisionDetection.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Light.hpp"
#include "MasterRenderer.hpp"
#include "Model.hpp"
#include "Maths.hpp"
#include "ResourceLoader.hpp"
#include "Shader.hpp"

using namespace irrklang;

void  collide(Player &one, std::vector<GameObject> &entities);

//Globals
Camera camera;
Player player;
Shader shader;
Shader terrainshader;
MasterRenderer renderer;
std::vector <GameObject> entityList;
std::vector <GameObject> terrainList;
Light light;
ISoundEngine *SoundEngine = createIrrKlangDevice();

Game::Game(GLuint width, GLuint height) : width(width), height(height), keys() {}

void Game::init() {
	//Load shaders
	shader = ResourceLoader::loadShader("shaders/VertexShader.glsl", "shaders/FragmentShader.glsl", nullptr, "s");

	//Load models
	Model droneModel = ResourceLoader::loadModel("Models/omfg.obj", false, "drone");
	Model floorModel = ResourceLoader::loadModel("Models/terrain/hill1.obj", true, "drone");
	Model treeModel = ResourceLoader::loadModel("Models/Trees/mynewtree.obj", false, "drone");
	Model treeModel1 = ResourceLoader::loadModel("Models/Trees/lpt.obj", false, "drone");
	Model fernModel = ResourceLoader::loadModel("Models/Ferns/fern.obj", false, "fern");

	//drone
	player = Player(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0.0f, 0.0f, 0), droneModel);
	entityList.push_back(player);

	//terrain
	GameObject terrain = GameObject(glm::vec3(0, 0, 0), glm::vec3(25.0f, 0.0, 25.0f), glm::vec3(0.0f, 0.0f, 0), floorModel);

	terrainList.push_back(terrain);
	std::srand(std::time(0));
	for (int i = 0; i < 300; i++) {

		int rx = std::rand() % 8000 + 1;
		int rz = std::rand() % 8000 + 1;

		int n = std::rand() % 4 + 1;

		if (n == 1) {
			rx = -rx;
			rz = -rz;
		}
		else if (n == 2) {
			rx = -rx;
			rz = rz;
		}
		else if (n == 3) {
			rz = -rz;
			rx = rx;
		}
		else  if (n == 4) {
			rx = rx;
			rz = rz;
		}

		GameObject tree = GameObject(glm::vec3(rx, 0, rz), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), treeModel1);

		if (i > 250) {
			tree.model = treeModel1;
		}
		else {
			tree.model = treeModel;
		}

		auto treeMIN = tree.model.meshes[0].vertices[0].positionCoordinates;
		auto treeMAX = treeMIN;
		for (const auto& mesh : tree.model.meshes) {
			for (const auto& vertex : mesh.vertices) {
				if (vertex.positionCoordinates.x < treeMIN.x) treeMIN.x = vertex.positionCoordinates.x;
				if (vertex.positionCoordinates.y < treeMIN.y) treeMIN.y = vertex.positionCoordinates.y;
				if (vertex.positionCoordinates.z < treeMIN.z) treeMIN.z = vertex.positionCoordinates.z;
				if (vertex.positionCoordinates.x > treeMAX.x) treeMAX.x = vertex.positionCoordinates.x;
				if (vertex.positionCoordinates.y > treeMAX.y) treeMAX.y = vertex.positionCoordinates.y;
				if (vertex.positionCoordinates.z > treeMAX.z) treeMAX.z = vertex.positionCoordinates.z;
			}
		}

		//update box positions
		treeMIN.x = treeMIN.x + tree.position.x;
		treeMAX.x = treeMAX.x + tree.position.x;
		treeMIN.y = treeMIN.y + tree.position.y;
		treeMAX.y = treeMAX.y + tree.position.y;
		treeMIN.z = treeMIN.z + tree.position.z;
		treeMAX.z = treeMAX.z + tree.position.z;

		treeMIN.x = treeMIN.x;
		treeMAX.x = treeMAX.x;
		treeMIN.y = treeMIN.y;
		treeMAX.y = treeMAX.y;
		treeMIN.z = treeMIN.z;
		treeMAX.z = treeMAX.z;

		tree.min.x = treeMIN.x;
		tree.max.x = treeMAX.x;
		tree.min.y = treeMIN.y;
		tree.max.y = treeMAX.y;
		tree.min.z = treeMIN.z;
		tree.max.z = treeMAX.z;

		entityList.push_back(tree);
	}


	//Initialise the renderer
	renderer = MasterRenderer(this->width, this->height);
	renderer.init();

	//Initialise camera
	camera = Camera(player);

	//Initialise light 
	light = Light(glm::vec3(-500000, 10000, 10000), glm::vec3(0.992, 0.737, 0.050));

	auto playerMIN = player.model.meshes[0].vertices[0].positionCoordinates;
	auto playerMAX = playerMIN;
	for (const auto& mesh : player.model.meshes) {
		for (const auto& vertex : mesh.vertices) {
			if (vertex.positionCoordinates.x < playerMIN.x) playerMIN.x = vertex.positionCoordinates.x;
			if (vertex.positionCoordinates.y < playerMIN.y) playerMIN.y = vertex.positionCoordinates.y;
			if (vertex.positionCoordinates.z < playerMIN.z) playerMIN.z = vertex.positionCoordinates.z;
			if (vertex.positionCoordinates.x > playerMAX.x) playerMAX.x = vertex.positionCoordinates.x;
			if (vertex.positionCoordinates.y > playerMAX.y) playerMAX.y = vertex.positionCoordinates.y;
			if (vertex.positionCoordinates.z > playerMAX.z) playerMAX.z = vertex.positionCoordinates.z;
		}
	}

	player.imin.x = playerMIN.x;
	player.imax.x = playerMAX.x;
	player.imin.y = playerMIN.y;
	player.imax.y = playerMAX.y;
	player.imin.z = playerMIN.z;
	player.imax.z = playerMAX.z;

	SoundEngine->play2D("sound/rive.mp3", GL_TRUE);
	SoundEngine->setSoundVolume(0.2);


}

void Game::processInput(GLfloat deltaTime) {
	
	//speed
	if (this->keys[GLFW_KEY_W]) {
		player.currentRunSpeed = player.RUN_SPEED;
	}
	else if (this->keys[GLFW_KEY_S]) {
		player.currentRunSpeed = -player.RUN_SPEED;
	}
	else {
		player.currentRunSpeed = 0.0f;
	}

	//angle
	if (this->keys[GLFW_KEY_A]) {
		player.currentTurnSpeed = player.TURN_SPEED;
	}
	else if (this->keys[GLFW_KEY_D]) {
		player.currentTurnSpeed = -player.TURN_SPEED;
	}
	else {
		player.currentTurnSpeed = 0.0f;
	}

	//thrust
	if (this->keys[GLFW_KEY_U]) {
		player.increaseThrust();
	}
	else if (this->keys[GLFW_KEY_J]) {
		player.decreaseThrust();
	}
	else if (this->keys[GLFW_KEY_R]) {
		player.currentThrust = player.weight;
	}

	//camera
	if (this->keys[GLFW_KEY_1]) {
		camera.state = THIRD_PERSON;
	}
	else if (this->keys[GLFW_KEY_2]) {
		camera.state = FIRST_PERSON;
	}
	else if (this->keys[GLFW_KEY_3]) {
		camera.state = TOP_DOWN;
	}
}

void Game::update(GLfloat deltaTime) {

	//Update player position
	player.move(deltaTime);
	entityList[0].position = player.position;
	entityList[0].rotation = player.rotation;

	//Update camera position
	camera.move(player);

	CollisionDetection::checkCollisions(player, entityList);

	collide(player, entityList);
}

void Game::render(GLfloat deltaTime) {
	//Render a list of entities
	renderer.render(entityList, terrainList, camera, light);
}

void  collide(Player &player, std::vector<GameObject> &entities) {

	for (int i = 1; i < entityList.size(); i++) {

		player.min = player.imin;
		player.max = player.imax;
		player.min.x = player.min.x + player.position.x;
		player.max.x = player.max.x + player.position.x;
		player.min.y = player.min.y + player.position.y;
		player.max.y = player.max.y + player.position.y;
		player.min.z = player.min.z + player.position.z;
		player.max.z = player.max.z + player.position.z;

		//check for collisions
		if (((player.max.x > entityList[i].min.x) && (player.min.x < entityList[i].max.x)) && ((player.max.y > entityList[i].min.y) && (player.min.y < entityList[i].max.y)) && ((player.max.z > entityList[i].min.z) && (player.min.z < entityList[i].max.z))) {
			player.rotation.y += 90;
			player.position.x = player.position.x - 5.0f;
			player.position.z = player.position.z - 5.0f;
		}
	}
}