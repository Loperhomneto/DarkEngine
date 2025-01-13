#pragma once
#include "Core.h"
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

	virtual void OnUpdate() override;
	virtual void OnEvent(Event& e) override;
	//void EventWindowResize(WindowResizeEvent& e);

	//game logic
private:
	Quad floor;
	Quad up1;
	Quad up2;
	Quad any1;
	Quad any2;
	Quad idle1;
	Quad idle2;
};