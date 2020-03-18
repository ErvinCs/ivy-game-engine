workspace "Ivy"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Relative to the root
IncludeDir = {}
IncludeDir["glfw"]        = "IvyEngine/vendor/glfw/include" 
IncludeDir["glad"]        = "IvyEngine/vendor/glad/include" 
IncludeDir["imgui"]       = "IvyEngine/vendor/imgui" 
IncludeDir["glm"]         = "IvyEngine/vendor/glm" 
IncludeDir["stb_image"]   = "IvyEngine/vendor/stb_image"
IncludeDir["angelscript"] = "IvyEngine/vendor/angelscript/include"

group "Dependencies"
    include "IvyEngine/vendor/glfw"
    include "IvyEngine/vendor/glad"
    include "IvyEngine/vendor/imgui"
    include "IvyEngine/vendor/angelscript"

project "IvyEngine"
    location "IvyEngine"
    kind "StaticLib"            
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
        "%{prj.name}/vendor/glm/glm/**.inl",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
        --"%{prj.name}/vendor/eastl/include/EASTL/**.h"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "ANGELSCRIPT_EXPORT"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        --"%{prj.name}/vendor/eastl"
        "%{IncludeDir.angelscript}"
    }

    links 
    {
        "glfw",
        "glad",
        "imgui",
        "angelscript",
        "opengl32.lib"

    }

    -- Windows specific properties
    filter "system:windows"
        systemversion "latest"

        defines
        {
            "IVY_PLATFORM_WINDOWS",
            "IVY_PLATFORM_LINUX",
            "IVY_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
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
    kind "ConsoleApp"           
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
        "IvyEngine/vendor",
        "IvyEngine/src",
        "%{IncludeDir.glm}",
        --"%{prj.name}/vendor/eastl"
        "%{IncludeDir.angelscript}"
    }

    links
    {
        "IvyEngine"
    }

    -- Windows specific properties
    filter "system:windows"
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
