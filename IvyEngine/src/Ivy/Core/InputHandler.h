#pragma once

#include "Logger.h"

namespace Ivy{
	/*
	 *
	 */
	class InputHandler
	{
	public:
		~InputHandler() = default;

		inline static bool IsKeyDown(unsigned int keycode) 
		{
			//IVY_CORE_TRACE("InputHandler: IsKeyDown: keycode={0}", keycode); 
			return instance->isKeyDownImpl(keycode);
		}
		inline static bool IsMouseButtonDown(unsigned int button) 
		{
			//IVY_CORE_TRACE("InputHandler: IsMouseButtonDown: button={0}", button); 
			return instance->isMouseButtonDownImpl(button);
		}
		inline static std::pair<float, float> GetMousePosition() 
		{ 
			//IVY_CORE_TRACE("InputHandler: GetMousePosition");
			return instance->getMousePositionImpl(); 
		}
		inline static float GetMouseX() 
		{ 
			//IVY_CORE_TRACE("InputHandler: GetMouseX");
			return instance->getMouseXImpl(); 
		}
		inline static float GetMouseY() 
		{ 
			//IVY_CORE_TRACE("InputHandler: GetMouseY");
			return instance->getMouseYImpl(); 
		}

		inline static std::unique_ptr<InputHandler>& GetInstance() { return instance; }

	protected:
		InputHandler() = default;
		InputHandler(const InputHandler&) = delete;
		InputHandler& operator=(const InputHandler&) = delete;

		virtual bool isKeyDownImpl(unsigned int keycode) = 0;
		virtual bool isMouseButtonDownImpl(unsigned int button) = 0;
		virtual std::pair<float, float> getMousePositionImpl() = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;

	private:
		static std::unique_ptr<InputHandler> instance;
		
	};

}