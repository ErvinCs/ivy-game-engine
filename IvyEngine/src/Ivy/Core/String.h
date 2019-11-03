#pragma once

//#include "../../ivypch.h"
//#include <cwchar>
//#include <string>

namespace Ivy {
	class String
	{
	private:
		wchar_t* string;
		size_t size;

	public:
		String();
		String(const char* other);
		String(const wchar_t* other);
		String(const String& other);
		~String();

		inline const size_t getSize() const
		{
			return size;
		}

		inline const wchar_t* getRawWString() const
		{
			return string;
		}

		inline const char* getRawCString() const
		{
			return convertWStringToCString(this->string);
		}

		static wchar_t* convertCStringToWString(const char* cString)
		{
			size_t size = strlen(cString) + 1;
			wchar_t* string = new wchar_t[size];
			mbstowcs(string, cString, size);
			//free cString
			return string;
		}

		static char* convertWStringToCString(const wchar_t* wString)
		{
			size_t size = wcslen(wString) + 1;
			char* string = new char[size];
			wcstombs(string, wString, size);
			//free wString
			return string;
		}

		inline bool operator==(const String& other)
		{
			return !wcsncmp(getRawWString(), other.getRawWString(), getSize());
		}
		inline bool operator!=(const String& other)
		{
			return wcsncmp(getRawWString(), other.getRawWString(), getSize());
		}

		#ifdef IVY_PLATFORM_WINDOWS

		static String getFileName(const String& fullPath)
		{
			
			wchar_t* lastSeparator;
			wcscpy(lastSeparator, wcsrchr(fullPath.getRawWString(), L'/') + 1);
			return String(lastSeparator);
		}

		static String getFileExtension(const String& fullPath)
		{
			wchar_t* lastSeparator;
			wcscpy(lastSeparator, wcsrchr(fullPath.getRawWString(), L'.') + 1);
			return String(lastSeparator);
		}

		#endif
	};
}