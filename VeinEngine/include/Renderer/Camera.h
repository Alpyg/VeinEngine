#pragma once

namespace Vein
{

	enum class CameraType
	{
		Perspective, Orthographic
	};

	class Camera
	{
	public:
		VN_API Camera(const CameraType& t_Type = CameraType::Perspective, const Vec2& t_Aspect = { 1.6f, 0.9f });
		VN_API Camera& operator=(const Camera& t_Camera);
		VN_API virtual ~Camera() = default;


		VN_API void SetAspect(const Vec2& t_Aspect) { m_Aspect = { t_Aspect.x, t_Aspect.y }; CalculateProjMatrix(); }
		VN_API void SetCameraType(const CameraType& t_Type) { m_Type = t_Type; }
		VN_API const CameraType& GetCameraType() { return m_Type; }

		VN_API const Mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		VN_API const Mat4& GetViewMatrix(const Mat4& t_TransformMatrix);

		VN_API void SetFOV(const float t_FOV) { m_FOV = (t_FOV > 110.0f) ? 110.0f : (t_FOV < 30.0f) ? 30.0f : t_FOV; }
		VN_API const float GetFOV() { return m_FOV; };
	private:
		VN_API void CalculateProjMatrix();
		VN_API void CalculateViewMatrix(const Mat4& t_TransformMatrix);

		CameraType m_Type;
		Vec2 m_Aspect;
		Mat4 m_ProjectionMatrix;
		Mat4 m_ViewMatrix;

		float m_FOV = 70.0f;
	};

}