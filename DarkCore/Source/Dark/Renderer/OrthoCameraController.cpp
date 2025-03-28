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
		m_OrthographicSize = 3.0f;
		
		CalculateViewProj();
	}

	void OrthoCameraController::OnUpdate(TimeStep ts)
	{
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
			m_CameraRotation -= ts.getDeltatime() * m_CameraRotationSpeed;
		}
		else if (Input::isKeyPressed(DARK_KEY_E))
		{
			m_CameraRotation += ts.getDeltatime() * m_CameraRotationSpeed;
		}

	}

	glm::mat4 OrthoCameraController::getViewProjectionMatrix()
	{
		CalculateViewProj();
		return m_viewProjectionMatrix;
	}

	void OrthoCameraController::setWindowSize(glm::vec2 size)
	{
		m_AspectRatio = size.x / size.y;
	}

	void OrthoCameraController::OnEvent(Event& e)
	{
		Event::CheckEventFunc<MouseScrollEvent>(e, DARK_BIND_FN(OnMouseScroll));
	}

	//void OrthoCameraController::OnWindowResize(WindowResizeEvent& e)	
	//{
	//	m_AspectRatio = (float)Input::GetWindowWidth() / (float)Input::GetWindowHeight();
	//	//Logger::info("window resized", Input::GetWindowWidth(), Input::GetWindowHeight());
	//}

	void OrthoCameraController::OnMouseScroll(MouseScrollEvent& e)
	{
		m_ZoomLevel -= e.scrolly * m_ZoomSpeed;
		if (m_ZoomLevel < 0.25f)
		{
			m_ZoomLevel = 0.25f;
		}
	}

	void OrthoCameraController::CalculateViewProj()
	{
		m_viewMatrix = glm::translate(glm::mat4(1.0f), m_CameraPosition) * glm::rotate(glm::mat4(1.0f), glm::radians(m_CameraRotation), glm::vec3(0.0f, 0.0f, 1.0f));
		m_projectionMatrix = glm::ortho(-m_OrthographicSize * m_AspectRatio * m_ZoomLevel, m_OrthographicSize * m_AspectRatio * m_ZoomLevel,
			-m_OrthographicSize * m_ZoomLevel, m_OrthographicSize * m_ZoomLevel, 1.0f, -1.0f);

		m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	}

}