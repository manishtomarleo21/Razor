#include "rzpch.h"
#include "OrthographicCameraController.h"

#include "Razor/Core/Input.h"
#include "Razor/Core/KeyCodes.h"

namespace Razor
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Bounds({ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel }), m_Camera(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top), m_Rotation(rotation)
		//: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}
	void OrthographicCameraController::OnUpdate(Timestep ts)
		
	{
		if (Input::IsKeyPressed(RZ_KEY_A)) {
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(RZ_KEY_D)) {
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(RZ_KEY_W)) {
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(RZ_KEY_S)) {
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		}

		if (m_Rotation) {

			if (Input::IsKeyPressed(RZ_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(RZ_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			
			m_Camera.SetRotation(m_CameraRotation);
		}
		
		m_Camera.SetPosition(m_CameraPosition);

	}
	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch< MouseScrolledEvent>(RZ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch< WindowResizeEvent>(RZ_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}
	void OrthographicCameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

	}
	void OrthographicCameraController::CalculateView()
	{
		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
		//m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
	}
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		CalculateView();
		return false;
	}
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		//m_AspectRatio = (float)e.GetWidth()/ (float)e.GetHeight();
		OnResize((float)e.GetWidth(),  (float)e.GetHeight());
		CalculateView();
		return false;
	}
}