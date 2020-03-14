#pragma once

#include <exception>
#include <string>

class ComponentNotFoundException
{
protected:
	std::string message;

public:
	ComponentNotFoundException() noexcept
	{
		this->message = "";
	}

	explicit ComponentNotFoundException(const std::string& msg)
	{
		this->message = msg;
	}

	virtual const char* what()
	{
		return message.c_str();
	}
};