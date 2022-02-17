#pragma once
#include <exception>

namespace QuestEngine::ECS {

	class EntityLoadRenderPassException final : public std::exception {
		[[nodiscard]] const char* what() const override {
			return "Unable to load entity with the specified render pass! Be sure to update how this entity needs to be loaded into the rendering system.";
		}
	};

} // namespace QuestGLCore::ShaderProgram