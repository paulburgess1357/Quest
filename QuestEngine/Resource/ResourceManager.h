#pragma once
#include "QuestEngine/Using/Resource.h"

namespace QuestEngine::Resource {

	class ResourceManager {

	public:
		Shader::ShaderProgram& get_shader(const std::string& shader_id);
		void load_shader(const std::string& shader_id, const std::initializer_list<std::pair<Shader::ShaderEnum, std::string>> shaders);

	private:
		ShaderResource m_shader_resource;
	};

} // namespace QuestEngine::Resource