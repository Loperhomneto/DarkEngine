#include "App.h"
using namespace Dark;

App::App()
{
	s_Layer layer = std::make_shared<FooLayer>();
	pushLayer(layer);
}

void FooLayer::OnAttach()
{
	Logger::info("onattach app");

	//TODO: refs, camera, imgui, framebuffers, unity like editor, overlay with layers, precompiled headers
	// add rotated quads
// how to make a smokey or glowey texture / watch made game in hazel in an hour to see what else to add
// spritesheets/how to render them
// add profiling, not sure if something is taking a really long time to render
// BATCH RENDERING!!!!
// text rendering
// ability to make ur own texture. e.g. rotate a texture to make a new one or create a one by one white pixel


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

void FooLayer::OnUpdate(TimeStep ts)
{
	//Backdrop	
	float width = Input::GetWindowWidth();
	float height = Input::GetWindowHeight();

	Renderer::Draw2DQuad(glm::vec2(200, 200), glm::vec2(100, 100), "container");
	Renderer::Draw2DQuad(glm::vec2(0, 0), glm::vec2(200, 200), "papiface");
	Renderer::Draw2DQuad(glm::vec2(300, 300), glm::vec2(300, 300), "papiface");


	//Renderer::Draw2DQuad(glm::vec2(0, 0), glm::vec2(100, 100), glm::vec3(1.0f));

	//Renderer::Draw2DQuad(glm::vec2(100, 100), glm::vec2(100, 100), glm::vec3(1.0f));

	//Renderer::DrawBackDrop("floor");

	////Tables
	//float s = width / 8;
	//for (float x = 0; x < width /*- (width / 4)*/; x += width / 4) {
	//	for (float y = 0; y < height ; y += height / 4) {
	//		glm::vec2 vert = glm::vec2(x + width / 8 - s / 2, y + height / 8 - s / 2);
	//		glm::vec2 size = glm::vec2(s);
	//		Renderer::Draw2DQuad(vert, size, "table");
	//	}
	//}
}

void FooLayer::OnEvent(Event& e)
{
	//Event::CheckEventFunc<WindowResizeEvent>(e, BIND_FN(&FooLayer::EventWindowResize));

	if (Event::CheckEvent(EventTypes::MouseOnClick, e))
	{
		SoundEngine::PlaySound("explosion", 0.1);
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

