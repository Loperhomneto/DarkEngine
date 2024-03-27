#pragma once

#include "Application.h"

extern Dark::Application* Dark::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Dark::CreateApplication();
	app->Run();
	delete app;

	return 0;
}