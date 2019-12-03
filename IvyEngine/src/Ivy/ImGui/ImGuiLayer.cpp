#include "ivypch.h"
#include "ImGuiLayer.h"

#include "../imgui/imgui.h"
#include "examples/imgui_impl_opengl3.h"
#include "examples/imgui_impl_glfw.h"

#include "../Core/Application.h"	//Care for dependency loop

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ivy {

	ImGuiLayer::ImGuiLayer()
		: SortingLayer("ImGuiLayer")
	{
		gladLoadGL();
	}


	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::begin()
	{
		// Begin ImGui Window rendering
		// Each layer should be able to manage its own rendering
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::end()
	{
		// End ImGui Window Rendering
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::getApplication();
		io.DisplaySize = ImVec2((float)app.getWindow().getWidth(), (float)app.getWindow().getHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/*if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}*/
	}

	void ImGuiLayer::imGuiRender() 
	{
		static bool show = false;
		ImGui::ShowDemoWindow(&show);
	}

	void ImGuiLayer::attach()  
	{
		//IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui::StyleColorsDark();

		/*ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}*/

		Application& app = Application::getApplication();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.getWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings [for OpenGL only atm]
		const char opengl_version[] = "#version 440";
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(opengl_version);
	}

	void ImGuiLayer::detach()  
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	/*
	bool ImGuiLayer::onKeyDownEvent(KeyDownEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.getKeyCode()] = true;

		return false;
	}

	bool ImGuiLayer::onKeyUpEvent(KeyUpEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.getKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::onMouseButtonDownEvent(MouseButtonDownEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.getMouseButton()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL || GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT || GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT || GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER || GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::onMouseButtonUpEvent(MouseButtonUpEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.getMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::onMouseMoveEvent(MouseMoveEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(event.getX(), event.getY());

		return false;
	}

	bool ImGuiLayer::onMouseScrollEvent(MouseScrollEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel  += event.getYOffset();
		io.MouseWheelH += event.getXOffset();

		return false;
	}

	bool ImGuiLayer::onWindowReseizeEvent(WindowResizeEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(event.getWidth(), event.getHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

		// TODO: Abstract this
		glViewport(0, 0, event.getWidth(), event.getHeight());

		return false;
	}*/
}