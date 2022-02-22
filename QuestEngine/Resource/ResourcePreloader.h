#pragma once
#include "QuestEngine/Resource/ResourceManager.h"

namespace QuestEngine::Resource {

	class ResourcePreloader {

	public:
		static void preload_resources(ResourceManager& resource_manager);

	private:
		static void load_ubo_matrices(ResourceManager& resource_manager);
		static void load_default_texture(ResourceManager& resource_manager);

		// TODO this likely won't be a default loaded shader
		static void load_standard_object_gbuffer_shader(ResourceManager& resource_manager);
		static void load_standard_object_forward_shader(ResourceManager& resource_manager);
		static void load_pointlight_shaders(ResourceManager& resource_manager);
		static void load_visualize_pointlight_shader(ResourceManager& resource_manager);
		static void load_postprocess_shader(ResourceManager& resource_manager);

		static void load_pointlight_model(ResourceManager& resource_manager);
		static void load_pointlight_visual_model(ResourceManager& resource_manager);
		static void load_main_camera(ResourceManager& resource_manager);

		static std::string m_resource_base;
	};


} // namespace QuestEngine::Resource