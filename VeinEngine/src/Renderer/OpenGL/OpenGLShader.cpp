#include "vnpch.h"
#include "Renderer/OpenGL/OpenGLShader.h"

#include "Core/Logger/Logger.h"

#include <fstream>
#include <glad/glad.h>

namespace Vein
{

	OpenGLShader::OpenGLShader(const String& name)
		: m_Name(name)
	{
		std::unordered_map<GLenum, String> sources;

		String vSrcCode = ReadSourceFile("data/shaders/" + name + ".vert");
		sources[GL_VERTEX_SHADER] = vSrcCode;

		String fSrcCode = ReadSourceFile("data/shaders/" + name + ".frag");
		sources[GL_FRAGMENT_SHADER] = fSrcCode;

		//String gSrcCode = ReadSourceFile("assets/shaders/" + name + ".geom");
		//if (gSrcCode != "")
		//	sources[GL_GEOMETRY_SHADER] = gSrcCode;

		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	String OpenGLShader::ReadSourceFile(const String& srcFile)
	{
		String srcCode = "";

		std::ifstream srcFileStream(srcFile.c_str());
		if (srcFileStream.fail())
			VN_ERROR("Shaders: Failed to read file: {0}, check if the file exists or if the correct path was given.", srcFile.c_str());

		std::stringstream srcCodeStream;
		srcCodeStream << srcFileStream.rdbuf();

		srcCode = srcCodeStream.str().c_str();

		return srcCode;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, String>& shaderSources)
	{
		GLuint program = glCreateProgram();
		VN_ASSERT(shaderSources.size() <= 3, "OpenGL supports a maximum of 3 shaders types only: Vertex, Fragment and Geometry");
		std::array<GLenum, 3> glShaderIDs;
		int glShaderIDIndex = 0;
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const String& source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				VN_ERROR("{0}", infoLog.data());
				VN_ASSERT(false, "Shader compilation failure!");
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		m_RendererID = program;

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			for (auto id : glShaderIDs)
				glDeleteShader(id);

			VN_ERROR("{0}", infoLog.data());
			VN_ASSERT(false, "Shader link failure!");
			return;
		}

		for (auto id : glShaderIDs)
			glDetachShader(program, id);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const String& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}
	void OpenGLShader::SetFloat(const String& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}
	void OpenGLShader::SetVec2f(const String& name, const Vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}
	void OpenGLShader::SetVec3f(const String& name, const Vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}
	void OpenGLShader::SetVec4f(const String& name, const Vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}
	void OpenGLShader::SetMat3(const String& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void OpenGLShader::SetMat4(const String& name, const Mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}