/*
- Model.hpp
-
- Author: 100086865
-
- Creates a whole model object made of many meshes. Provides functions that
- build a model from an obj file and render it to the screen
*/

#pragma once

#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb/stb_image.h>

#include <iostream>
#include <vector>

#include "Mesh.hpp"

/*
- Represents a model in its complete from, i.e. a model object
- of multiple meshes. Model provides functionality to load a model
- into the program and draw it to the screen
*/
class Model {

public:

	//Model data
	std::vector<Texture>	texturesLoaded;		//A list of textures loaded previously (prevents generating the same texture multiple time)
	std::vector<Mesh>		meshes;				//A list of all the meshes that make up a complete model
	std::string				dir;				//Model directory
	bool					gammaCorrection;

	/*
	- Default model constructor
	*/
	Model() {}

	/*
	- Builds a model from a file at a given path
	- @param: path - the path of an object file
	*/
	Model(std::string const &path, bool gamma) : gammaCorrection(gamma) {
		loadModel(path);
	}

	/*
	- Renders a model to the screen
	- @param: Shader s
	*/
	void draw(Shader s);



private:

	/*
	- loads a model into an Assimp data strucutre called scene (Root)
	- @param: model object path
	*/
	void loadModel(std::string const &path);

	/*
	- Recursive function that gets the mesh at a node, convert it into a Mesh object and store it for processing
	- @param: Assimp node to get a mesh from
	- @param: A scene of nodes that contain mesh
	*/
	void processNode(aiNode *node, const aiScene *scene);

	/*
	- Converts an Assimp mesh into a usable Mesh object
	- @param: Assimp mesh we want to convert
	- @param: A scene of nodes that contain mesh
	- @return: A usable Mesh object
	*/
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);

	/*
	- Loads a material from the mesh data
	- @param: aiMaterial
	- @param: aiTextureType
	- @param: type name - The type of material
	*/
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};