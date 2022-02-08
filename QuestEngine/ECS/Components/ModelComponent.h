#pragma once
#include "QuestEngine/Using/Model.h"

namespace QuestEngine::ECS::Components {

	struct StandardModelComponent {
		explicit StandardModelComponent(Model::StandardModel* model)
			:m_model{ model } {
		}

		Model::StandardModel* m_model{ nullptr };
	};

	struct IndexedModelComponent {
		explicit IndexedModelComponent(Model::IndexedModel* model)
			:m_model{ model } {
		}

		Model::IndexedModel* m_model{ nullptr };
	};


} // QuestEngine::ECS::Components