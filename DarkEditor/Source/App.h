#pragma once
#include "Dark.h"
#include "ScenePanel.h"
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

	void ImGuiRender(unsigned int colorAttachmnetRendererID) override;
private:
	//glm::vec3 m_Color = glm::vec3(1.0f);
	//int add = -1;
	float m_Rotation = 0.0f;
	bool m_blockEvents = false;

	glm::vec2 m_framebufferSize = glm::vec2(1280.0f, 720.0f);

	std::shared_ptr<Scene> m_Scene;
	std::shared_ptr<ScenePanel> m_ScenePanel;
};