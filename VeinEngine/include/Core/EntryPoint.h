#pragma once

#include "Core/Application/Application.h"
#include "Core/Logger/Logger.h"
#include "Core/Profiling/Instrumentor.h"

#ifdef VN_PLATFORM_WINDOWS

extern Vein::Application* Vein::CreateApplication();

int main(int argc, char** argv)
{
	Vein::Logger::Init();

	VN_PROFILE_BEGIN_SESSION("Startup", "VeinEngine-Startup.json");
	auto app = Vein::CreateApplication();
	VN_PROFILE_END_SESSION();

	VN_PROFILE_BEGIN_SESSION("Runtime", "VeinEngine-Runtime.json");
	app->Run();
	VN_PROFILE_END_SESSION();

	VN_PROFILE_BEGIN_SESSION("Shutdown", "VeinEngine-Shutdown.json");
	delete app;
	VN_PROFILE_END_SESSION();
}

#endif