#include "dkpch.h"
#include "OrthoCameraController.h"
#include "Dark/KeyCodes.h"
#include "Dark/Input.h"
#include "gtc/matrix_transform.hpp"

namespace Dark
{

#define DARK_BIND_FN(x) std::bind(&OrthoCameraController::x, this, std::placeholders::_1)

	OrthoCameraController::OrthoCameraController()
	{
		m_AspectRatio = (float)Input::GetWindowWidth() / (float)Input::GetWindowHeight();
		m_viewMatrix = glm::translate(glm::mat4(1.0f), m_CameraPosition);
		m_projectionMatrix = glm::ortho(-1.0f * m_ZoomLevel, 1.0f * m_ZoomLevel, -1.0f * m_ZoomLevel, 1.0f * m_ZoomLevel);
		m_viewProjectionMatrix = m_viewMatrix * m_projectionMatrix;
	}

	void OrthoCameraController::OnUpdate(TimeStep ts)
	{
		// TODO: add camera rotation
		if (Input::isKeyPressed(DARK_KEY_W))
		{
			m_CameraPosition.y -= ts.getDeltatime() * m_CameraTranslationSpeed;
		}
		else if (Input::isKeyPressed(DARK_KEY_S))
		{
			m_CameraPosition.y += ts.getDeltatime() * m_CameraTranslationSpeed;
		}

		if (Input::isKeyPressed(DARK_KEY_A))
		{
			m_CameraPosition.x += ts.getDeltatime() * m_CameraTranslationSpeed;
		}
		else if (Input::isKeyPressed(DARK_KEY_D))
		{
			m_CameraPosition.x -= ts.getDeltatime() * m_CameraTranslationSpeed;
		}

		if (Input::isKeyPressed(DARK_KEY_Q))
		{
			m_CameraRotation += ts.getDeltatime() * m_CameraRotationSpeed;
		}
		else if (Input::isKeyPressed(DARK_KEY_E))
		{
			m_CameraRotation -= ts.getDeltatime() * m_CameraRotationSpeed;
		}

	}

	glm::mat4 OrthoCameraController::getViewProjectionMatrix()
	{
		m_viewMatrix = glm::translate(glm::mat4(1.0f), m_CameraPosition) * glm::rotate(glm::mat4(1.0f), glm::radians(m_CameraRotation), glm::vec3(0.0f, 0.0f, 1.0f));
		m_projectionMatrix = glm::ortho(-1.0f * m_ZoomLevel, 1.0f * m_ZoomLevel, -1.0f * m_ZoomLevel, 1.0f * m_ZoomLevel);
		m_viewProjectionMatrix = m_viewMatrix * m_projectionMatrix;
		return m_viewProjectionMatrix;
	}

	void OrthoCameraController::OnEvent(Event& e)
	{
		Event::CheckEventFunc<WindowResizeEvent>(e, DARK_BIND_FN(OnWindowResize));
		Event::CheckEventFunc<MouseScrollEvent>(e, DARK_BIND_FN(OnMouseScroll));
	}

	void OrthoCameraController::OnWindowResize(WindowResizeEvent& e)	
	{
		m_AspectRatio = (float)Input::GetWindowWidth() / (float)Input::GetWindowHeight();
	}

	void OrthoCameraController::OnMouseScroll(MouseScrollEvent& e)
	{
		m_ZoomLevel += e.scrolly * m_ZoomSpeed;
		if (m_ZoomLevel < 0.25f)
		{
			m_ZoomLevel = 0.25f;
		}
	}

}