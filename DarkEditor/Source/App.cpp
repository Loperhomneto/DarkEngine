#include "App.h"
using namespace Dark;

App::App()
{
	s_Layer layer = std::make_shared<FooLayer>();
	pushLayer(layer);
}

void FooLayer::OnAttach()
{
	// make logger work without separating lines
	// enables asserts and fail safes things that might not work
	// maintenance to make this robust
	// background
	// add rotation to sprites
	// add profiling, not sure if something is taking a really long time to render

	//init
	Logger::info("onAttach app");

	Renderer2D::AddTexture("assets/textures/container.jpg", false, "container");
	Renderer2D::AddTexture("assets/textures/awesomeface.png", true, "papiface");
	Renderer2D::AddTexture("assets/textures/check.jpg", false, "checkerboard");
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
	SoundEngine::AddSound("assets/sounds/explosion.wav", "explosion");
	Renderer2D::AddOrthoCameraController();

	//Native Scripts
	class MoveUpScript : public ScriptableEntity
	{
	public:
		void OnAttach() override { Logger::info("MoveUpScript attached!"); }
		void OnDetach() override { Logger::info("MoveUpScript detached!"); }

		void OnUpdate(TimeStep ts) override
		{
			glm::vec2& pos = GetComponent<TransformComponent>().Pos;
			pos.y += ts.getDeltatime() / 2.0f;
		}
	};

	class ChangingColorScript : public ScriptableEntity
	{
	public:
		void OnUpdate(TimeStep ts) override
		{
			glm::vec4& color = GetComponent<RendererComponent>().Color;
			float colorZ = color.z + (ts.getDeltatime() * add * 5.0f);
			if (colorZ < 0.0f)
			{
				add = 1.0f;
			}
			else if (colorZ > 1.0f)
			{
				add = -1.0f;
			}

			color = glm::vec4(1.0f, 1.0f, colorZ, 1.0f);
		}
	private:
		int add = -1;
	};

	class RotationScript : public ScriptableEntity
	{
	public:
		void OnUpdate(TimeStep ts) override
		{
			float& rotation = GetComponent<TransformComponent>().Rotation;
			rotation += ts.getDeltatime() * 50;
		}
	};

	class ReverseRotationScript : public ScriptableEntity
	{
	public:
		void OnUpdate(TimeStep ts) override
		{
			float& rotation = GetComponent<TransformComponent>().Rotation;
			rotation -= ts.getDeltatime() * 50;
		}
	};

	//ECS entt
	m_Scene = std::make_shared<Scene>();
	std::shared_ptr<Entity> ent = m_Scene->CreateEntity("Very Named Entity");

	ent->AddComponent<TransformComponent>(glm::vec2(-1.0f, 1.0f), glm::vec2(1.5f, 1.5f));
	ent->AddComponent<RendererComponent>(glm::vec4(1.0f, 0.8f, 0.6f, 1.0f));

	ent->AddComponent<NativeScriptComponent>(new MoveUpScript());

	std::shared_ptr<Entity> ent2 = m_Scene->CreateEntity("Changing Color Square", glm::vec2(0.5f, 0.5f), glm::vec2(1.0f, 1.0f));
	ent2->AddComponent<RendererComponent>(glm::vec4(1.0f, 0.8f, 0.6f, 1.0f));
	ent2->AddComponent<NativeScriptComponent>(new ChangingColorScript());

	std::shared_ptr<Entity> ent3 = m_Scene->CreateEntity("Colored Entity", glm::vec2(1.0f, -2.0f), glm::vec2(2.0f, 2.0f));
	ent3->AddComponent<RendererComponent>(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));

	std::shared_ptr<Entity> ent4 = m_Scene->CreateEntity("Container Entity", glm::vec2(-3.0f, -2.0f), glm::vec2(1.0f, 1.0f));
	ent4->AddComponent<RendererComponent>("container");

	std::shared_ptr<Entity> ent5 = m_Scene->CreateEntity("Papiface Entity 1", glm::vec2(-2.0f, -2.0f), glm::vec2(0.5f, 0.5f));
	ent5->AddComponent<RendererComponent>("papiface");

	std::shared_ptr<Entity> ent6 = m_Scene->CreateEntity("Papiface Entity 2", glm::vec2(-1.5f, -1.5f), glm::vec2(3.0f, 3.0f));
	ent6->AddComponent<RendererComponent>("papiface");

	std::shared_ptr<Entity> ent7 = m_Scene->CreateEntity("Tree Sprite", glm::vec2(-3.0f, -0.5f), glm::vec2(1.0f, 2.0f));
	ent7->AddComponent<Sprite>("testSpritesheet", glm::vec2(0, 1), glm::vec2(1, 2));

	std::shared_ptr<Entity> ent8 = m_Scene->CreateEntity("Colored Sprite", glm::vec2(2.0f, 0.5f), glm::vec2(2.5f, 2.5f));
	ent8->AddComponent<Sprite>("testSpritesheet", glm::vec2(0, 3));
	ent8->AddComponent<RendererComponent>(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));

	std::shared_ptr<Entity> ent9 = m_Scene->CreateEntity("Rotating Colored Square", glm::vec2(-1.0f, -1.0f), glm::vec2(2.0f, 2.0f));
	ent9->AddComponent<RendererComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	ent9->AddComponent<NativeScriptComponent>(new RotationScript());

	std::shared_ptr<Entity> ent10 = m_Scene->CreateEntity("Reverse Rotating Square", glm::vec2(-1.0f, -1.0f), glm::vec2(2.5f, 2.5f));
	ent10->AddComponent<RendererComponent>("container", glm::vec4(1.0f, 1.0f, 0.8f, 1.0f));
	ent10->AddComponent<NativeScriptComponent>(new ReverseRotationScript());
}

