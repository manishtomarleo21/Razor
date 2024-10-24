workspace "Razor"
    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Razor/vendor/GLFW/include"

include "Razor/vendor/GLFW"

project "Razor"
    location "Razor"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "rzpch.h"
    pchsource "Razor/src/rzpch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}"
    }

    links{
        "GLFW",
        "opengl32.lib",
        "dwmapi.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

    defines {
        "RZ_PLATFORM_WINDOWS",
        "RZ_BUILD_DLL"
    }

    postbuildcommands {
         "{RMDIR} ../bin/" .. outputdir .. "/Sandbox",
        "{MKDIR} ../bin/" .. outputdir .. "/Sandbox",
        "{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"
    }

filter "configurations:Debug"
    defines "RZ_DEBUG"
    symbols "On"
    systemversion "latest"  -- Add this to ensure the configuration is applied

filter "configurations:Release"
    defines "RZ_RELEASE"
    optimize "On"
    systemversion "latest"  -- Add this to ensure the configuration is applied

filter "configurations:Dist"
    defines "RZ_DIST"
    optimize "On"
    systemversion "latest"  -- Add this to ensure the configuration is applied

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Razor/vendor/spdlog/include",
        "Razor/src"
    }

    links {
        "Razor"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

    defines {
        "RZ_PLATFORM_WINDOWS"
    }

filter "configurations:Debug"
    defines "RZ_DEBUG"
    symbols "On"
    systemversion "latest"

filter "configurations:Release"
    defines "RZ_RELEASE"
    optimize "On"
    systemversion "latest"

filter "configurations:Dist"
    defines "RZ_DIST"
    optimize "On"
    systemversion "latest"