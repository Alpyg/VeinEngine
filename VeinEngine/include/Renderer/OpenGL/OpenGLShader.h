#pragma once

#include "Renderer/Shader.h"

namespace Vein
{

	typedef unsigned int GLenum;

	class OpenGLShader : public Shader
	{
	public:
		VN_API OpenGLShader(const String& t_Name);
		VN_API virtual ~OpenGLShader();

		VN_API virtual void Bind() const override;
		VN_API virtual void Unbind() const override;

		VN_API virtual const String& GetName() const override { return m_Name; }

		VN_API void SetInt(const String& t_Name, int t_Value);

		VN_API void SetFloat(const String& t_Name, float t_Value);
		VN_API void SetVec2f(const String& t_Name, const Vec2& t_Value);
		VN_API void SetVec3f(const String& t_Name, const Vec3& t_Value);
		VN_API void SetVec4f(const String& t_Name, const Vec4& t_Value);

		VN_API void SetMat3(const String& t_Name, const glm::mat3& t_Matrix);
		VN_API void SetMat4(const String& t_Name, const Mat4& t_Matrix);
	private:
		VN_API String ReadSourceFile(const String& t_SrcFile);
		VN_API void Compile(const std::unordered_map<GLenum, String>& t_SrcShader);

		uint32_t m_RendererID;
		String m_Name;
	};

}