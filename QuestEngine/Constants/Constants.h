#pragma once
#include <string>

namespace QuestEngine::Constants {
	const std::string main_camera{ "main_camera " };
	const std::string ubo_matrices{ "ubo_matrices" };
	const std::string post_process_shader{ "post_process_shader" };
	const std::string g_buffer_light_pass{ "g_buffer_light_pass" };
	const std::string pointlight_shader{"pointlight_g_buffer_shader"};
	const std::string pointlight_model{"indexed_pointlight_model"};
}