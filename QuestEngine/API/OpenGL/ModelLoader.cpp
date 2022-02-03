#include "pch.h"
#include "ModelLoader.h"

namespace QuestEngine::API::OpenGL {

	ModelLoader::ModelLoader(const QuestEngineAPI& engine_api)
		:m_engine_api{ engine_api } {
	}

	//std::vector<QuestGLCore::Model::Mesh<QuestGLCore::VertexData::VertexData>> ModelLoader::create_model(const std::string& shader_program_name, const std::vector<float>& vertices, const std::vector<int>& vertex_description) {
	//	// 1) Load shader program (via OpenGLShaderLoader)
	//	// 2) Load model (e.g. use shader_program_name to get ptr to loaded shader.  Use that to construct the model).  Load model into m_engine_api.
	//}

		


} // namespace QuestEngine::API::OpenGL