void FooLayer::OnUpdate(TimeStep ts)
{
	Renderer2D::DrawBackDrop("floor");

	//m_Rotation += ts.getDeltatime() * 50;
	// 
	//Renderer2D::DrawBackDrop(glm::vec3(0.1f, 0.2f, 0.3f));
	//float colorZ = m_Color.z + (ts.getDeltatime() * add * 5.0f);
	//if (colorZ < 0.0f)
	//{
	//	add = 1.0f;
	//}
	//else if (colorZ > 1.0f)
	//{
	//	add = -1.0f;
	//}
	//m_Color = glm::vec3(1.0f, 1.0f, colorZ);
	//Renderer2D::Draw2DQuad(glm::vec2(0.5f, 0.5f), glm::vec2(1.0f, 1.0f), m_Color);
	//Renderer2D::Draw2DQuad(glm::vec2(1.0f, -2.0f), glm::vec2(2.0f, 2.0f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
	//
	//Renderer2D::Draw2DQuad(glm::vec2(-3.0f, -2.0f), glm::vec2(1.0f, 1.0f), "container");
	//Renderer2D::Draw2DQuad(glm::vec2(-2.0f, -2.0f), glm::vec2(0.5f, 0.5f), "papiface");
	//Renderer2D::Draw2DQuad(glm::vec2(-1.5f, -1.5f), glm::vec2(3.0f, 3.0f), "papiface");
	//
	//Renderer2D::DrawSprite(glm::vec2(-3.0f, -0.5f), glm::vec2(1.0f, 2.0f), "testSpritesheet", glm::vec2(0, 1), glm::vec2(1, 2));
	//Renderer2D::Draw2DRotatedQuad(glm::vec2(-1.0f, -1.0f), glm::vec2(2.0f, 2.0f), m_Rotation, glm::vec3(1.0f, 1.0f, 1.0f));
	//Renderer2D::Draw2DRotatedQuad(glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 1.0f), -m_Rotation, "container", glm::vec3(1.0f, 1.0f, 0.8f));
	//
	//Renderer2D::Draw2DQuad(glm::vec2(-5.0f, -5.0f), glm::vec2(10.0f, 10.0f), "checkerboard");

	m_Scene->OnUpdate(ts);
}

void FooLayer::OnEvent(Event& e)
{

}

void FooLayer::ImGuiRender(unsigned int colorAttachmnetRendererID)
{
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	bool dockspaceOpen = true;
	ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);
	ImGui::PopStyleVar(3);

	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Tools"))
		{
			if (ImGui::MenuItem("Open Viewport")) {   }
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	bool another_window = true;
	bool open_viewport = true;
	ImGui::Begin("Scene Panel", &another_window);
	ImGui::End();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("Viewport", &open_viewport);
	ImGui::PopStyleVar();
	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	m_framebufferSize = { viewportPanelSize.x, viewportPanelSize.y };
	ImGui::Image(colorAttachmnetRendererID, viewportPanelSize, ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
	ImGui::End();

	bool show_demo_window;
	ImGui::ShowDemoWindow(&show_demo_window);

	ImGui::End();

	Renderer2D::updateFramebuffer(m_framebufferSize);
}

Dark::Application* Dark::CreateApplication()
{
	return new App();
}
