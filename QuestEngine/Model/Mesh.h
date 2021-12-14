#pragma once
#include <glm/glm.hpp>

template<typename T>
class Mesh{

public:
	void draw() {
		m_mesh.bind();
		m_mesh.draw();
		m_mesh.unbind();
	}

private:
	T m_mesh;
	glm::mat4 m_model_matrix{};
	glm::mat3 m_normal_matrix{};
};

