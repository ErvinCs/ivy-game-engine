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

		inline String operator+=(const String& other)
		{
			size_t oldSize = this->getSize();
			this->size += other.getSize() - 1;			// Delete one \0
			wchar_t* concatString = new wchar_t[size];
			wmemcpy(concatString, this->string, oldSize);
			wcscat(concatString, other.getRawWString());

			delete[] string;

			this->string = concatString;
			return *this;
		}

		inline String operator+(const String& other)
		{
			size_t resultSize = this->getSize() + other.getSize() - 1;		// Delete one \0
			wchar_t* concatString = new wchar_t[resultSize];
			wmemcpy(concatString, this->string, this->size);
			wcscat(concatString, other.getRawWString());

			return String(concatString);
		}

		friend std::ostream& operator<<(std::ostream& out, const String& string)
		{
			out << string.getRawCString();
			return out;
		}

		static String getFileName(const String& fullPath)
		{
			
			wchar_t* lastSeparator;
			#ifdef IVY_PLATFORM_WINDOWS
				wcscpy(lastSeparator, wcsrchr(fullPath.getRawWString(), L'/') + 1);
			#else
				wcscpy(lastSeparator, wcsrchr(fullPath.getRawWString(), L'\\') + 1);
			#endif
			return String(lastSeparator);
		}

		static String getFileExtension(const String& fullPath)
		{
			wchar_t* lastSeparator;
			wcscpy(lastSeparator, wcsrchr(fullPath.getRawWString(), L'.') + 1);
			return String(lastSeparator);
		}


	};
}