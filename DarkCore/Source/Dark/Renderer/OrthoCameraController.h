#pragma once
#include "Dark/Event.h"
#include "Dark/TimeStep.h"
#include "glm.hpp"

namespace Dark
{

	class OrthoCameraController
	{
	public:
		OrthoCameraController();

		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);

		glm::mat4 getViewProjectionMatrix();
	private:
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_viewProjectionMatrix;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	private:
		void OnWindowResize(WindowResizeEvent& e);
		void OnMouseScroll(MouseScrollEvent& e);
	};

}