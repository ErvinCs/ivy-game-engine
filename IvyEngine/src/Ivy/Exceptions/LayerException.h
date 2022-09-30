#pragma once

#include <exception>
#include <string>


namespace Ivy {
	/**
	 * Thrown by the LayerStack on attempting to pop an unexistent layer.
	 * @see LayerStack
	 */
	class LayerException : public std::exception
	{
	protected:
		std::string message;

	public:
		LayerException() noexcept
		{
			this->message = "";
		}

		explicit LayerException(const std::string& msg)
		{
			this->message = msg;
		}

		virtual const char* what()
		{
			return message.c_str();
		}
	};
}