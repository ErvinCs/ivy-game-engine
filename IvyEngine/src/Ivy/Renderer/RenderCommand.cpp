#include "ivypch.h"
#include "RenderCommand.h"

#include "OpenGL/OpenGLRenderAPI.h"

namespace Ivy {

	std::unique_ptr<RenderAPI> RenderCommand::renderAPI = RenderAPI::Create();

}