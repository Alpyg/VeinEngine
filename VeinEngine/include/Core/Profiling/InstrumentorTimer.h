#pragma once

#include <chrono>

namespace Vein
{

	class InstrumentationTimer
	{
	public:
		VN_API InstrumentationTimer(const char* t_Name);
		VN_API ~InstrumentationTimer();

		VN_API void Stop();
	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
		bool m_Stopped;
	};

}