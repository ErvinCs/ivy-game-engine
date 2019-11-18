#include "ivypch.h"
#include "ImGuiLayer.h"

#include "../imgui/imgui.h"
#include "../imgui/examples/imgui_impl_glfw.h"
#include "../ImGui/examples/imgui_impl_opengl3.h"

#include "../Core/Application.h"	//Care for dependency loop

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ivy {

	ImGuiLayer::ImGuiLayer()
		: SortingLayer("ImGuiLayer")
	{
	}


	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::update() 
	{
		/*ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::getInstance();
		io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());


		float currTime = (float)glfwGetTime();
		io.DeltaTime = this->time > 0.0 ? (currTime - this->time) : (1.0f / 60.0f);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/
	}

	void ImGuiLayer::onEvent(Event& event) 
	{
	}

	void ImGuiLayer::attach()  
	{
		/*ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplOpenGL3_Init("#version 450");
		*/
	}

	void ImGuiLayer::detach()  
	{

	}

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

		//Don't do this here
		glViewport(0, 0, event.getWidth(), event.getHeight());

		return false;
	}
}