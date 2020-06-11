#pragma once

#include <exception>
#include <string>


namespace Ivy
{

	/**
	 * Thrown if an EventHandler assignment(=) operations fails
	 * @see EventHandler
	 */
	class EventException
	{
	protected:
		std::string message;

	public:
		EventException() noexcept
		{
			this->message = "";
		}

		explicit EventException(const std::string& msg)
		{
			this->message = msg;
		}

		virtual const char* what()
		{
			return message.c_str();
		}
	};

}