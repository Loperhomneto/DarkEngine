#pragma once
#include "Dark/Components.h"
#include "Dark/Scene.h"
#include "Dark/Entity.h"
#include "imgui.h"

using namespace Dark;

class ScenePanel
{
public:
	ScenePanel(std::shared_ptr<Scene> scene);

	void setContext(std::shared_ptr<Scene> scene);

	void OnImGuiRender();
private:
	void TreeNode(Entity entity);
private:
	std::shared_ptr<Scene> m_context;
};