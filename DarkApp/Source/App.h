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
	void OnAttach() override;
	void OnUpdate(TimeStep ts) override;
	void OnEvent(Event& e) override;

private:
	glm::vec3 m_Color = glm::vec3(1.0f);
	int add = -1;
	float m_Rotation = 0.0f;
	//void EventWindowResize(WindowResizeEvent& e);

	//game logic
};