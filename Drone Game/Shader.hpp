/*
- Shader.hpp
-
- Author: 100086865
-
*/

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>

class Shader {

public:

	//Shader indentifier
	GLuint ID;

	/*
	- Default Shader constructor
	*/
	Shader() {}

	/*
	- Sets the shader to be used
	- @return: The shader in use
	*/
	Shader &use();

	/*
	- Compiles the shaders into a shader program
	- @param: Vertex shader source
	- @param: Fragment shader source
	- @param: (Optional) geometry shader source
	*/
	void compile(const GLchar *vs, const GLchar *fs, const GLchar *gs = nullptr);

	/*
	- Sets the uniform variables of a shader to the specified value
	- @param: Uniform variable name
	- @param: Uniform variable value(s)
	- @param: Should the shader be used?
	*/
	void setFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
	void setInteger(const GLchar *name, GLint value, GLboolean useShader = false);
	void setVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void setVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
	void setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void setVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
	void setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void setVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
	void setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);

private:
	/*
	- Checks for errors when compiling the shader program
	- @param: Shader object causing the error
	- @param: The type of error (Vertex Shader, Fragment Shader, Geometry Shader, Shader Program)
	*/
	void checkCompileErrors(GLuint shaderObject, std::string type);
};