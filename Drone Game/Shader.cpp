/*
- Shader.cpp
-
- Author: 100086865
-
*/

#include "Shader.hpp"

Shader &Shader::use() {
	glUseProgram(this->ID);
	return *this;
}

void Shader::compile(const GLchar *vs, const GLchar *fs, const GLchar *gs) {

	GLuint vertexShader, fragmentShader, geometryShader;

	//Compile the vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::cout << "here" << std::endl;

	glShaderSource(vertexShader, 1, &vs, NULL);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, "Vertex Shader");

	//Compile the fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fs, NULL);
	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader, "Fragment Shader");

	//Compile the geometry shader (If it exists)
	if (gs != nullptr) {
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShader, 1, &gs, NULL);
		glCompileShader(geometryShader);
		checkCompileErrors(geometryShader, "Geometry Shader");
	}

	//Build the shader program
	this->ID = glCreateProgram();

	//Attach shaders to the program
	glAttachShader(this->ID, vertexShader);
	glAttachShader(this->ID, fragmentShader);
	if (gs != nullptr) { glAttachShader(this->ID, geometryShader); }

	//Links all the attached shaders to the program
	glLinkProgram(this->ID);
	checkCompileErrors(this->ID, "Shader program");

	//Clean up shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (gs != nullptr) { glDeleteShader(geometryShader); }
}

void Shader::setFloat(const GLchar *name, GLfloat value, GLboolean useShader) {

	if (useShader) {
		this->use();
	}

	glUniform1f(glGetUniformLocation(this->ID, name), value);
}
void Shader::setInteger(const GLchar *name, GLint value, GLboolean useShader) {

	if (useShader) {
		this->use();
	}

	glUniform1i(glGetUniformLocation(this->ID, name), value);
}
void Shader::setVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader) {

	if (useShader) {
		this->use();
	}

	glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}
void Shader::setVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader) {

	if (useShader) {
		this->use();
	}

	glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}
void Shader::setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader) {

	if (useShader) {
		this->use();
	}

	glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}
void Shader::setVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader) {

	if (useShader) {
		this->use();
	}

	glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}
void Shader::setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader) {

	if (useShader) {
		this->use();
	}

	glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}
void Shader::setVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader) {

	if (useShader) {
		this->use();
	}

	glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}
void Shader::setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader) {

	if (useShader) {
		this->use();
	}

	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(GLuint shaderObject, std::string type) {

	GLint success;
	GLchar infoLog[1024];
	if (type != "Shader Program") {

		glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(shaderObject, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
	else {

		glGetProgramiv(shaderObject, GL_LINK_STATUS, &success);

		if (!success) {
			glGetProgramInfoLog(shaderObject, 1024, NULL, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
}