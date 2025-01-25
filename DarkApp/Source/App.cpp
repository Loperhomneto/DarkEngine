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

//TODO: camera, imgui, framebuffers, unity like editor, fix background
// add rotated quads
// how to make a smokey or glowey texture / watch made game in hazel in an hour to see what else to add
// spritesheets/how to render them
// add profiling, not sure if something is taking a really long time to render


//init
	SoundEngine::AddSound("assets/sounds/explosion.wav", "explosion");

	Renderer2D::AddTexture("assets/textures/container.jpg", false, "container");
	Renderer2D::AddTexture("assets/textures/awesomeface.png", true, "papiface");
	Renderer2D::AddTexture("assets/textures/flooring.jpg", false, "flooring");
	Renderer2D::AddTexture("assets/textures/floor.png", true, "floor");
	Renderer2D::AddTexture("assets/textures/up1.png", true, "up1");
	Renderer2D::AddTexture("assets/textures/up2.png", true, "up2");
	Renderer2D::AddTexture("assets/textures/any1.png", true, "any1");
	Renderer2D::AddTexture("assets/textures/any2.png", true, "any2");
	Renderer2D::AddTexture("assets/textures/idle1.png", true, "idle1");
	Renderer2D::AddTexture("assets/textures/idle2.png", true, "idle2");
	Renderer2D::AddTexture("assets/textures/table.png", true, "table");

	//Renderer2D::AddOrthoCameraController();
}

void FooLayer::OnUpdate(TimeStep ts)
{
	//Backdrop	
	//float width = Input::GetWindowWidth();
	//float height = Input::GetWindowHeight();
	Renderer2D::DrawBackDrop(glm::vec3(0.1f, 0.2f, 0.3f));

	Renderer2D::Draw2DQuad(glm::vec2(400, 200), glm::vec2(200, 200), glm::vec4(0.8f, 0.8f, 0.8f, 0.5f));
	Renderer2D::Draw2DQuad(glm::vec2(100, 100), glm::vec2(100, 100), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));

	Renderer2D::Draw2DQuad(glm::vec2(200, 200), glm::vec2(100, 100), "container");
	Renderer2D::Draw2DQuad(glm::vec2(0, 0), glm::vec2(200, 200), "papiface");
	Renderer2D::Draw2DQuad(glm::vec2(300, 300), glm::vec2(300, 300), "papiface");

	//Renderer2D::DrawBackDrop("floor");

	////Tables
	//float s = width / 8;
	//for (float x = 0; x < width /*- (width / 4)*/; x += width / 4) {
	//	for (float y = 0; y < height ; y += height / 4) {
	//		glm::vec2 vert = glm::vec2(x + width / 8 - s / 2, y + height / 8 - s / 2);
	//		glm::vec2 size = glm::vec2(s);
	//		Renderer2D::Draw2DQuad(vert, size, "table");
	//	}
	//}
}

void FooLayer::OnEvent(Event& e)
{
	//Event::CheckEventFunc<WindowResizeEvent>(e, BIND_FN(&FooLayer::EventWindowResize));

	if (Event::CheckEvent(EventTypes::KeyInput, e))
	{
		//SoundEngine::PlaySound("explosion", 0.1);
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

