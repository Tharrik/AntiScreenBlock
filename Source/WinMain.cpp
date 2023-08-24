#include <windows.h>

#include "SFML/Graphics.hpp"

#include "Common.h"

#include "Args.h"
#include "Text.h"

extern sf::RenderWindow* gWindow = nullptr;
extern wchar_t* gErrorMessage = new wchar_t[ERROR_MESSAGE_SIZE];

sf::Vector2u WINDOW_SIZE{ 160U, 100U };
NOTIFYICONDATA gIconData;

sf::Clock gUpdateTimer;
float gUpdatePeriod = .0333f;

sf::Clock gMouseTimer;
INPUT gMouseInput;
Text gTimerText;
std::string gTimerString;
sf::RectangleShape gTimerBB;

void Start();
void Update();
void UpdateEvents();
void Render();

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR pCmdLine, _In_ int nCmdShow)
{
	ReadArguments(pCmdLine);

	Start();

	while (gWindow->isOpen())
	{
		if (gUpdateTimer.getElapsedTime().asSeconds() > gUpdatePeriod)
		{
			gUpdateTimer.restart();

			Update();

			Render();
		}
		else
		{
			// Calculate time to next update to put the program to sleep until needed
			// This makes the program stop consuming so much energy. In testing it went
			// from ~25% CPU consumption to 0~0.3%.
			float _timeToNextUpdate = gUpdatePeriod - gUpdateTimer.getElapsedTime().asSeconds();

			Sleep(_timeToNextUpdate * 1000);
		}
	}

	return 0;

}

void CallBackTest()
{
	int a = 3 + 2;
	int b = a;
}

void Start()
{
	// Update the window size values for a hidden window
	if (argHideWindow)
	{
		WINDOW_SIZE.x = 0U;
		WINDOW_SIZE.y = 0U;
	}

	// Create the window
	gWindow = new sf::RenderWindow(
		sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y),
		"RFAntiScreenBlock",
		sf::Style::None);

	gIconData.cbSize = sizeof(NOTIFYICONDATA);
	gIconData.hWnd = gWindow->getSystemHandle();
	gIconData.uFlags = NIF_ICON | NIF_TIP;
	gIconData.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	swprintf_s(gIconData.szTip, 128, L"Anti Screen Block");

	bool success = Shell_NotifyIcon(NIM_ADD, &gIconData);

	// Start the program timer
	gUpdateTimer.restart();
	gUpdatePeriod = 1.f / argFPS;

	// Start the mouse timer
	gMouseTimer.restart();

	// Create mouse input
	ZeroMemory(&gMouseInput, sizeof(INPUT));
	gMouseInput.type = INPUT_MOUSE;
	gMouseInput.mi.dx = argDisplacement.x;
	gMouseInput.mi.dy = argDisplacement.y;
	gMouseInput.mi.dwFlags = MOUSEEVENTF_MOVE;

	gTimerText.Set("Ola ke ase");
	gTimerText.SetSize(30);
	gTimerText.SetColor(sf::Color::White);

	gTimerBB.setSize({ 10,10 });
	gTimerBB.setFillColor(sf::Color::Transparent);
	gTimerBB.setOutlineColor(sf::Color::Red);
	gTimerBB.setOutlineThickness(1);
}

void Update()
{
	// check all the window's events that were triggered since the last iteration of the loop
	UpdateEvents();

	if (!argHideWindow)
	{
		// Update timer
		int _minutes = (argTimeInMilliseconds * 0.001f - gMouseTimer.getElapsedTime().asSeconds()) / 60;
		int _seconds = (int)(argTimeInMilliseconds * 0.001f - gMouseTimer.getElapsedTime().asSeconds()) % 60;

		gTimerString.clear();
		gTimerString.reserve(5);
		if (_minutes >= 10)
		{
			gTimerString += std::to_string(_minutes);
		}
		else
		{
			gTimerString += "0";
			gTimerString += std::to_string(_minutes);
		}

		gTimerString += ":";

		if (_seconds >= 10)
		{
			gTimerString += std::to_string(_seconds);
		}
		else
		{
			gTimerString += "0";
			gTimerString += std::to_string(_seconds);
		}
		gTimerText.Set(gTimerString);

		sf::Vector2f _timerPosition;
		_timerPosition.x = (WINDOW_SIZE.x - gTimerText.GetBoundingBox().x) * 0.5f;
		_timerPosition.y = (WINDOW_SIZE.y - gTimerText.GetBoundingBox().y) * 0.5f;

		gTimerText.SetPosition(_timerPosition);
		gTimerBB.setSize(gTimerText.GetBoundingBox());
		gTimerBB.setPosition(_timerPosition);
	}

	if (gMouseTimer.getElapsedTime().asMilliseconds() >= argTimeInMilliseconds)
	{
		// Restart timer
		gMouseTimer.restart();

		SendInput(1, &gMouseInput, sizeof(INPUT));
	}

}

void UpdateEvents()
{
	sf::Event event;
	bool _exit = false;
	while (gWindow->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			_exit = true;
			break;

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				_exit = true;
				break;
			}
			break;
		}

		if (_exit)
			gWindow->close();
	}
}

void Render()
{
	// If the window is hidden do nothing
	if (argHideWindow)
		return;

	// clear the window with black color
	gWindow->clear(sf::Color::Black);

	gTimerText.Render();

	gWindow->draw(gTimerBB);

	// end the current frame
	gWindow->display();
}
