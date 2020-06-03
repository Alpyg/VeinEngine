#include "vnpch.h"
#include "Renderer/Camera.h"

namespace Vein
{

	Camera::Camera(const CameraType& t_Type, const Vec2& t_Aspect)
		: m_Type(t_Type)
		, m_Aspect(t_Aspect)
		, m_ProjectionMatrix(1.0f)
		, m_ViewMatrix(1.0f)
	{
		SetCameraType(m_Type);
	}

	Camera& Camera::operator=(const Camera& t_Camera)
	{
		m_Type = t_Camera.m_Type;
		m_Aspect = t_Camera.m_Aspect;
		m_ProjectionMatrix = t_Camera.m_ProjectionMatrix;
		m_ViewMatrix = t_Camera.m_ViewMatrix;
		m_FOV = t_Camera.m_FOV;

		return *this;
	}

	const Mat4& Camera::GetViewMatrix(const Mat4& t_TransformMatrix)
	{
		CalculateViewMatrix(t_TransformMatrix);
		return m_ViewMatrix;
	}

	void Camera::CalculateProjMatrix()
	{
		switch (m_Type)
		{
			case CameraType::Perspective: m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_Aspect.x / m_Aspect.y, 0.1f, 1000.0f); break; // Change 1000.0f to render distance
			case CameraType::Orthographic: m_ProjectionMatrix = glm::ortho(-m_Aspect.x, m_Aspect.x, -m_Aspect.y, m_Aspect.y, -1.0f, 1.0f); break;
		}
	}

	void Camera::CalculateViewMatrix(const Mat4& t_TransformMatrix)
	{
		m_ViewMatrix = m_ProjectionMatrix * t_TransformMatrix;
	}

}