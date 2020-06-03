#pragma once

#include <algorithm>
#include <fstream>
#include <thread>
#include <mutex>

#include "Core/String/String.h"

namespace Vein
{

	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

	struct ProfileResult
	{
		String Name;

		FloatingPointMicroseconds Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;
	};

	struct InstrumentationSession
	{
		String Name;
	};

	class Instrumentor
	{
	public:
		VN_API Instrumentor();

		VN_API void BeginSession(const String& t_Name, const String& t_Filepath);
		VN_API void EndSession();

		VN_API void WriteProfile(const ProfileResult& t_Result);

		VN_API static Instrumentor& Get() {
			static Instrumentor instance;
			return instance;
		}

	private:
		VN_API void WriteHeader();
		VN_API void WriteFooter();

		// Note: you must already own lock on m_mutex before
		// calling InternalEndSession()
		VN_API void InternalEndSession();

		std::mutex m_Mutex;
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
	};

}

#define VN_PROFILE 1
#if VN_PROFILE
// Resolve which function signature macro will be used. Note that this only
// is resolved when the (pre)compiler starts, so the syntax highlighting
// could mark the wrong one in your editor!
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#define VN_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define VN_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
#define VN_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define VN_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define VN_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define VN_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define VN_FUNC_SIG __func__
#else
#define VN_FUNC_SIG "VN_FUNC_SIG unknown!"
#endif

#define VN_PROFILE_BEGIN_SESSION(t_Name, filepath)  ::Vein::Instrumentor::Get().BeginSession(t_Name, filepath)
#define VN_PROFILE_END_SESSION()                  ::Vein::Instrumentor::Get().EndSession()
#define VN_PROFILE_SCOPE(t_Name)                    ::Vein::InstrumentationTimer timer##__LINE__(t_Name);
#define VN_PROFILE_FUNCTION()                     VN_PROFILE_SCOPE(VEIN_FUNC_SIG)
#else
#define VN_PROFILE_BEGIN_SESSION(t_Name, filepath)
#define VN_PROFILE_END_SESSION()
#define VN_PROFILE_SCOPE(t_Name)
#define VN_PROFILE_FUNCTION()
#endif