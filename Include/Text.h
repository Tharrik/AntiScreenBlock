#pragma once

#include "SFML/Graphics.hpp"

#define WINDOWS_FONTS_FOLDER R"(C:\Windows\Fonts\)"
#define DEFAULT_FONT "arial.ttf"

class Text {

private:
	static std::string sAuxString;

private:
	sf::Font mFont;
	sf::Text mText;

public:
	Text();
	Text(const char* text);
	~Text() = default;

public:
	void Update();
	void Render();

public:
	inline void Set(const std::string& text) { mText.setString(text); }

	sf::Vector2f GetBoundingBox();

	void SetFont();
	void SetFont(const std::string& font);

	void SetSize(unsigned int sizeInPixels);
	void SetColor(sf::Color color);

	void SetPosition(sf::Vector2f position);
	void SetPosition(unsigned int x, unsigned int y);

private:
	void LoadDefaultFont();

};
