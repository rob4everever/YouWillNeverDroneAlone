/*
-	Game.hpp
-
-	Author: 100086865
-
-	Defines a game class, creates fields and provides
-	declerations for its methods
-
*/

#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include "Debug.hpp"

class Game {

public:

	GLuint width, height;
	GLboolean keys[1024];
	GLboolean keysProcessed[1024];

	/*
	- Constructor that creates the game and sets its dimenstions,
	- aswell as setting the initial GameState
	- @param: Game window width
	- @param: Game window height
	*/
	Game(GLuint width, GLuint height);

	/*
	- Initialises the game, loads shaders, textures, levels, objects etc
	*/
	void init();

	/*
	- Processes keyboard input
	- @param: Delta time
	*/
	void processInput(GLfloat deltaTime);

	/*
	- Updates the game each frame
	- @param: Delta time
	*/
	void update(GLfloat deltaTime);

	/*
	- Renders the game to the screen
	*/
	void render(GLfloat deltaTime);
};