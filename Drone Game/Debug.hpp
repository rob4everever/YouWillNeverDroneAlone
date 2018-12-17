/*
-	Debug.hpp
-
-	Author: 100086865
-
-	Provides static methods that aid in debugging issues
-
*/

#pragma once


#include <glm/glm.hpp>
#include <iostream>

class Debug {

public:

	/*
	- Prints a vec2
	- @param: vec2
	*/
	static void printVector(glm::vec2 vec);

	/*
	- Prints a vec3
	- @param: vec3
	*/
	static void printVector(glm::vec3 vec);

	/*
	- Prints a vec4
	- @param: vec4
	*/
	static void printVector(glm::vec4 vec);

	/*
	- Prints a 4x4 matrix
	- @param: 4x4 matrix
	*/
	static void printMatrix(glm::mat2 mat);

	/*
	- Prints a 4x4 matrix
	- @param: 4x4 matrix
	*/
	static void printMatrix(glm::mat3 mat);

	/*
	- Prints a 4x4 matrix
	- @param: 4x4 matrix
	*/
	static void printMatrix(glm::mat4 mat);
};