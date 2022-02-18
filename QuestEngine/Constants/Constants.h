#pragma once
#include <string>

namespace QuestEngine::Constants {
	const std::string main_camera{ "main_camera " };
	const std::string ubo_matrices{ "ubo_matrices" };

	const std::string post_process_shader{ "post_process_shader" };
	const std::string pointlight_shader{"pointlight_lightpass_shader"};

	const std::string pointlight_model{"indexed_pointlight_model"};
	const std::string visualize_pointlight_model{ "visualize_pointlight_model" };
	const std::string visualize_pointlight_model_shader{ "visualize_pointlight_model_shader" };

	const std::string default_texture{ "default_texture" };
	const std::string default_diffuse_shader_name{ "all_textures.diffuse" };
}