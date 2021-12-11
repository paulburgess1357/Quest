#pragma once
#include "QuestEngine/Using/Resource.h"

namespace QuestEngine::Resource {

	class ResourceManager {

	public:
		QuestGLCore::Shader::ShaderProgram& get_shader(const std::string& shader_id);
		void load_shader(const std::string& shader_id, const std::initializer_list<std::pair<QuestGLCore::Shader::ShaderEnum, std::string>> shaders);

	private:
		Resource::ShaderResource m_shader_resource;
	};

} // namespace QuestEngine::Resource