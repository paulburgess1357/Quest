#include "pch.h"
#include "ResourcePreloader.h"
#include "QuestEngine/Using/Model.h"
#include "QuestUtility/String/FileToString.h"
#include "QuestUtility/Sphere/Sphere.h"

namespace QuestEngine::Resource {

	std::string ResourcePreloader::m_resource_base{ "../Resources/" };

	void ResourcePreloader::preload_resources(ResourceManager& resource_manager){
		load_ubo_matrices(resource_manager);
		load_default_texture(resource_manager);

		load_standard_object_shader(resource_manager);
		load_pointlight_shaders(resource_manager);
		load_visualize_pointlight_shader(resource_manager);
		load_postprocess_shader(resource_manager);
		
		load_pointlight_model(resource_manager);
		load_pointlight_visual_model(resource_manager);
		load_main_camera(resource_manager);
	}

	// ======================== Shader ========================

	void ResourcePreloader::load_standard_object_shader(ResourceManager& resource_manager) {


		// TODO this likely won't be a default loaded shader


		const std::string vertex = QuestUtility::String::FileToString::load(m_resource_base + "Shaders/GBuffer/GBufferShapeVertexGeometryPassDualTextured.glsl");
		const std::string fragment = QuestUtility::String::FileToString::load(m_resource_base + "Shaders/GBuffer/GBufferShapeFragmentGeometryPassDualTextured.glsl");
		const std::unordered_map<Shader::ShaderEnum, std::string> shader_map{
			{ Shader::ShaderEnum::VERTEX, vertex },
			{ Shader::ShaderEnum::FRAGMENT, fragment }
		};
		resource_manager.load_shader(Constants::standard_object_shader, shader_map, true);
	}

	void ResourcePreloader::load_pointlight_shaders(ResourceManager& resource_manager){
		const std::string vertex = QuestUtility::String::FileToString::load(m_resource_base + "Shaders/Pointlight/PointlightVertexLightpass.glsl");
		const std::string fragment = QuestUtility::String::FileToString::load(m_resource_base + "Shaders/Pointlight/PointlightFragmentLightpass.glsl");
		const std::unordered_map<Shader::ShaderEnum, std::string> shader_map{
			{ Shader::ShaderEnum::VERTEX, vertex },
			{ Shader::ShaderEnum::FRAGMENT, fragment }
		};
		resource_manager.load_shader(Constants::pointlight_shader, shader_map, true);

		Shader::ShaderProgram& shader = resource_manager.get_shader(Constants::pointlight_shader);
		shader.bind();
		shader.set_uniform("all_textures.position", 0);
		shader.set_uniform("all_textures.normals", 1);
		shader.set_uniform("all_textures.color_spec", 2);
		shader.unbind();
	}

	void ResourcePreloader::load_visualize_pointlight_shader(ResourceManager& resource_manager){
		// Forward Pass Shaders
		const std::string vertex = QuestUtility::String::FileToString::load(m_resource_base + "Shaders/ForwardPass/ForwardPassVertexTextured.glsl");
		const std::string fragment = QuestUtility::String::FileToString::load(m_resource_base + "Shaders/ForwardPass/ForwardPassFragmentTextured.glsl");

		// Deferred Pass Shaders
		// const std::string vertex = QuestUtility::String::FileToString::load(m_resource_base + "Shaders/GBuffer/GBufferShapeVertexGeometryPassSingleTextured.glsl");
		// const std::string fragment = QuestUtility::String::FileToString::load(m_resource_base + "Shaders/GBuffer/GBufferShapeFragmentGeometryPassSingleTextured.glsl");

		const std::unordered_map<Shader::ShaderEnum, std::string> shader_map{
			{ Shader::ShaderEnum::VERTEX, vertex },
			{ Shader::ShaderEnum::FRAGMENT, fragment }
		};
		resource_manager.load_shader(Constants::visualize_pointlight_shader, shader_map, true);
	}

