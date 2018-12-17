/*
- Texture.hpp
-
- Author: 100086865
-
*/

#pragma once

#include <glad/glad.h>

class Texture2D {

public:
	//Texture identifier
	GLuint ID;

	//Texture dimensions
	GLuint width, height;

	//Texture format
	GLuint internal_format;
	GLuint image_format;

	//Texture configuration
	//configuration on the x(s) and y(t) axis
	GLuint wrap_s;
	GLuint wrap_t;
	//Use most or least amount of mips
	GLuint filter_min;
	GLuint filter_max;

	/*
	- Default Texture2D constructor
	*/
	Texture2D();

	/*
	- Generates a texture from an image
	- @param: image width
	- @param: image height
	- @param: image data
	*/
	void generate(GLuint width, GLuint height, unsigned char *data);

	/*
	- Binds a texture
	*/
	void bind() const;
};