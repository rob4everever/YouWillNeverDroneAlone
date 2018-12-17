/*
- ResourceLoader.hpp
-
- Author: 100086865
-
*/

#pragma once

#include <map>
#include <string>

#include "Texture.hpp"
#include "Shader.hpp"
#include "Model.hpp"

class ResourceLoader {

public:
	//Maps to store the resources (shaders and textures <Resource Name><Resource>)
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture2D> textures;
	static std::map<std::string, Model> models;

	/*
	- Builds and loads a shader program from shader source files
	- @param: Vertex shader source file
	- @param: Fragment shader source file
	- @param: (Optional) Geometry shader source file
	- @param: Name for the resource
	- @return: Shader program
	*/
	static Shader loadShader(const GLchar *vertexShaderFile, const GLchar *fragmentShaderFile, const GLchar *geometryShaderFile, std::string name);

	/*
	- Gets a stored shader
	- @param: Shader name
	- @return: Requested shader
	*/
	static Shader getShader(std::string name);

	/*
	- Loads a texture from a file
	- @param: Image file
	- @param: Alpha
	- @param: Texture name
	- @return: Texture generated from an image file
	*/
	static Texture2D loadTexture(GLchar *file, GLboolean alpha, std::string name);

	/*
	- Gets a stored texture
	- @param: Texture name
	- @return: Requested texture
	*/
	static Texture2D getTexture(std::string name);

	/*
	- Loads a model
	- @param: Model path
	- @param: Gamma correction
	- @param: Model name
	- @return: Requested texture
	*/
	static Model loadModel(std::string const &path, bool gamma, std::string name);

	/*
	- Gets a stored model
	- @param: Model name
	- @return: Requested model
	*/
	static Model getModel(std::string name);

	/*
	- Clear all resources
	*/
	static void clear();

private:
	/*
	- Private constructor (Singleton class, we do not want any objects)
	*/
	ResourceLoader() {}

	/*
	- Loads and generates a shader from a file
	- @param: Vertex shader source file
	- @param: Fragment shader source file
	- @param: (Optional) Geometry shader source file
	- @return: A shader loaded from the file
	*/
	static Shader loadShaderFromFile(const GLchar *vertexShaderFile, const GLchar *fragmentShaderFile, const GLchar *geometryShaderFile = nullptr);

	/*
	- Loads and generates a texure from a file
	- @param:Texture image file
	- @param: Alpha
	- @return: A texture generated from an image file
	*/
	static Texture2D loadTextureFromFile(GLchar *file, GLboolean alpha);
};