	void ResourcePreloader::load_postprocess_shader(ResourceManager& resource_manager){
		const std::string vertex = QuestUtility::String::FileToString::load(m_resource_base + "Shaders/PostProcess/PostProcessVertex.glsl");
		const std::string fragment = QuestUtility::String::FileToString::load(m_resource_base + "Shaders/PostProcess/PostProcessFragment.glsl");
		const std::unordered_map<Shader::ShaderEnum, std::string> shader_map{
			{ Shader::ShaderEnum::VERTEX, vertex },
			{ Shader::ShaderEnum::FRAGMENT, fragment }
		};
		resource_manager.load_shader(Constants::post_process_shader, shader_map, false);

		Shader::ShaderProgram& shader = resource_manager.get_shader(Constants::post_process_shader);
		shader.bind();
		shader.set_uniform("post_process_texture", 0);
		shader.unbind();
	}

	// ======================== Texture ========================

	void ResourcePreloader::load_default_texture(ResourceManager& resource_manager){
			const QuestUtility::ImageLoading::StandardImageLoaderFromFile image_loader{ m_resource_base + "Textures/default_texture.png", false };
			const Texture::StandardTextureCreator2D texture_creator{ image_loader, true };
			Texture::Texture texture{ texture_creator.generate_texture() };
			resource_manager.load_texture2D(Constants::default_texture, texture);
	}

	// ======================== Model ========================

	void ResourcePreloader::load_pointlight_model(ResourceManager& resource_manager){
		const Sphere sphere_creator{ 3.0f, 30, 30, false }; // Radius = 1.0

		// Note that currently the spheres are not being scaled by the distance
		// the light can travel! That can cause the circular lines as its an area
		// where the sphere stops!

		// ======== Standard Pointlight Model ========
		// Sphere with position information only (used for pointlights)
		Shader::ShaderProgram& shader = resource_manager.get_shader(Constants::pointlight_shader);
		auto pointlight_model = Model::ModelCreator::create_model(shader, { sphere_creator.getVerticesVector() }, { sphere_creator.getIndiciesVector() }, { 3 }, Model::ModelDrawMode::Triangles);
		resource_manager.load_model(Constants::pointlight_model, pointlight_model);
	}

	void ResourcePreloader::load_pointlight_visual_model(ResourceManager& resource_manager){
		const Sphere sphere_creator{ 1.0f, 30, 30, false }; // Radius = 1.0

		// ======== Textured Pointlight Model ========
		// Sphere with position, normals, and texture coords (used to help visualize where pointlights are located)
		Shader::ShaderProgram& model_texture_shader = resource_manager.get_shader(Constants::visualize_pointlight_shader);
		auto visualize_pointlight_model = Model::ModelCreator::create_model(model_texture_shader, { sphere_creator.getInterleavedVerticesVector() }, { sphere_creator.getIndiciesVector() }, { 3, 3, 2 }, Model::ModelDrawMode::Triangles);
		resource_manager.load_model(Constants::visualize_pointlight_model, visualize_pointlight_model);

		// Get pointer to loaded model
		Model::IndexedModel* model_pointer = resource_manager.get_indexed_model_pointer(Constants::visualize_pointlight_model);

		// Get pointer to model's shader
		const auto texture_ptr = resource_manager.get_texture_ptr(Constants::default_texture);

		// For each mesh, register the texture
		auto& mesh_vector = model_pointer->get_mesh_vector();
		for (auto& model_mesh : mesh_vector) {
			model_mesh.register_texture(Texture::TextureEnum::Diffuse, &model_texture_shader, texture_ptr);
		}
	}

	// ====================== Uniform Buffer Objects ======================

	void ResourcePreloader::load_ubo_matrices(ResourceManager& resource_manager){
			const std::string ubo_id{ Constants::ubo_matrices };
			UniformBufferObjects::UniformBufferObject ubo{ ubo_id };
			ubo.allocate_buffer_memory(sizeof(glm::mat4) * 2);
			resource_manager.load_ubo(ubo_id, ubo);
	}

	// ======================== Camera ========================

	void ResourcePreloader::load_main_camera(ResourceManager& resource_manager){
		resource_manager.load_camera(Constants::main_camera, { 0.0f, 0.0f, -6.0f }, { 0.0f, 0.0f, 0.0f });
	}

} // namespace QuestEngine::Resource