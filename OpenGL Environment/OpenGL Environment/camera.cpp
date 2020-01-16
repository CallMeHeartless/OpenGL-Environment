/***********************

********************/
#include "camera.h"

Camera::Camera(){}

/***********************
* CCamera: Constructor what gives the camera a specified size
* @author: Kerry Pellett (2018)
* @parameter: float _fWidth (camera width) and float _fHeight (camera height)
* @return: CCamera&
********************/
Camera::Camera(float _fWidth, float _fHeight) {
	// Create orthographic camera
	m_mfProjection = glm::ortho(0.0f, _fWidth, 0.0f, _fHeight, 0.0f, 20000.0f);
}

// Perspective constructor
Camera::Camera(float _fFOV, float _fRatio, float _fNear, float _fFar) :m_fFOV(_fFOV){
	m_mfProjection = glm::perspective(_fFOV, _fRatio, _fNear, _fFar);
}

Camera::~Camera(){}

/***********************
* GetView: Returns the view matrix of the camera
* @author: Kerry Pellett (2018)
* @parameter: void
* @return: glm::mat4 that is the view matrix of the camera
********************/
glm::mat4 Camera::GetView() const{
	return glm::lookAt(m_vfCameraPos, m_vfCameraPos + m_vfCameraFront, m_vfCameraUp);
}

/***********************
* GetProjection: Obtains the projection matrix of the camera
* @author: Kerry Pellett (2018)
* @parameter: void
* @return: glm::mat4 that is the camera's projection matrix
********************/
glm::mat4 Camera::GetProjection()const {
	return m_mfProjection;
}

void Camera::SetPosition(glm::vec3 _position) {
	m_vfCameraPos = _position;
}

void Camera::UpdatePosition(float _fX, float _fY, float _fZ) {
	m_vfCameraPos += glm::vec3(_fX, _fY, _fZ);
	//SetPosition(m_vfCameraPos); // If functionality changes
	
}

glm::vec3 Camera::GetPosition()const {
	return m_vfCameraPos;
}

void Camera::PointAt(glm::vec3 _vfPoint) {
	// Create new forward vector
	m_vfCameraFront = glm::normalize(_vfPoint - m_vfCameraPos);
	// Create right vector
	m_vfCameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), m_vfCameraFront));
	// Create camera up
	m_vfCameraUp = glm::normalize(glm::cross(m_vfCameraFront, m_vfCameraRight));
}

void Camera::SetOffset(glm::vec3 _vfOffset) {
	m_vfOffset = _vfOffset;
}

glm::vec3 Camera::GetOffset()const {
	return m_vfOffset;
}

glm::vec3 Camera::GetRight()const {
	return m_vfCameraRight;
}

glm::vec3 Camera::GetUp()const {
	return m_vfCameraUp;
}