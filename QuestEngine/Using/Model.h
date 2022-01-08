#pragma once
#include "QuestGLCore/Model/Model.h"

namespace QuestEngine::Model {
	using StandardModel = QuestGLCore::Model::Model<QuestGLCore::VertexData::VertexData>;
	using StandardMesh = QuestGLCore::Model::Mesh<QuestGLCore::VertexData::VertexData>;
	using IndexedModel = QuestGLCore::Model::Model<QuestGLCore::VertexData::IndexedVertexData>;
	using IndexedMesh = QuestGLCore::Model::Mesh<QuestGLCore::VertexData::IndexedVertexData>;
} // namespace QuestEngine::Model