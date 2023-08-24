#pragma once

#include <iostream>

// MACROS
#define ARG_MARKER_A(text) "/"##text
#define ARG_MARKER_B(text) "-"##text
#define ARG_VERIFY(text1, text2) strcmp(text1, ARG_MARKER_A(text2)) == 0 || strcmp(text1, ARG_MARKER_B(text2)) == 0

// ARGUMENTS
#define ARG_TIME(arg) ARG_VERIFY(arg, "t")
int argTimeInMilliseconds = 120000;

#define ARG_DISPLACEMENT_X(arg) ARG_VERIFY(arg, "dx")
#define ARG_DISPLACEMENT_Y(arg) ARG_VERIFY(arg, "dy")
POINT argDisplacement{1, 0};

#define ARG_SHOW(arg) ARG_VERIFY(arg, "s")
bool argHideWindow = true;

#define ARG_FPS(arg) ARG_VERIFY(arg, "fps")
int argFPS = 30;

void ReadArguments(LPWSTR args)
{
	std::wstring _argsW = args;
	std::string _args(_argsW.begin(), _argsW.end());


	std::string word;
	for (size_t i = 0; i <= _args.size(); ++i)
	{
		if (i == _args.size() || _args[i] == ' ')
		{
			if (ARG_TIME(word.data()))
			{
				word.clear();

				for (++i; i < _args.size() && _args[i] != ' '; ++i)
				{
					word += _args[i];
				}

				argTimeInMilliseconds = std::stoi(word);
			}

			else if (ARG_DISPLACEMENT_X(word.data()))
			{
				word.clear();

				for (++i; i < _args.size() && _args[i] != ' '; ++i)
				{
					word += _args[i];
				}

				argDisplacement.x = std::stoi(word);
			}

			else if (ARG_DISPLACEMENT_Y(word.data()))
			{
				word.clear();

				for (++i; i < _args.size() && _args[i] != ' '; ++i)
				{
					word += _args[i];
				}

				argDisplacement.y = std::stoi(word);
			}

			else if (ARG_SHOW(word.data()))
			{
				argHideWindow = false;
			}

			else if (ARG_FPS(word.data()))
			{
				word.clear();

				for (++i; i < _args.size() && _args[i] != ' '; ++i)
				{
					word += _args[i];
				}

				argFPS = std::stoi(word);
			}

			word.clear();
		}
		else
		{
			word += _args[i];
		}
	}
}
