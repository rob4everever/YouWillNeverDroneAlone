#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.hpp"

class Maths {
public:
	static glm::mat4 createTransformationMatrix(glm::vec3 &translation, glm::vec3 &rotation, glm::vec3 &scale);
	static glm::mat4 createViewMatrix(Camera &camera);
};