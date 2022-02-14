#pragma once

#include <Windows.h>
#include "framework.h"

// Engine
#include "QuestEngine/Engine/Engine.h"

// Resource
#include "QuestEngine/Resource/TResource.h"
#include "QuestEngine/Resource/ResourceManager.h"

// Camera
#include "QuestEngine/Camera/ProjectionMatrix.h"
#include "QuestEngine/Camera/Camera.h"

// Using
#include "QuestEngine/Using/Window.h"
#include "QuestEngine/Using/Resource.h"
#include "QuestEngine/Using/API.h"
#include "QuestEngine/Using/Model.h"
#include "QuestEngine/Using/Shader.h"
#include "QuestEngine/Using/Texture.h"
#include "QuestEngine/Using/UniformBufferObjects.h"
#include "QuestEngine/Using/Framebuffer.h"

// ECS
#include "QuestEngine/ECS/Components/TransformComponent.h"
#include "QuestEngine/ECS/Components/RotateComponent.h"
#include "QuestEngine/ECS/Components/ModelComponent.h"

#include "QuestEngine/ECS/Manage/RegistryManager.h"
#include "QuestEngine/ECS/Manage/SystemManager.h"

#include "QuestEngine/ECS/Systems/RenderSystem.h"
#include "QuestEngine/ECS/Systems/TransformSystem.h"

// API
#include "QuestEngine/API/Neutral/EngineAPI.h"
#include "QuestEngine/API/Neutral/RegistryAPI.h"
#include "QuestEngine/API/Neutral/ResourceAPI.h"

#include "QuestEngine/API/OpenGL/ModelLoaderAPI.h"
#include "QuestEngine/API/OpenGL/ShaderLoaderAPI.h"
#include "QuestEngine/API/OpenGL/TextureLoaderAPI.h"
#include "QuestEngine/API/OpenGL/ModelLoaderExceptions.h"

// UBO
#include "QuestEngine/UniformBufferObjects/UniformBufferManager.h"

// Texture
#include "QuestEngine/Texture/TextureType.h"

// Misc
#include "QuestEngine/Constants/Constants.h"