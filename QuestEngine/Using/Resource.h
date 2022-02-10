#pragma once
#include "QuestEngine/Resource/TResource.h"
#include "QuestEngine/Camera/Camera.h"
#include "QuestEngine/Using/Shader.h"
#include "QuestEngine/Using/Model.h"
#include "QuestEngine/Using/UniformBufferObjects.h"
#include <string>

namespace QuestEngine::Resource {
	using ShaderResource = TResource<std::string, Shader::ShaderProgram>;
	using StandardModelResource = TResource<std::string, Model::StandardModel>;
	using IndexedModelResource = TResource<std::string, Model::IndexedModel>;
	using CameraResource = TResource<std::string, Camera::Camera>;
	using UBOResource = TResource<std::string, UniformBufferObjects::UniformBufferObject>;
} // namespace QuestEngine::Resource