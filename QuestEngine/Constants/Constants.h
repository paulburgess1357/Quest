#pragma once
#include <string>

namespace QuestEngine::Constants {
	const std::string main_camera{ "main_camera " };

	// Matrices
	const std::string ubo_matrices{ "ubo_matrices" };
	const std::string model_matrix{ "model_matrix" };

	// Shaders
	const std::string post_process_shader{ "post_process_shader" };
	const std::string pointlight_shader{"pointlight_lightpass_shader"};
	const std::string visualize_pointlight_shader{ "visualize_pointlight_model_shader" };
	const std::string standard_deferred_object_shader{ "standard_object_deferred_shader" };
	const std::string standard_forward_object_shader{ "standard_object_forward_shader" };

	// Models
	const std::string pointlight_model{"indexed_pointlight_model"};
	const std::string visualize_pointlight_model{ "visualize_pointlight_model" };

	// Textures
	const std::string default_texture{ "default_texture" };
}