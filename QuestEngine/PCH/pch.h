#pragma once

// add headers that you want to pre-compile here
#include <Windows.h>
#include "framework.h"

// Resource
#include "QuestEngine/Resource/TResource.h"

// Camera
#include "QuestEngine/Camera/ProjectionMatrix.h"
#include "QuestEngine/Camera/Camera.h"

// Using
#include "QuestEngine/Using/Window.h"
#include "QuestEngine/Using/Resource.h"

// Systems
#include "QuestEngine/ECS/Systems/RenderSystem.h"
#include "QuestEngine/ECS/Systems/TransformSystem.h"

// Components
#include "QuestEngine/ECS/Components/ModelComponent.h"
#include "QuestEngine/ECS/Components/RotateComponent.h"

// ECS
#include "QuestEngine/ECS/Components/TransformComponent.h"
#include "QuestEngine/ECS/Components/RotateComponent.h"
#include "QuestEngine/ECS/Components/ModelComponent.h"

#include "QuestEngine/ECS/Manage/RegistryManager.h"
#include "QuestEngine/ECS/Manage/SystemManager.h"

#include "QuestEngine/ECS/Systems/RenderSystem.h"
#include "QuestEngine/ECS/Systems/TransformSystem.h"