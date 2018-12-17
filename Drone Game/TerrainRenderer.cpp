#include "TerrainRenderer.hpp"

TerrainRenderer::TerrainRenderer(Shader shader, glm::mat4 projectionMatrix) : shader(shader) {
	//Pass the shader to the vertex shader (uses before passing)
	shader.setMatrix4("projection", projectionMatrix, GL_TRUE);
}

void TerrainRenderer::prepareInstance(GameObject &object) {
	glm::mat4 transformationMatrx = Maths::createTransformationMatrix(object.position, object.rotation, object.size);
	shader.setMatrix4("model", transformationMatrx);
}

void TerrainRenderer::render(std::vector<GameObject> &terrains) {
	for (GameObject &e : terrains) {
		prepareInstance(e);
		e.draw(shader);
	}
}