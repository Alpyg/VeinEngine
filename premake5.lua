workspace "Vein"
	architecture "x64"
	
	startproject "VeinSandbox"
	
	configurations
	{
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["spdlog"] = "VeinEngine/dependencies/spdlog/include"
IncludeDir["glfw"] = "VeinEngine/dependencies/glfw/include"
IncludeDir["glad"] = "VeinEngine/dependencies/glad/include"
IncludeDir["glm"] = "VeinEngine/dependencies/glm"
IncludeDir["imgui"] = "VeinEngine/dependencies/imgui"
IncludeDir["stb_image"] = "VeinEngine/dependencies/stb_image"
IncludeDir["assimp"] = "VeinEngine/dependencies/assimp/include"

group "Dependencies"
	include "VeinEngine/dependencies"
group ""

project "VeinEngine"
	location "VeinEngine"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "vnpch.h"
	pchsource "VeinEngine/src/vnpch.cpp"
	
	files {
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/dependencies/stb_image/*"
	}
	
	includedirs {
		"%{prj.name}/include/",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.assimp}/../build/include"
	}
	
	links {
		"glad",
		"glfw",
		"imgui",
		"opengl32.lib"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"BUILD_SHARED_LIB"
    }
			
	filter "system:windows"
		systemversion "latest"

		defines {
			"VN_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands {
			"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/VeinSandbox/"
		}
			
	filter "system:linux"
		systemversion "latest"

		defines {
			"VN_PLATFORM_LINUX",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands {
			"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/VeinSandbox/"
		}

	filter "configurations:Debug"
		defines "VN_DEBUG"
		runtime "Debug"
		symbols "on"

		defines {
			"VN_ENABLE_ASSERTS",
			"VN_PROFILE",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Release"
		defines "VN_RELEASE"
		runtime "Release"
		optimize "on"


project "VeinSandbox"
	location "VeinSandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files {
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp",
	}
	
	includedirs {
		"%{prj.name}/include/",
		"VeinEngine/include/",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.assimp}/../build/include"
	}

	links {
		"VeinEngine",
		"imgui"
    }

	defines {
		"_CRT_SECURE_NO_WARNINGS"
    }
	
	filter "system:windows"
		systemversion "latest"

		defines {
			"VN_PLATFORM_WINDOWS"
		}
	
	filter "system:linux"
		systemversion "latest"

		defines {
			"VN_PLATFORM_LINUX"
		}

	filter "configurations:Debug"
		defines "VN_DEBUG"
		runtime "Debug"
		symbols "on"

		defines {
			"VN_ENABLE_ASSERTS",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Release"
		defines "VN_RELEASE"
		runtime "Release"
		optimize "on"
