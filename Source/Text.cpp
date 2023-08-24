#include "Text.h"

#include "Common.h"

#include <Windows.h>

std::string Text::sAuxString;

Text::Text()
{
	LoadDefaultFont();

	mText.setFont(mFont);
}

Text::Text(const char* text) : Text()
{
	Set(text);
}

void Text::Render()
{
	gWindow->draw(mText);
}

sf::Vector2f Text::GetBoundingBox()
{
	return mText.getGlobalBounds().getSize();
}

void Text::SetFont()
{
	LoadDefaultFont();

	mText.setFont(mFont);
}

void Text::SetFont(const std::string& font)
{
	// Try direct load
	if (!mFont.loadFromFile(font))
	{
		sAuxString = WINDOWS_FONTS_FOLDER;
		sAuxString += font;

		// Try load from windows fonts folder
		if (!mFont.loadFromFile(sAuxString))
		{
			// If all fails load default font
			LoadDefaultFont();
		}
	}

	mText.setFont(mFont);
}

void Text::SetSize(unsigned int sizeInPixels)
{
	mText.setCharacterSize(sizeInPixels);
}

void Text::SetColor(sf::Color color)
{
	mText.setFillColor(color);
}

void Text::SetPosition(sf::Vector2f position)
{
	mText.setPosition(position);
}

void Text::SetPosition(unsigned int x, unsigned int y)
{
	mText.setPosition(x, y);
}

void Text::LoadDefaultFont()
{
	sAuxString = WINDOWS_FONTS_FOLDER;
	sAuxString += DEFAULT_FONT;

	if (!mFont.loadFromFile(sAuxString))
	{
		swprintf_s(gErrorMessage, ERROR_MESSAGE_SIZE, L"Fatal error. Could not find default font (%S)", sAuxString.data());
		FatalAppExit(0, gErrorMessage);
	}
}
