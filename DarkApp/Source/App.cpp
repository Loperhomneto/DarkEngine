#include "App.h"
#include <cstdlib>
using namespace Dark;

App::App()
{
	s_Layer layer = std::make_shared<FooLayer>();
	pushLayer(layer);
}


FooLayer::FooLayer() : npc(glm::vec2(0))
{
	// Make it such that the draw quad function is overloaded with the drawtexturedquad function.
	// also maybe make it so that you draw a backdrop, and you wont have to keep updating that rect in the
	// onupdate function in foolayer. Make it so that you only have to set a background through a function or in 
	// the constructer of the foolayer.
	// ability to make ur own texture. e.g. rotate a texture to make a new one or create a one by one white pixel
	// VertexAttrib should be not always have to be created, sometimes it should be replaced with a simple
	// glm::vec2 for the position of the rectangle
	// add profiling, not sure if something is taking a really long time to render
	// BATCH RENDERING!!!!
	// text rendering
	// how to make a smokey or glowey texture / watch made game in hazel in an hour to see what else to add
	// spritesheets/how to render them


	//init
	SoundEngine::AddSound("assets/sounds/explosion.wav", "explosion");

	Renderer::AddTexture("assets/textures/container.jpg", false, "container");
	Renderer::AddTexture("assets/textures/awesomeface.png", true, "papiface");
	Renderer::AddTexture("assets/textures/flooring.jpg", false, "flooring");
	Renderer::AddTexture("assets/textures/floor.png", true, "floor");
	Renderer::AddTexture("assets/textures/up1.png", true, "up1");
	Renderer::AddTexture("assets/textures/up2.png", true, "up2");
	Renderer::AddTexture("assets/textures/any1.png", true, "any1");
	Renderer::AddTexture("assets/textures/any2.png", true, "any2");
	Renderer::AddTexture("assets/textures/idle1.png", true, "idle1");
	Renderer::AddTexture("assets/textures/idle2.png", true, "idle2");
	Renderer::AddTexture("assets/textures/table.png", true, "table");
}

void FooLayer::OnUpdate()
{
	//Backdrop	
	float width = Input::GetWindowWidth();
	float height = Input::GetWindowHeight();
	//float s = width / 8;
	//for (float x = 0; x < width; x += width / 8) {
	//	for (float y = 0; y < height; y += height / 8) {
	//		VertexAttrib vert(glm::vec2(x, y));
	//		glm::vec2 size(s);
	//		Renderer::DrawTexturedQuad(vert, size, "floor");
	//	}
	//}
	VertexAttrib vert1(glm::vec2(0, 0));
	Renderer::DrawTexturedQuad(vert1, glm::vec2(width, height), "floor");

	//Tables
	float s = width / 8;
	for (float x = 0; x < width /*- (width / 4)*/; x += width / 4) {
		for (float y = 0; y < height ; y += height / 4) {
			VertexAttrib vert(glm::vec2(x + width / 8 - s / 2, y + height / 8 - s / 2));
			glm::vec2 size = glm::vec2(s);
			Renderer::DrawTexturedQuad(vert, size, "table");
		}
	}

	//NPCS
	//s = width / 10;
	//for (float x = width*3/4; x < width; x += width / 8) {
	//	for (float y = 0; y < height; y += height / 4) {
	//		VertexAttrib vert(glm::vec2(x + width/16 - s/2, y + height / 8 - s / 2));
	//		glm::vec2 size = glm::vec2(s);
	//		Renderer::DrawTexturedQuad(vert, size, "idle1");
	//	}
	//}

	npc.onUpdate();

}

void FooLayer::OnEvent(Event& e)
{
	//Event::CheckEventFunc<WindowResizeEvent>(e, BIND_FN(&FooLayer::EventWindowResize));

	if (Event::CheckEvent(EventTypes::MouseOnClick, e))
	{
		SoundEngine::PlaySound("explosion", 0.1);
		npc.walk(glm::vec2(200, 200));
	}

}

//void FooLayer::EventWindowResize(WindowResizeEvent& e)
//{
//	std::cout << "Height: " << e.height << " Width: " << e.width;
//}

Dark::Application* Dark::CreateApplication()
{
	return new App();
}

NPC::NPC(glm::vec2 POS)
{
	pos = POS;
	currentDes = pos;
}

void NPC::walk(glm::vec2 des)
{
	currentDes = des;
}

void NPC::onUpdate()
{
	// set animation stages
	double curTime = Input::getTime();

	if (curTime - lastAnimation >= timestep)
	{
		if (animationStage == maxAnimationStages)
		{
			animationStage = 1;
		}
		else
		{
			animationStage++;
		}

		lastAnimation = curTime;
	}

	glm::vec2 size(100);
	if (animationStage == 1)
	{
		Renderer::DrawTexturedQuad(pos, size, "idle1");
	}
	else if (animationStage == 2)
	{
		Renderer::DrawTexturedQuad(pos, size, "idle2");
	}

	//walk toward current set destination
	if (currentDes != pos)
	{
		glm::vec2 sub = abs(pos - currentDes);

		pos.x += sub.x * curTime * speed;
		pos.y += sub.y * curTime * speed;
		std::cout << "Pos.x: " << pos.x << " Pos.y:" << pos.y << std::endl;
	}
}
