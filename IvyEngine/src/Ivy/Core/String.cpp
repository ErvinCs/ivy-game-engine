#include "ivypch.h"
#include "String.h"

namespace Ivy {

	//TODO - Test for memory leaks

	String::String()
	{
		this->size = 0;
		this->string = '\0';
	}

	String::String(const char* s)
	{
		this->size = strlen(s) + 1;
		this->string = convertCStringToWString(s);
		//free s
	}

	String::String(const wchar_t* other)
	{
		this->size = wcslen(other) + 1;
		wcscpy(this->string, other);
		//free other
	}

	String::String(const String& other)
	{
		this->size = other.size;
		this->string = new wchar_t[this->size];
		wcscpy(this->string, other.getRawWString());
	}

	String::~String()
	{
		this->size = 0;
		delete[] string;
	}

}