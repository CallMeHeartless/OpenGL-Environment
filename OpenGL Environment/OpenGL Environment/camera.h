/***********************
 * File:		Camera.h
 * Description: Header file for the Camera class
 * Author:		Kerry Pellett
 * Contact:		kerry.pellet@gmail.com
********************/

#ifndef __CAMERA_H__
#define __CAMERA_H__

// Local includes
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

class Camera {
	private:
		glm::vec3 m_vfCameraPos = glm::vec3(0.0f, 0.0f, 20.0f); // default
		glm::vec3 m_vfCameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_vfCameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 m_vfCameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 m_vfOffset = glm::vec3(0, 0, 0);
		glm::mat4 m_mfProjection;
		float m_fFOV = 0.0f;


	public:
		Camera();
		Camera(float _fWidth, float _fHeight);
		Camera(float _fFOV, float _ratio, float _fNear, float _fFar);
		~Camera();

		glm::mat4 GetView()const;
		glm::mat4 GetProjection() const;

		glm::vec3 GetRight()const;
		glm::vec3 GetUp()const;

		void SetPosition(glm::vec3 _vfPosition);
		void UpdatePosition(float _fX, float _fY, float _fZ);
		glm::vec3 GetPosition()const;
		void SetOffset(glm::vec3 _vfOffset);
		glm::vec3 GetOffset()const;

		void PointAt(glm::vec3 _vfPoint);

};
#endif // !__CAMERA_H__
