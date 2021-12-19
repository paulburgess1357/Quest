#pragma once
#include <glm/glm.hpp>

template<typename T>
class Mesh{

public:
	void draw() {
		m_mesh.bind();
		m_mesh.unbind();
		m_mesh.draw();
	}

private:

	//TODO important: the model class, NOT the mesh class, should have the matrices!!!!!

	T m_mesh;
	//glm::mat4 m_model_matrix{};
	//glm::mat3 m_normal_matrix{};
};

