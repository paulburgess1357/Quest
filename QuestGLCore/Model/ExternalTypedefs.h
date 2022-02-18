#pragma once
#include "QuestGLCore/Model/Model.h"
#include "QuestGLCore/Model/MeshQuad.h"

namespace QuestGLCore::Model {
	using StandardModel = Model<QuestGLCore::VertexData::VertexData>;
	using StandardMesh = Mesh<QuestGLCore::VertexData::VertexData>;
	using IndexedModel = Model<QuestGLCore::VertexData::IndexedVertexData>;
	using IndexedMesh = Mesh<QuestGLCore::VertexData::IndexedVertexData>;
	using IndexedMeshQuad = IndexedMeshQuad;
} // namespace QuestEngine::Model