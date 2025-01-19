#pragma once
#include "Dark.h"
#include <iostream>
using namespace Dark;

class App : public Application
{
public:
	App();
};

class FooLayer : public Layer
{
public:
	FooLayer();

	virtual void OnUpdate(TimeStep ts) override;
	virtual void OnEvent(Event& e) override;
	//void EventWindowResize(WindowResizeEvent& e);

	//game logic
};