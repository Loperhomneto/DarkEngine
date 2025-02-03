#include "App.h"
using namespace Dark;

App::App()
{
	s_Layer layer = std::make_shared<FooLayer>();
	pushLayer(layer);
}

void FooLayer::OnAttach()
{
	Logger::info("onAttach app");

// make logger work without separating lines
// add rotated quads
// how to make a smokey or glowey texture / watch made game in hazel in an hour to see what else to add
// add profiling, not sure if something is taking a really long time to render


	//init
	SoundEngine::AddSound("assets/sounds/explosion.wav", "explosion");

	Renderer2D::AddTexture("assets/textures/container.jpg", false, "container");
	Renderer2D::AddTexture("assets/textures/awesomeface.png", true, "papiface");
	//Renderer2D::AddTexture("assets/textures/flooring.jpg", false, "flooring");
	Renderer2D::AddTexture("assets/textures/floor.png", true, "floor");
	//Renderer2D::AddTexture("assets/textures/up1.png", true, "up1");
	//Renderer2D::AddTexture("assets/textures/up2.png", true, "up2");
	//Renderer2D::AddTexture("assets/textures/any1.png", true, "any1");
	//Renderer2D::AddTexture("assets/textures/any2.png", true, "any2");
	//Renderer2D::AddTexture("assets/textures/idle1.png", true, "idle1");
	//Renderer2D::AddTexture("assets/textures/idle2.png", true, "idle2");
	//Renderer2D::AddTexture("assets/textures/table.png", true, "table");
	Renderer2D::AddSpritesheet("assets/textures/RPGpack_sheet_2X.png", true, "testSpritesheet", glm::vec2(128, 128));

	Renderer2D::AddOrthoCameraController();
}

void FooLayer::OnUpdate(TimeStep ts)
{
	m_Rotation += ts.getDeltatime() * 50;

	Renderer2D::DrawBackDrop("floor");
	//Renderer2D::DrawBackDrop(glm::vec3(0.1f, 0.2f, 0.3f));
	float colorZ = m_Color.z + (ts.getDeltatime() * add * 5.0f);
	if (colorZ < 0.0f)
	{
		add = 1.0f;
	}
	else if (colorZ > 1.0f)
	{
		add = -1.0f;
	}
	m_Color = glm::vec3(1.0f, 1.0f, colorZ);
	Renderer2D::Draw2DQuad(glm::vec2(0.5f, 0.5f), glm::vec2(1.0f, 1.0f), m_Color);
	Renderer2D::Draw2DQuad(glm::vec2(1.0f, -2.0f), glm::vec2(2.0f, 2.0f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));

	Renderer2D::Draw2DQuad(glm::vec2(-3.0f, -2.0f), glm::vec2(1.0f, 1.0f), "container");
	Renderer2D::Draw2DQuad(glm::vec2(-2.0f, -2.0f), glm::vec2(0.5f, 0.5f), "papiface");
	Renderer2D::Draw2DQuad(glm::vec2(-1.5f, -1.5f), glm::vec2(3.0f, 3.0f), "papiface");

	Renderer2D::DrawSprite(glm::vec2(-3.0f, -0.5f), glm::vec2(1.0f, 2.0f), "testSpritesheet", glm::vec2(0, 1), glm::vec2(1, 2));
	Renderer2D::Draw2DRotatedQuad(glm::vec2(-1.0f, -1.0f), glm::vec2(2.0f, 2.0f), m_Rotation, glm::vec3(1.0f, 1.0f, 1.0f));
	Renderer2D::Draw2DRotatedQuad(glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 1.0f), -m_Rotation, "container", glm::vec3(1.0f, 1.0f, 0.8f));

	// Imgui DockerSpacer
	bool my_tool_active;
	ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	// Edit a color stored as 4 floats
	float color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	ImGui::ColorEdit4("Color", color);

	// Display contents in a scrolling region
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
	ImGui::BeginChild("Scrolling");
	for (int n = 0; n < 50; n++)
		ImGui::Text("%04d: Some text", n);
	ImGui::EndChild();
	ImGui::End();
}

void FooLayer::OnEvent(Event& e)
{

}

Dark::Application* Dark::CreateApplication()
{
	return new App();
}

