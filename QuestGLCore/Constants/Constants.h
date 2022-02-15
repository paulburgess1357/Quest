#pragma once
#include <string>

namespace QuestGLCore::Constants {
	const std::string model_matrix{ "model_matrix" };
	const std::string normal_matrix{ "normal_matrix" };
	const std::string view_matrix{ "view_matrix" };
	const std::string projection_matrix{ "projection_matrix" };
	constexpr bool gamma_enabled{ true }; // Post-process shader
}