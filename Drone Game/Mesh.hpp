/*
- Window.hpp
-
- Author: 100086865
-
- Class that represents a single mesh object. Multiple meshes makes
- up a complete model. Provides a function to draw a mesh to the screen.
*/

#pragma once

#include <glm/glm.hpp>

#include <iostream>
#include <vector>

#include "Shader.hpp"

/*
- A single vertex(point) is represented by 3 vectors
- positionCoordinates - the position of a vertex
- normalCoordinates - the normal coordinates of a vertex
- textureCoordinates - the coordinates of a texture
- tangentCoordinates - the coordinates of a texture
- bitangentCoordinates - the coordinates of a texture
*/
struct Vertex {
	glm::vec3 positionCoordinates;
	glm::vec3 normalCoordinates;
	glm::vec2 textureCoordinates;
	glm::vec3 tangentCoordinates;
	glm::vec3 bitangentCoordinates;
};

/*
- Texture data
- id - to allow us to identify a texture
- type - the type of texture it is (diffuse, specular etc)
- Path - location of a texture
*/
struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

/*
- Class represents a single mesh object (single shape that makes up part of a model).
- It contains the minimum data needed to define a mesh as well as method to draw the mesh to the screen
*/
class Mesh {

public:

	//Mesh data
	std::vector<Vertex>			vertices;			//collection of mesh vertices
	std::vector<unsigned int>	indices;			//collection of mesh indices
	std::vector<Texture>		textures;			//collection of mesh texture coordinates
	unsigned int VAO;

	/*
	- Constructor that initialises the data of a mesh
	- @param: vertices - a vector of vertices
	- @param: indices  - a vector of indices
	- @param: textures - a vector of texture data
	*/
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	/*
	- Draws a single mesh
	- @param: Shader used to draw
	*/
	void draw(Shader s);

	std::vector<Vertex> getVertices() { return this->vertices; }
	unsigned int VBO, EBO;
private:

	//Render data


	/*
	- Sets up the buffers to allow us to render a mesh
	*/
	void setupMesh();
};