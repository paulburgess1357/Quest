#include "pch.h"
#include "PointLightLoaderAPI.h"
#include "QuestEngine/API/OpenGL/ModelLoaderAPI.h"

namespace QuestEngine::API::OpenGL {

	SphereLoader::SphereLoader(const float radius, const int sectors, const int stacks, const bool smooth)
		:m_sphere{ radius, sectors, stacks, smooth} {
	}

	void SphereLoader::load_sphere_into_resource(QuestEngine::API::EngineAPI& engine_api, const std::string& sphere_resource_id, const std::string& loaded_shader_id, const bool position_only) const {
		const QuestEngine::API::OpenGL::ShaderLoaderAPI shader_loader = engine_api.get_shader_loader_api();
		const QuestEngine::API::OpenGL::ModelLoaderAPI model_loader = engine_api.get_model_loader_api();
		if (position_only) {
			// Load Position (e.g. pointlight)
			model_loader.load_model<GL_TRIANGLES>(sphere_resource_id, loaded_shader_id, { m_sphere.getVerticesVector() }, { m_sphere.getIndiciesVector() }, { 3, 3, 2 });
		} else {
			// Load Position, Normals, and Texture Coordinates
			model_loader.load_model<GL_TRIANGLES>(sphere_resource_id, loaded_shader_id, { m_sphere.getInterleavedVerticesVector() }, { m_sphere.getIndiciesVector() }, { 3, 3, 2 });
		}
	}

	void SphereLoader::load_default_textured_sphere_into_resource(QuestEngine::API::EngineAPI& engine_api, const std::string& sphere_resource_id, const std::string& loaded_shader_id) const {

		// Load into resource
		load_sphere_into_resource(engine_api, sphere_resource_id, loaded_shader_id, false);

		// Texture Sphere

		// Get pointer to loaded model
		const QuestEngine::API::ResourceAPI& resource_api = engine_api.get_resource_api();
		QuestEngine::Model::IndexedModel* model_pointer = resource_api.get_indexed_model_pointer(sphere_resource_id);

		// Get pointer to model's shader
		const auto texture_ptr = resource_api.get_texture_pointer(Constants::default_texture);
		QuestGLCore::Shader::ShaderProgram* model_shader_program = model_pointer->get_shader_program();

		// For each mesh, register the texture
		auto& mesh_vector = model_pointer->get_mesh_vector();
		for (auto& model_mesh : mesh_vector) {
			model_mesh.register_texture(Constants::default_diffuse_shader_name, model_shader_program, texture_ptr);
		}

	}


} // QuestEngine::API::OpenGL