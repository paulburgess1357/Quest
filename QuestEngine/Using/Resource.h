#pragma once
#include "QuestEngine/Resource/TResource.h"
#include "QuestGLCore/Include/Shader.h"
#include <string>

namespace QuestEngine::Resource {
	using ShaderResource = TResource<std::string, QuestGLCore::Shader::ShaderProgram>;
} // namespace QuestEngine::Resource