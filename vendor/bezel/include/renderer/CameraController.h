#pragma once

#include "bezel/include/renderer/OrthographicCamera.h"
#include "bezel/include/Timestep.h"

#include "bezel/include/events/AppEvent.h"
#include "bezel/include/events/MouseEvent.h"

// Not too sure if I want to separate the camera controller into 2 files for ortho and perspective yet

namespace Bezel {

	class OrthographicCameraController {
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;	// In degrees
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;

		bool onMouseScrolled(MouseScrolledEvent& e);
		bool onWindowResized(WindowResizeEvent& e);
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void onUpdate(Timestep ts);
		void onEvent(Event& e);

		OrthographicCamera& getCamera() { return m_Camera; }
		const OrthographicCamera& getCamera() const { return m_Camera; } // Incase a const camera obj is needed
	
		float getZoomLevel() const { return m_ZoomLevel; }
		void setZoomLevel(float level) { m_ZoomLevel = level; }
	};

}