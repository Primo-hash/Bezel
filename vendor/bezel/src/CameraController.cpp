#include "bezel/Precompiled.h"
#include "bezel/include/renderer/CameraController.h"

#include "bezel/include/Input.h"
#include "bezel/include/InputCodes.h"

namespace Bezel {

	/*
		On construction camera is set to fit the aspect ratio value provided by the application.
	*/
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) :
		m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation) {

	}

	/*
		Camera movement controlled by key input events.
	*/
	void OrthographicCameraController::onUpdate(Timestep ts) {
		// Translation
		if (Bezel::Input::isKeyPressed(BZ_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		else if (Bezel::Input::isKeyPressed(BZ_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;

		if (Bezel::Input::isKeyPressed(BZ_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		else if (Bezel::Input::isKeyPressed(BZ_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

		// Rotation if set
		if (m_Rotation) {
			if (Bezel::Input::isKeyPressed(BZ_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Bezel::Input::isKeyPressed(BZ_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;
		}

		m_Camera.setPosition(m_CameraPosition);
		// This line basically sets movement speed for the camera to be slow
		// when camera is zoomed in and faster when zoomed out.
		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	/*
		When referenced starts an event dispatcher to bind input events to the current object.
	*/
	void OrthographicCameraController::onEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(BZ_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BZ_BIND_EVENT_FN(OrthographicCameraController::onWindowResized));
	}

	/* 
		Camera zoom controlled by mouse scroll event if this function is referenced.
		A reference to a mouse scroll event object needs to be provided.
	*/
	bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e) {
		m_ZoomLevel -= e.getYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);	// Sets a minimum zoom level
		// Projection updated to fit aspect ratio after zoom level adjustment
		m_Camera.setProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	/*
		Handles updating the projection on window resize events when referenced.
	*/
	bool OrthographicCameraController::onWindowResized(WindowResizeEvent& e) {
		m_AspectRatio = (float)e.getWidth() / (float)e.getHeight();
		m_Camera.setProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}
