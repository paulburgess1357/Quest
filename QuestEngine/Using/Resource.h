#pragma once
#include "QuestEngine/Resource/TResource.h"
#include "QuestEngine/Using/Shader.h"
#include <string>

namespace QuestEngine::Resource {
	using ShaderResource = TResource<std::string, Shader::ShaderProgram>;
} // namespace QuestEngine::Resource