#pragma once
#include "QuestEngine/API/EngineAPI.h"

namespace QuestEngine::API::OpenGL {

	class ModelLoader {

	public:
		ModelLoader(const QuestEngineAPI& engine_api);
		//std::vector<QuestGLCore::Model::Mesh<QuestGLCore::VertexData::VertexData>> create_model(const std::string& shader_program_name, const std::vector<float>& vertices, const std::vector<int>& vertex_description);

		//TODO do the same for indexed model
		//TODO for textures later on, possible add something lile 'attach texture' to a specific model name? E.g. If i have a loaded box, I can then say attach texture and the box uses that texture...  Seems more intuitive than attaching to the shader program.  Still need to create texture handler.




	private:
		const QuestEngineAPI& m_engine_api;
	};

} // namespace QuestEngine::API::OpenGL