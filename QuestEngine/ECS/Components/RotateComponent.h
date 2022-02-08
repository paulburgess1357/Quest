#pragma once

namespace QuestEngine::ECS::Components {
	struct RotateComponent {
		glm::vec3 m_axis{ 0.0f, 1.0f, 0.5f };
		float m_rate{ 0.01f };
	};
} // namespace QuestEngine::ECS::Components