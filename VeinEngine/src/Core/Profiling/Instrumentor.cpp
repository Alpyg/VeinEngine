#include "vnpch.h"
#include "Core/Profiling/Instrumentor.h"

#include "Core/Logger/Logger.h"

namespace Vein
{

    Instrumentor::Instrumentor() : m_CurrentSession(nullptr)
    {
    }

    void Instrumentor::BeginSession(const String& t_Name, const String& t_FilePath)
    {
		std::lock_guard lock(m_Mutex);
		if (m_CurrentSession) {
			// If there is already a current session, then close it before beginning new one.
			// Subsequent profiling output meant for the original session will end up in the
			// newly opened session instead.  That's better than having badly formatted
			// profiling output.
			if (Logger::GetLogger()) { // Edge case: BeginSession() might be before Log::Init()
				VN_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", t_Name.c_str(), m_CurrentSession->Name.c_str());
			}
			InternalEndSession();
		}
		m_OutputStream.open(t_FilePath.c_str());

		if (m_OutputStream.is_open()) {
			m_CurrentSession = new InstrumentationSession({ t_Name });
			WriteHeader();
		}
		else {
			if (Logger::GetLogger()) { // Edge case: BeginSession() might be before Log::Init()
				VN_ERROR("Instrumentor could not open results file '{0}'.", t_FilePath.c_str());
			}
		}
    }

	void Instrumentor::EndSession()
	{
		std::lock_guard lock(m_Mutex);
		InternalEndSession();
	}

	void Instrumentor::WriteProfile(const ProfileResult& t_Result)
	{
		std::stringstream json;

		String name = t_Result.Name;
		name.replace('"', '\'');

		json << std::setprecision(3) << std::fixed;
		json << ",{";
		json << "\"cat\":\"function\",";
		json << "\"dur\":" << (t_Result.ElapsedTime.count()) << ',';
		json << "\"name\":\"" << name << "\",";
		json << "\"ph\":\"X\",";
		json << "\"pid\":0,";
		json << "\"tid\":" << t_Result.ThreadID << ",";
		json << "\"ts\":" << t_Result.Start.count();
		json << "}";

		std::lock_guard lock(m_Mutex);
		if (m_CurrentSession) {
			m_OutputStream << json.str();
			m_OutputStream.flush();
		}
	}

	void Instrumentor::WriteHeader()
	{
		m_OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
		m_OutputStream.flush();
	}

	void Instrumentor::WriteFooter()
	{
		m_OutputStream << "]}";
		m_OutputStream.flush();
	}

	void Instrumentor::InternalEndSession()
	{
		if (m_CurrentSession) {
			WriteFooter();
			m_OutputStream.close();
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
		}
	}

}