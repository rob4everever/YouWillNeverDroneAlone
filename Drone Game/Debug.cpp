/*
-	Debug.cpp
-
-	Author: 100086865
-
-	Source code for Debug.hpp
-
*/

#include "Debug.hpp"



void Debug::printVector(glm::vec2 vec) {
	std::cout << "\n" << std::endl;
	std::cout << "VEC3.X:: " << vec.x << std::endl;
	std::cout << "VEC3.Y:: " << vec.y << std::endl;
}

void Debug::printVector(glm::vec3 vec) {
	std::cout << "\n" << std::endl;
	std::cout << "VEC3.X:: " << vec.x << std::endl;
	std::cout << "VEC3.Y:: " << vec.y << std::endl;
	std::cout << "VEC3.Z:: " << vec.z << std::endl;
}

void Debug::printVector(glm::vec4 vec) {
	std::cout << "\n" << std::endl;
	std::cout << "VEC4.X:: " << vec.x << std::endl;
	std::cout << "VEC4.Y:: " << vec.y << std::endl;
	std::cout << "VEC4.Z:: " << vec.z << std::endl;
	std::cout << "VEC4.W:: " << vec.w << std::endl;
}

void Debug::printMatrix(glm::mat2 mat) {

	std::cout << "\n" << std::endl;

	unsigned int columns, rows;

	for (int columns = 0; columns < 2; columns++) {
		for (int rows = 0; rows < 2; rows++) {
			std::cout << mat[columns][rows] << ", ";
		}

		std::cout << "\n" << std::endl;
	}
}

void Debug::printMatrix(glm::mat3 mat) {

	std::cout << "\n" << std::endl;

	unsigned int columns, rows;

	for (int columns = 0; columns < 3; columns++) {
		for (int rows = 0; rows < 3; rows++) {
			std::cout << mat[columns][rows] << ", ";
		}

		std::cout << "\n" << std::endl;
	}
}

void Debug::printMatrix(glm::mat4 mat) {

	std::cout << "\n" << std::endl;

	unsigned int columns, rows;

	for (int columns = 0; columns < 4; columns++) {
		for (int rows = 0; rows < 4; rows++) {
			std::cout << mat[columns][rows] << ", ";
		}

		std::cout << "\n" << std::endl;
	}
}