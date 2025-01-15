#pragma once

#include "Application.h"

extern Dark::Application* Dark::CreateApplication();

int main()
{
	auto app = Dark::CreateApplication();
	app->Run();
	delete app;

	return 0;
}