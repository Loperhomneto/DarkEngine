#pragma once
#include <utility>

class Input
{
public:
	static bool isKeyPressed(int keycode);
	static bool isMousePressed(int button);
	static std::pair<int, int> GetMousePosition();
	static int GetXPos();
	static int GetYPos();

	static double getTime();

	static int GetWindowWidth();
	static int GetWindowHeight();
};

