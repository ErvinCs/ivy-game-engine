workspace "Ivy"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "IvyEngine"
	location "IvyEngine"
	kind "SharedLib"			-- DLL
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ivypch.h"
	pchsource "IvyEngine/src/ivypch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
		--"%{prj.name}/vendor/eastl/include/EASTL/**.h"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/glm"
		--"%{prj.name}/vendor/eastl"
	}

	-- Windows specific properties
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"		-- Linking the runtime libraries
		systemversion "latest"

		defines
		{
			"IVY_PLATFORM_WINDOWS",
			"IVY_PLATFORM_LINUX",
			"IVY_BUILD_DLL"
		}

		-- Post-build: place the dll into IvyApplication
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/IvyApplication")
		}

	filter "configurations:Debug"
		defines "IVY_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "IVY_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "IVY_DIST"
		runtime "Release"
		optimize "on"

-- Application

project "IvyApplication"
	location "IvyApplication"
	kind "ConsoleApp"			-- DLL
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir   ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"IvyEngine/vendor/spdlog/include",
		"IvyEngine/src",
		"%{prj.name}/vendor/glm"
		--"%{prj.name}/vendor/eastl"
	}

	links
	{
		"IvyEngine"
	}

	-- Windows specific properties
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"		-- Linking the runtime libraries
		systemversion "latest"

		defines
		{
			"IVY_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "IVY_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "IVY_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "IVY_DIST"
		runtime "Release"
		optimize "on"