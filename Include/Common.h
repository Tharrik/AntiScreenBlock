#ifndef COMMON_H
#define COMMON_H

#include <string>

#include "SFML/Graphics.hpp"

#if (__cplusplus == 199711L)
	#error Enable C++ Version verification in the project. Go to Configuration Properties > C/C++ > Command Line property page. Add /Zc:__cplusplus or to the Additional options pane.
#endif

#if (__cplusplus <= 201103L)
	std::wstring StringToWString(const char* text)
	{
		std::string str(text);
		std::wstring wstr(str.begin(), str.end());
		return wstr;
	}
	#define FUNCTION_NAME StringToWString(__FUNCTION__).data()
#else
	#define FUNCTION_NAME __FUNCTIONW__
#endif

#define ERROR_MESSAGE_SIZE 512
extern wchar_t* gErrorMessage;

extern sf::RenderWindow* gWindow;

#endif // !COMMON_H