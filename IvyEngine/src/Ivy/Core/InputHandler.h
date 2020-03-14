#pragma once


namespace Ivy{

	class InputHandler
	{
	public:
		~InputHandler() = default;

		inline static bool IsKeyDown(unsigned int keycode) { return instance->isKeyDownImpl(keycode); }
		inline static bool IsMouseButtonDown(unsigned int button) { return instance->isMouseButtonDownImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return instance->getMousePositionImpl(); }
		inline static float GetMouseX() { return instance->getMouseXImpl(); }
		inline static float GetMouseY() { return instance->getMouseYImpl(); }

	protected:
		InputHandler() = default;
		InputHandler(const InputHandler&) = delete;
		InputHandler& operator=(const InputHandler&) = delete;

		// TODO - Lowerecase these
		virtual bool isKeyDownImpl(unsigned int keycode) = 0;
		virtual bool isMouseButtonDownImpl(unsigned int button) = 0;
		virtual std::pair<float, float> getMousePositionImpl() = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;

	private:
		static std::unique_ptr<InputHandler> instance;

	};

}