#pragma once

//-------------------- Core --------------------
#include "Ivy/Core/Application.h"
#include "Ivy/Core/Logger.h"
#include "Ivy/Core/SortingLayerStack.h"
#include "Ivy/Core/Timestep.h"

//-------------------- ImGui --------------------
#include "Ivy/ImGui/ImGuiLayer.h"

//-------------------- InputHandling --------------------
#include "Ivy/Windows/GLFWKeyCodes.h"
#include "Ivy/Core/InputHandler.h"

//-------------------- Rendering --------------------
#include "Ivy/Renderer/Renderer.h"
#include "Ivy/Renderer/RenderCommand.h"
#include "Ivy/Renderer/VertexBufferLayout.h"
#include "Ivy/Renderer/IndexBuffer.h"
#include "Ivy/Renderer/VertexBuffer.h"
#include "Ivy/Renderer/VertexArray.h"
#include "Ivy/Renderer/Shader.h"
#include "Ivy/Renderer/Texture.h"
#include "Ivy/Renderer/OrthoCamera.h"

//-------------------- ECS --------------------
#include "Ivy/ECS/Entity.h"
#include "Ivy/ECS/System.h"
#include "Ivy/ECS/Component.h"
#include "Ivy/ECS/ECS.h"
#include "Ivy/ECS/RenderSystem.h"
#include "Ivy/ECS/ScriptSystem.h"
#include "Ivy/ECS/CollisionSystem.h"
#include "Ivy/ECS/Components/Transform.h"
#include "Ivy/ECS/Components/Renderable.h"
#include "Ivy/ECS/Components/ScriptComponent.h"
#include "Ivy/ECS/Components/Tag.h"
#include "Ivy/ECS/Components/Collidable.h"
#include "Ivy/ECS/JSONManager.h"

//-------------------- Scripting --------------------
#include "Ivy/Scripting/ScriptableObject.h"
#include "Ivy/Scripting/ScriptManager.h"