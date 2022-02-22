#pragma once
#include <string>

namespace QuestGLCore::Constants {
	const std::string model_matrix{ "model_matrix" };
	const std::string normal_matrix{ "normal_matrix" };
	const std::string view_matrix{ "view_matrix" };
	const std::string projection_matrix{ "projection_matrix" };
	constexpr bool gamma_enabled{ true }; // Post-process shader

	const std::string default_diffuse_shader_name{ "all_textures.diffuse" };
	const std::string default_specular_shader_name{ "all_textures.specular" };
	const std::string default_normal_shader_name{ "all_textures.normal" };

}