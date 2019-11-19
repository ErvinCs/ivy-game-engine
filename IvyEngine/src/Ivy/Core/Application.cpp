#include "ivypch.h"
#include "Application.h"

//#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Logger.h"
#include "InputHandler.h"

// -------------------- TEMP --------------------
#include "../Renderer/OpenGL/OpenGLIndexBuffer.h"
#include "../Renderer/OpenGL/OpenGLVertexBuffer.h"
#include "../Renderer/OpenGL/OpenGLVertexBufferLayout.h"
#include "../Renderer/OpenGL/OpenGLVertexArray.h"
#include "../Renderer/OpenGL/OpenGLShader.h"
#include "../Renderer/OpenGL/OpenGLTexture.h"
#include "../Renderer/OpenGL/OpenGLRenderer.h"
// ----------------------------------------------

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../imgui/imgui.h"
//#include "examples/imgui_impl_opengl3.h"
//#include "examples/imgui_impl_glfw.h"

namespace Ivy {

	Application* Application::instance = nullptr;

	Application::Application()
	{
		instance = this;
		window = std::unique_ptr<Window>(Window::Create());
		
		window->setCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		//IVY_CORE_INFO("{0}",glGetString(GL_VERSION));


		imGuiLayer = new ImGuiLayer();
		pushLayer(imGuiLayer);
	}


	Application::~Application()
	{
		//delete imGuiLayer;
	}

	void Application::Init()
	{
		memoryManager.init();
		fileManager.init();
		inputManager.init();
		rendererManager.init();
	}

	void Application::Run()
	{
		// -------------------- TEMP --------------------
		const float positions[] = {
		   -50.0f,  -50.0f, 0.0f, 0.0f,	//0
			50.0f,  -50.0f, 1.0f, 0.0f,	//1
			50.0f,   50.0f, 1.0f, 1.0f,	//2
		   -50.0f,   50.0f, 0.0f, 1.0f	//3
		};
		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		OpenGLRenderer renderer;
		renderer.init();

		OpenGLVertexArray va;
		OpenGLVertexBuffer vb(positions, 4 * 4 * sizeof(float));
		OpenGLVertexBufferLayout layout;

		layout.push<float>(2);
		layout.push<float>(2);
		va.addVertexBuffer(vb, layout);

		OpenGLIndexBuffer ib(indices, 6);

		// Math
		glm::mat4 projection = glm::ortho(0.0f, 1024.0f, 0.0f, 800.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::vec3 translation(200, 200, 0);

		// Shader
		OpenGLShader shader("C:/Workspace/ivy-game-engine/IvyEngine/res_temp/shaders/image.shader");
		shader.bind();
		//shader.setUniform4f("u_color", 0.2f, 0.3f, 0.8f, 1.0f);

		// Texture
		OpenGLTexture texture("C:/Workspace/ivy-game-engine/IvyEngine/res_temp/textures/cat1.png");
		texture.bind(0);
		shader.setUniform1i("u_texture", 0);

		va.unbind();
		vb.unbind();
		ib.unbind();
		shader.unbind();
		// ----------------------------------------------

		while (isRunning)
		{
			//memoryManager.run();
			//fileManager.run();
			//inputManager.run();
			//rendererManager.run();
			
			imGuiLayer->begin();
			for (SortingLayer* layer : layerStack)
				layer->imGuiRender();
			// -------------------- TEMP --------------------
			{
				// Model Matrix & MVP calculation
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
				glm::mat4 mvp = projection * view * model;
				// Bind shader - inefficient, the shader is already bound after the 1st frame
				shader.bind();
				// Bind uniform & issue draw calls
				shader.setUniformMat4f("u_mvp", mvp);
				renderer.draw(va, ib, shader);
			}
			{
				// Modify the translation from the gui
				ImGui::SliderFloat(" Translation1-X", &translation.x, 0.0f, 800.0f);
				ImGui::SliderFloat(" Translation1-Y", &translation.y, 0.0f, 600.0f);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}
			// ----------------------------------------------
			imGuiLayer->end();

			window->update();
		}
	}

	void Application::Shutdown()
	{
		rendererManager.shutdown();
		inputManager.shutdown();
		fileManager.shutdown();
		memoryManager.shutdown();
	}

	void Application::pushLayer(SortingLayer* layer)
	{
		this->layerStack.push(layer);
		layer->attach();
	}

	void Application::onEvent(Event& event)
	{
		// TODO - Propagate event through layers (iterate from end to begin)
		//IVY_CORE_WARN("OnEvent: {0}", event.toString());
		event();
		//event();	//TODO - call event in the update loop at some event processing stage, use EventHandles
	}

	bool Application::onWindowClose(WindowCloseEvent& event)
	{
		isRunning = false;
		return true;
	}
}