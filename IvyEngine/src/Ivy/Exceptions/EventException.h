#pragma once

#include <exception>
#include <string>

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
