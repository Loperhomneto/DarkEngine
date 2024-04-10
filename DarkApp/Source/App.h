#pragma once
#include "Core.h"
#include <iostream>
using namespace Dark;

class NPC
{
public:
	NPC(glm::vec2 POS);

	void walk(glm::vec2 DES);
	void onUpdate();
private:
	glm::vec2 pos;
	glm::vec2 currentDes;

	const float speed = 0.25;

	const int maxAnimationStages = 2;
	int animationStage = 1;
	double lastAnimation = 0.0;
	const double timestep = 1.0;
};



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
	
	NPC npc;
};