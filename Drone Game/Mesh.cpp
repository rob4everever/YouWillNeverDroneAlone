/*
- Mesh.cpp
-
- Author: 100086865
-
- Source code for Mesh.hpp
*/

#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {

	//Sets the required data of a mesh object
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	//Calls a function that will build the mesh
	setupMesh();
}

void Mesh::setupMesh() {

	//Generate buffers
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	//Bind buffers
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

	//Buffer render data
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &this->indices[0], GL_STATIC_DRAW);

	//Vertex coordinates	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	//Normal coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normalCoordinates));

	//Texture coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates));

	//Tangent coordinates
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangentCoordinates));

	//Bitangent coordinates
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangentCoordinates));

	//Unbind current vertex array
	glBindVertexArray(0);
}

void Mesh::draw(Shader s) {

	//Different texture types
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	//Loop through every texture of a mesh
	for (unsigned int i = 0; i < textures.size(); i++) {

		//Activates the appropiate texture
		glActiveTexture(GL_TEXTURE0 + i);

		//texture number
		std::string number;
		//Type of texture e.g. texture_diffuse
		std::string name = textures[i].type;

		if (name == "texture_diffuse") {
			//increments (creates) another diffuse texture and increases its identification number
			number = std::to_string(diffuseNr++);
		}
		else if (name == "texture_specular") {
			//increments (creates) another specular texture and increases its identification number
			number = std::to_string(specularNr++);
		}
		else if (name == "texture_normal") {
			//increments (creates) another normal texture and increases its identification number
			number = std::to_string(normalNr++);
		}
		else if (name == "texture_height") {
			//increments (creates) another height texture and increases its identification number
			number = std::to_string(heightNr++);
		}

		s.setFloat(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	//Bind the VAO
	glBindVertexArray(this->VAO);
	//Index draw each element
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	//Unbind VAO
	glBindVertexArray(0);

	//Deactivate currently bound texture
	glActiveTexture(GL_TEXTURE0);
}