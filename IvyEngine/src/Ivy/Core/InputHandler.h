#pragma once
#include "ivypch.h"

namespace Ivy{

	class InputHandler
	{
	public:
		~InputHandler() = default;

		inline static bool IsKeyPressed(unsigned int keycode) { return instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(unsigned int button) { return instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return instance->GetMouseYImpl(); }

	protected:
		InputHandler() = default;
		InputHandler(const InputHandler&) = delete;
		InputHandler& operator=(const InputHandler&) = delete;

		virtual bool IsKeyPressedImpl(unsigned int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(unsigned int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static std::shared_ptr<InputHandler> instance;

	};

}