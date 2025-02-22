#pragma once
#include "Dark/Core.h"
#include "Application.h"

namespace Dark {

	class Input
	{
	public:
		static bool isKeyPressed(int keycode);
		static bool isMousePressed(int button);
		static std::pair<int, int> GetMousePosition();
		static int GetXPos();
		static int GetYPos();

		static double getProgramTime();

		static int GetWindowWidth();
		static int GetWindowHeight();

		static void BlockInput(bool block) { m_blockInputs = block; }
	private:
		static bool m_blockInputs;
	};

}