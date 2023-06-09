#pragma once

#include "Camera.h"

#include "glm/glm.hpp"

namespace CitrusEngine {
	//Implement a perspective camera (method explanations found in Camera.h)
	class PerspectiveCamera : public Camera {
	public:
		PerspectiveCamera(float fov, float aspectRatio);

		glm::vec3 GetPosition() override { return position; }
		void SetPosition(glm::vec3 pos) override { position = pos; RecalculateViewMatrix(); }
		glm::vec3 GetRotation() override { return rotation; }
		void SetRotation(glm::vec3 rot) override { rotation = rot; RecalculateViewMatrix(); }

		glm::mat4 GetProjectionMatrix() override { return projectionMatrix; }
		glm::mat4 GetViewMatrix() override { return viewMatrix; }
		glm::mat4 GetViewProjectionMatrix() override { return viewProjectionMatrix; }

		//Get where the camera is looking
		const glm::vec3& GetLookTarget() const { return lookTarget; }
	private:
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 viewProjectionMatrix;

		glm::vec3 position;
		glm::vec3 rotation;

		glm::vec3 lookTarget;

		//Recalculate the view matrix based on a new position and rotation
		void RecalculateViewMatrix();
		//Recalculate where the camera is looking
		void RecalculateLookTarget();
	};
}