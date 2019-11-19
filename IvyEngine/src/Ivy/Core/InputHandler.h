#pragma once


namespace Ivy{

	class InputHandler
	{
	public:
		~InputHandler() = default;

		inline static bool IsKeyDown(unsigned int keycode) { return instance->IsKeyDownImpl(keycode); }

		inline static bool IsMouseButtonDown(unsigned int button) { return instance->IsMouseButtonDownImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return instance->GetMouseYImpl(); }

	protected:
		InputHandler() = default;
		InputHandler(const InputHandler&) = delete;
		InputHandler& operator=(const InputHandler&) = delete;

		virtual bool IsKeyDownImpl(unsigned int keycode) = 0;

		virtual bool IsMouseButtonDownImpl(unsigned int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static std::unique_ptr<InputHandler> instance;

	};

}