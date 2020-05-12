#pragma once

#include <exception>
#include <string>


namespace Ivy
{
	/**
	 *
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