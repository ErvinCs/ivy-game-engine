#include "ivypch.h"
#include "RenderCommand.h"

#include "OpenGL/OpenGLRenderAPI.h"

namespace Ivy {

	RenderAPI* RenderCommand::renderAPI = new OpenGLRenderAPI();

}