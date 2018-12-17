/*
- ResourceLoader.cpp
-
- Author: 100086865
-
*/

#include <SOIL.h>

#include <iostream>
#include <sstream>
#include <fstream>

#include "ResourceLoader.hpp"

// Instantiate static variables
std::map<std::string, Texture2D> ResourceLoader::textures;
std::map<std::string, Shader> ResourceLoader::shaders;
std::map<std::string, Model> ResourceLoader::models;

Shader ResourceLoader::loadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name) {
	shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return shaders[name];
}

Shader ResourceLoader::getShader(std::string name) {
	return shaders[name];
}

Texture2D ResourceLoader::loadTexture(GLchar *file, GLboolean alpha, std::string name) {
	textures[name] = loadTextureFromFile(file, alpha);
	return textures[name];
}

Texture2D ResourceLoader::getTexture(std::string name) {
	return textures[name];
}

Model ResourceLoader::loadModel(std::string const &path, bool gamma, std::string name) {
	models[name] = Model(path, gamma);
	return models[name];
}

Model ResourceLoader::getModel(std::string name) {
	return models[name];
}

void ResourceLoader::clear() {
	for (auto iter : shaders) {
		glDeleteProgram(iter.second.ID);
	}
	for (auto iter : textures) {
		glDeleteProgram(iter.second.ID);
	}
}

Shader ResourceLoader::loadShaderFromFile(const GLchar *vertexShaderFile, const GLchar *fragmentShaderFile, const GLchar *geometryShaderFile) {

	std::string vertexShaderCode;
	std::string fragmentShaderCode;
	std::string geometryShaderCode;



	try {
		//Open shader files
		std::ifstream vertexShaderFile(vertexShaderFile);
		std::ifstream fragmentShaderFile(fragmentShaderFile);
		std::stringstream vShaderStream, fShaderStream;

		//Read file into stream
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();

		//Close files
		vertexShaderFile.close();
		fragmentShaderFile.close();

		//Stream to string
		vertexShaderCode = vShaderStream.str();
		fragmentShaderCode = fShaderStream.str();

		if (geometryShaderFile != nullptr) {
			std::ifstream geometryShaderFile(geometryShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryShaderCode = gShaderStream.str();
		}
	}
	catch (std::exception e) {
		std::cout << "Error in shader: Failed to read the shader files" << std::endl;
	}
	Shader shader;
	shader.compile(vertexShaderCode.c_str(), fragmentShaderCode.c_str(), geometryShaderFile != nullptr ? geometryShaderCode.c_str() : nullptr);

	return shader;
}

Texture2D ResourceLoader::loadTextureFromFile(GLchar *file, GLboolean alpha) {

	Texture2D texture;

	//Set alpha if required
	if (alpha) {
		texture.internal_format = GL_RGBA;
		texture.image_format = GL_RGBA;
	}

	//Load the image
	int width, height;
	unsigned char *image = SOIL_load_image(file, &width, &height, 0, texture.image_format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);

	//Generate texture
	texture.generate(width, height, image);

	//Free image data
	SOIL_free_image_data(image);
	return texture;
}

