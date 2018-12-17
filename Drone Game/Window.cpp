/*
-	Window.cpp
-
-	Author: 100086865
-
-	Entry point for the program. Creates and configures a window and
-	initialises and starts the game.
-
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Game.hpp"
#include "ResourceLoader.hpp"
#include "Window.hpp"

//Screen dimensions
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;

Game YouWillNeverDroneAlone(SCR_WIDTH, SCR_HEIGHT);

int main() {
	//GLFW configuration
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	//GLFW window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "You Will Never Drone Alone...", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	//GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//Prints OpenGL version
	printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));

	//Timings
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	//Initialise the game
	YouWillNeverDroneAlone.init();

	//Game loop
	while (!glfwWindowShouldClose(window)) {

		//Calculate delta time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = (currentFrame - lastFrame);
		lastFrame = currentFrame;
		glfwPollEvents();

		//Process input
		YouWillNeverDroneAlone.processInput(deltaTime);

		//Update game
		YouWillNeverDroneAlone.update(deltaTime);

		//Render game
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		YouWillNeverDroneAlone.render(deltaTime);

		//Swap buffers
		glfwSwapBuffers(window);
	}

	//Deallocate resources
	ResourceLoader::clear();

	//Close program
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			YouWillNeverDroneAlone.keys[key] = GL_TRUE;
		}
		else if (action == GLFW_RELEASE) {
			YouWillNeverDroneAlone.keys[key] = GL_FALSE;
			YouWillNeverDroneAlone.keysProcessed[key] = GL_FALSE;
		}
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}